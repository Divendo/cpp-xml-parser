/*************************** GPLv3 License *****************************
<xmlParser> is an opensource easy-to-use xml parser
Copyright (C) 2011  Divendo

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
***********************************************************************/

#include "document.h"

#include <sstream>
#include <cctype>

namespace xml
{
    // Public
        document::document(const element& root, const std::string& initEncoding)
            : root(root), strEncoding(initEncoding), parseStream(0)
        {
            if(strEncoding == "" || strEncoding.find('"') != std::string::npos)
                strEncoding = "ISO-8859-1";
        }
        document::document(const std::string& rootName, const std::string& initEncoding)
            : root(rootName), strEncoding(initEncoding)
        {
            if(strEncoding == "" || strEncoding.find('"') != std::string::npos)
                strEncoding = "ISO-8859-1";
        }

        std::string document::toString() const
        {
            std::ostringstream out; // Create an ostringstream
            out<<*this;             // Write this document to the stream
            return out.str();       // Convert the stream to a string and return the string
        }

        void document::setEncoding(const std::string& newEncoding)
        {
            if(newEncoding != "" || newEncoding.find('"') != std::string::npos)
                strEncoding = newEncoding;
        }


        std::string document::encoding() const
        { return strEncoding; }

        void document::parse(std::istream& in) throw(parseError)
        {
            try
            {
                strEncoding = "ISO-8859-1"; // Reset the encoding, this will be overwritten if an encoding is found
                parseStream = &in;          // Remember the input stream, it will be used in other member functions
                parseLine = 0;              // Reset the variables which keep track of the current line
                parsePos = 0;               // and position in the stream
                parseDocumentStart();       // Start parsing
                parseStream = 0;            // When done, stop pointing to the stream
            }
            catch(parseError&)              // If an error occurred
            {
                parseStream = 0;            // Stop pointing to the stream
                strEncoding = "ISO-8859-1"; // Reset the encoding
                root = element("root");     // Reset the root-tag
                throw;                      // Re-throw the error
            }
        }

        void document::parse(const std::string& str) throw(parseError)
        {
            std::istringstream stream(str); // Create a stream from the string
            parse(stream);                  // Parse the string using the created stream
        }

    // Private:
        void document::parseDocumentStart() throw(parseError)
        {
            char chr = 0;                       // Used for reading characters from the stream
            std::string buffer = "";            // Used for temporarily storing a few read characters
            int oldParsePos = parsePos;         // Used to store the previous parsePos, that is before it's resetted because a newline is found
                                                // This might be needed because characters may be put back in the stream

            while(parseStream->get(chr))        // Get a character from the stream, and check if the stream is still ok
            {
                // Keep track of where we are in the stream
                if(chr == '\n')
                {
                    ++parseLine;
                    oldParsePos = parsePos;
                    parsePos = 0;
                }
                else
                    ++parsePos;

                if(chr == '<')                  // If the character we just read is a <
                    buffer += chr;              // Add it to the buffer
                else if (buffer != "")          // If it wasn't a < and the buffer isn't empty (because if it is, this character isn't interesting)
                {
                    buffer += chr;              // Add it to the buffer
                    // Check if we're at the start of the document start-tag
                    if(buffer.length() == 2 && buffer != "<?")
                    {
                        parseStream->putback('<');  // Since a tag is started and it wasn't the start-tag of the document, it must be the root-tag
                                                    // To parse the root tag, we need the opening <
                        --parsePos;                 // Decrease the parsing position
                        parseStream->putback(chr);  // Put the last read character back in the stream
                        if(chr == '\n')             // If the last read character was a newline
                        {
                            --parseLine;            // We need to decrease the line number by 1
                            parsePos = oldParsePos; // and restore the old parsing position
                        }
                        else                        // If the last read character wasn't a newline
                            --parsePos;             // Just decrease the parsing position by 1
                        buffer = "";                // Clear the buffer
                        break;                      // Stop searching for the start-tag
                    }
                    else if(chr == '>')             // If we have found the end of the start-tag of the document
                        break;                      // Stop searching
                }
            }

            // Check if the reading went well
            // If not something's wrong, because this function may not yet reach the end of the stream
            if(!parseStream->good())
            {
                if(parseStream->eof())
                    throw parseError(parseError::unexpectedEnd);
                else if(parseStream->fail())
                    throw parseError(parseError::readingError);
            }

            // Check if we've found the start-tag
            if(buffer != "")
            {
                // Search for the encoding attribute, and set the encoding if it is there
                size_t start = buffer.find("encoding=\"");
                if(start != std::string::npos)
                {
                    start += 10;
                    size_t end = buffer.find('"', start);
                    if(end != std::string::npos)
                        strEncoding = fromXmlEntities(buffer.substr(start, end - start));
                }
                else if((start = buffer.find("encoding='")) != std::string::npos)
                {
                    start += 10;
                    size_t end = buffer.find('\'', start);
                    if(end != std::string::npos)
                        strEncoding = fromXmlEntities(buffer.substr(start, end - start));
                }
            }

            // Clear any whitespaces between the start-tag and the root-tag, and then parse the root-tag
            while(parseStream->get(chr))        // Get a character from the stream, and check if the stream is still ok
            {
                // Keep track of where we are in the stream
                if(chr == '\n')
                {
                    ++parseLine;
                    parsePos = 0;
                }
                else
                    ++parsePos;

                // Stop clearing the whitespaces when we find the opening < of the root-tag
                if(chr == '<')
                    break;
            }
            // Check if the reading went well
            // If not something's wrong, because this function may not yet reach the end of the stream
            if(!parseStream->good())
            {
                if(parseStream->eof())
                    throw parseError(parseError::unexpectedEnd);
                else if(parseStream->fail())
                    throw parseError(parseError::readingError);
            }
            root = parseElement();              // Parse the root-tag, and store it
        }

        element document::parseElement() throw(parseError)
        {
            // Read the name from the stream
            // Throw an error if the name appears to be invalid
            char chr = 0;
            std::string name = "";
            while(parseStream->get(chr))
            {
                // Keep track of where we are in the stream
                if(chr == '\n')
                {
                    ++parseLine;
                    parsePos = 0;
                }
                else
                    ++parsePos;

                // The name ends when a whitespace is detected
                if(std::isspace(chr))
                    break;

                // The name also ends when a > is detected
                // The > needs to be put back because it is needed to stop searching for attributes
                if(chr == '>')
                {
                    parseStream->putback('>');
                    --parsePos;
                    break;
                }

                // Add the character to the name
                name += chr;

                // If any forbidden characters are found in the name, throw an error
                if(chr == '<' || chr == '&' || chr == '\'' || chr =='"' || (name == "" && !std::isalpha(chr)) || (!std::isalnum(chr) && !std::ispunct(chr)) ||
                   (name.length() == 3 && std::tolower(name[0]) == 'x' && std::tolower(name[1]) == 'm' && std::tolower(name[2]) == 'l'))
                    throw parseError(parseError::invalidTagname, parseLine, parsePos, name);
            }
            if(!parseStream->good())
            {
                if(parseStream->eof())
                    throw parseError(parseError::unexpectedEnd);
                else if(parseStream->fail())
                    throw parseError(parseError::readingError);
            }

            // Read the attributes (if there are any)
            element out(name);
            name = "";                                  // Will now represent the name of the attribute
            std::string value = "";                     // Represents the value of the attribute
            bool readingName = true;                    // Whether we're currently reading the name or the value
            bool selfClose = false;                     // Whether the element is a selfclosing element (e.g. <name />)
            int quotes = -1;                            // Whether the attribute's value is surrounded by double quotes (") or single quotes (')
                                                        //     -1 => Unknown
                                                        //      0 => No quotes (stop at first whitespace)
                                                        //      1 => Double quotes
                                                        //      2 => Single quotes
            while(parseStream->get(chr))
            {
                // Keep track of where we are in the stream
                if(chr == '\n')
                {
                    ++parseLine;
                    parsePos = 0;
                }
                else
                    ++parsePos;

                // If the closing > is found, stop searching attributes
                if(chr == '>')
                {
                    selfClose = (name == "/");          // If there was a / before the closing >
                    break;
                }

                // If we're reading the name of an attribute
                if(readingName)
                {
                    // If the current character is a whitespace, it's skipped
                    // If we already had a piece of a name we'll just add it to the attribute list as an attribute without a value
                    if(std::isspace(chr))
                    {
                        if(name != "")
                        {
                            out[name] = "";
                            name = "";
                        }
                    }
                    // If we found an =, we're at the end of the name and can start parsing the attribute's value
                    else if(chr == '=')
                    {
                        quotes = -1;                    // We don't know yet what kind of quotes are used for the value
                        readingName = false;            // We're done parsing the name
                    }
                    // Any other character will be a part of the name
                    else
                        name += chr;
                }
                else                                    // We're parsing the attribute's value
                {
                    // If we haven't determined yet which quotes are used, we'll do that now
                    if(quotes == -1)
                    {
                        switch(chr)
                        {
                            case '"':  quotes = 1; break;
                            case '\'': quotes = 2; break;
                            default:
                                quotes = 0;
                                value += chr;
                            break;
                        }
                    }
                    // If the closing quot or whitespace is found, add the attribute and reset the variables used for the parsing
                    else if((quotes == 1 && chr == '"') || (quotes == 2 && chr == '\'') || (quotes == 0 && std::isspace(chr)))
                    {
                        out[name] = fromXmlEntities(value);
                        name = "";
                        value = "";
                        readingName = true;
                        quotes = -1;
                    }
                    else
                        value += chr;
                }
            }
            if(!parseStream->good())
            {
                if(parseStream->eof())
                    throw parseError(parseError::unexpectedEnd);
                else if(parseStream->fail())
                    throw parseError(parseError::readingError);
            }
            // If it was a selfclosing element, we're done parsing this element
            if(selfClose)
                return out;
            // If we had an unfinished attribute, add it to the element
            if(name != "")
                out[name] = fromXmlEntities(value);

            // Read the body and child elements
            name = "";                          // Temporarily store the name of the closing tag
            std::string body = "";              // Store the contents of the body of this element
            bool openingFound = false;          // True if the previous character was a <, false otherwise
            bool closingTag = false;            // True if we're currently parsing the name of a closing tag
            int oldParsePos = parsePos;         // Used to store the previous parsePos, that is before it's resetted because a newline is found
                                                // This might be needed because characters may be put back in the stream
            while(parseStream->get(chr))
            {
                // Keep track of where we are in the stream
                if(chr == '\n')
                {
                    ++parseLine;
                    oldParsePos = parsePos;
                    parsePos = 0;
                }
                else
                    ++parsePos;

                if(openingFound)
                {
                    if(closingTag)
                    {
                        if(chr == '>')
                        {
                            if(name == out.name())
                                break;
                            throw parseError(parseError::unclosedElement, parseLine, parsePos, out.name());
                        }
                        else
                            name += chr;
                    }
                    else
                    {
                        if(chr != '/')
                        {
                            // It was the opening of a child element
                            parseStream->putback(chr);  // Put the last read character back in the stream
                            if(chr == '\n')             // If the last read character was a newline
                            {
                                --parseLine;            // We need to decrease the line number by 1
                                parsePos = oldParsePos; // and restore the old parsing position
                            }
                            else                        // If the last read character wasn't a newline
                                --parsePos;             // Just decrease the parsing position by 1

                            // Parse the child element and append it to the current element
                            out.children.append(parseElement());
                            openingFound = false;
                            closingTag = false;
                        }
                        else
                        {
                            name = "";
                            closingTag = true;
                        }
                    }
                }
                else
                {
                    if(chr == '<')
                        openingFound = true;
                    else
                        body += chr;
                }
            }
            if(parseStream->bad() || (!parseStream->eof() && parseStream->fail()))
                throw parseError(parseError::readingError);

            out.body = fromXmlEntities(body);
            return out;
        }

    // Function to write a document to an output stream (friend of document)
    std::ostream& operator<<(std::ostream& out, const document& doc)
    {
        // Write the xml version and encoding to the stream, the version is always 1.0
        out<<"<?xml version=\"1.0\" encoding=\""<<doc.strEncoding<<"\"?>";

        // Write the root element to the stream
        out<<doc.root;

        // Return the stream
        return out;
    }

    // Function to read a document from an input stream
    std::istream& operator>>(std::istream& in, document& doc) throw(parseError)
    {
        doc.parse(in);
        return in;
    }

} // namespace xml
