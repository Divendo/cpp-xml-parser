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

s#include "element.h"

#include <cctype>
#include <sstream>

namespace xml
{
    // Public:
        element::element(const std::string& elementName, const std::string& body)
            : body(body), children(this), chrReplacement(0), elementParent(0)
        {
            if(validateName(elementName))
                strName = elementName;
            else
                strName = "tag";
        }

        element::element(const element& other)
            : children(this), elementParent(0)
        { copyFrom(other); }

        element& element::operator=(const element& other)
        {
            copyFrom(other);
            return *this;
        }

        bool element::rename(const std::string& newName)
        {
            if(validateName(newName))
            {
                strName = newName;
                return true;
            }
            return false;
        }

        std::string element::name() const
        {return strName;}

        element* element::parent()
        { return elementParent; }
        const element* element::parent() const
        { return elementParent; }

        bool element::setReplacementChar(const char& newChr)
        {
            if(element::validateReplacementChar(newChr))
            {
                chrReplacement = newChr;
                return true;
            }
            return false;
        }

        char element::replacementChar() const
        {
            if(chrReplacement == 0)                     // If this instance doesn't have it's own attribute-replacement-character
                return element::staticChrReplacement;   // We use the default
            return chrReplacement;                      // If it does have it's own, we use it's own attribute-replacement-character
        }
        void element::useDefault(const bool& use)
        {
            if(use)                                                 // If we have to use the default attribute-replacement-character
                chrReplacement = 0;                                 // Make this instance stop using it's own attribute-replacement-character
            else                                                    // If we have to use the attribute-replacement-character of this instance
            {
                if(chrReplacement == 0)                             // Check if this instance has an attribute-replacement-character
                    chrReplacement = element::staticChrReplacement; // If not, change the attribute-replacement-character of this instance to the default
                // If it does have it's own attribute-replacement-character, nothing needs to be done
            }
        }

        // Static:
            bool element::setDefaultReplacementChar(const char& newChr)
            {
                if(element::validateReplacementChar(newChr))
                {
                    element::staticChrReplacement = newChr;
                    return true;
                }
                return false;
            }
            char element::defaultReplacementChar()
            { return element::staticChrReplacement; }

        element::iterator element::begin()
        { return mapAttrs.begin(); }
        element::const_iterator element::begin() const
        { return mapAttrs.begin(); }
        element::iterator element::end()
        { return mapAttrs.end(); }
        element::const_iterator element::end() const
        { return mapAttrs.end(); }

        element::reverse_iterator element::rbegin()
        { return mapAttrs.rbegin(); }
        element::const_reverse_iterator element::rbegin() const
        { return mapAttrs.rbegin(); }
        element::reverse_iterator element::rend()
        { return mapAttrs.rend(); }
        element::const_reverse_iterator element::rend() const
        { return mapAttrs.rend(); }

        std::string element::getAttribute(const std::string attrName) const
        {
            std::map<std::string, std::string>::const_iterator pos = mapAttrs.find(attrName);
            if(pos != mapAttrs.end())
                return pos->second;
            return "";
        }
        std::string element::operator[](const std::string& attrName) const
        { return getAttribute(attrName); }
        std::string& element::operator[](const std::string& attrName)
        {
            if(attributeExists(attrName))                           // If the attribute exists
                return mapAttrs[attrName];                          // Return a reference to it's value
            return mapAttrs[replaceIllegalChars(attrName)] = "";    // If it doesn't exist, create an empty one with a valid name and return a reference to it's value
        }

        void element::setAttribute(const std::string& attrName, const std::string& newValue)
        {
            // Replace any illegal characters with the attribute-replacement-character to make sure the name is valid
            // Then assign the new value to it, if the attribute didn't exist it will be created
            mapAttrs[replaceIllegalChars(attrName)] = newValue;
        }

        bool element::attributeExists(const std::string& attrName) const
        { return mapAttrs.count(attrName); }

        bool element::removeAttribute(const std::string& attrName)
        { return mapAttrs.erase(attrName); }

        std::string element::toString() const
        {
            std::ostringstream out; // Create an ostringstream
            out<<*this;             // Write this element to the stream
            return out.str();       // Convert the stream to a string and return the string
        }

    // Protected:
        // Static
            char element::staticChrReplacement = '_';
            bool element::validateReplacementChar(const char& chr)
            {
                if(chr == 'x' || chr == 'X' ||                  // 'x' and 'X' aren't allowed, because a name may not start with "xml" or "Xml", so the names can not always start with an 'x' or 'X'
                   std::iscntrl(chr) || std::isspace(chr) ||    // Control characters and whitespaces aren't allowed in names
                   chr == '<' || chr == '>' || chr == '&' ||
                   chr == '\'' || chr =='"')                    // These characters are reserved for xml, and therefore illegal in names
                    return false;
                return true;
            }

        std::string element::replaceIllegalChars(std::string str)
        {
            const char replacement = replacementChar();

            // A name may not start with "xml" (uppercase or lowercase)
            if(str.length() >= 3 && std::tolower(str[0]) == 'x' && std::tolower(str[1]) == 'm' && std::tolower(str[2]) == 'l')
                str[0] = replacement;

            // A name may not be empty
            if(str.length() == 0)
                str += replacement;

            for(std::string::iterator pos = str.begin(); pos != str.end(); ++pos)
            {
                if(pos == str.begin())
                {
                    // A name may only start with an alphabetical character
                    if(!std::isalpha(*pos))
                        *pos = replacement;
                }
                // A name can only contain alphanumerical characters or punctation characters
                // But it may not contain any xml-reserved characters (i.e. <>&'")
                else if((!std::isalnum(*pos) && !std::ispunct(*pos)) || (*pos == '<' || *pos == '>' || *pos == '&' || *pos == '\'' || *pos =='"'))
                    *pos = replacement;
            }

            // Return the corrected string
            return str;
        }

        void element::copyFrom(const element& other)
        {
            // Copy the name, body, attributes and attribute-replacement-character
            strName         = other.strName;
            body            = other.body;
            mapAttrs        = other.mapAttrs;
            chrReplacement  = other.chrReplacement;

            // Clear all children in this element
            children.clear();
            // And copy the children of the other
            for(childList::const_iterator pos = other.children.begin(); pos != other.children.end(); ++pos)
                children.append(*pos);
        }

    // Function to write a element to an ostream (friend of element)
    std::ostream& operator<<(std::ostream& out, const element& t)
    {
        // Open the element and write the name
        out<<'<'<<t.strName;

        // Write any attributes to the stream
        for(std::map<std::string, std::string>::const_iterator pos = t.mapAttrs.begin(); pos != t.mapAttrs.end(); ++pos)
            out<<' '<<pos->first<<"=\""<<toXmlEntities(pos->second)<<'"';

        // Close the opening element, and write the body to the stream
        out<<'>'<<toXmlEntities(t.body);

        // Write all children to the stream
        for(std::list<element>::const_iterator pos = t.children.begin(); pos != t.children.end(); ++pos)
            out<<*pos;

        // Write the closing element to the stream
        out<<"</"<<t.strName<<'>';

        // Return the stream
        return out;
    }

    // Function to validate a name
    bool validateName(const std::string& name)
    {
        // A name may not be empty or start with "xml" (case insensitive)
        if(name.length() == 0 || (name.length() >= 3 && std::tolower(name[0]) == 'x' && std::tolower(name[1]) == 'm' && std::tolower(name[2]) == 'l'))
            return false;

        for(std::string::const_iterator pos = name.begin(); pos != name.end(); ++pos)
        {
            if(pos == name.begin())
            {
                // A name may only start with an alphabetical character
                if(!std::isalpha(*pos))
                    return false;
            }
            // A name can only contain alphanumerical characters or punctation characters
            // But it may not contain any xml-reserved characters (i.e. <>&'")
            else if((!std::isalnum(*pos) && !std::ispunct(*pos)) || (*pos == '<' || *pos == '>' || *pos == '&' || *pos == '\'' || *pos =='"'))
                return false;
        }

        // The has passed all of the tests, so it's valid
        return true;
    }

    // Function to convert text to XML-entities
    std::string toXmlEntities(const std::string& str)
    {
        std::string out = "";   // This string will hold the result

        for(std::string::const_iterator pos = str.begin(); pos != str.end(); ++pos)
        {
            switch(*pos)
            {
                // If the current character is a reserved XML character, replace it by it's entity
                // Otherwise, just add the character to the result-string
                case '<':   out += "&lt;";      break;
                case '>':   out += "&gt;";      break;
                case '&':   out += "&amp;";     break;
                case '\'':  out += "&apos;";    break;
                case '"':   out += "&quot;";    break;
                default:    out += *pos;        break;
            }
        }
        return out;             // Return the result
    }

    // Function to convert XML-entities to normal text
    std::string fromXmlEntities(const std::string& str)
    {
        std::string out = "";                       // This string will hold the result
        std::string buffer = "";                    // This string will be used as buffer to temporarily store an entity

        // Loop through the whole string 'str'
        for(std::string::const_iterator pos = str.begin(); pos != str.end(); ++pos)
        {
            if(*pos == '&')                         // If we're at the start of an entity
            {
                out += buffer;                      // Store any previous entity data
                buffer = "&";                       // Wipe the buffer and store the beginning '&' in it
            }
            else if(buffer == "")                   // If we're not at the start of an entity and also not in the middle of it
                out += *pos;                        // Just ad the character to the result-string
            else                                    // If we're in the middle of an entity
            {
                buffer += *pos;                     // Add the current character to the buffer
                if(*pos == ';')                     // If it was an closing ';'
                {
                    if(buffer == "&lt;")            // Check which entity it was and add the right character to the result-string
                        out += '<';
                    else if(buffer == "&gt;")
                        out += '>';
                    else if(buffer == "&amp;")
                        out += '&';
                    else if(buffer == "&apos;")
                        out += '\'';
                    else if(buffer == "&quot;")
                        out += '"';
                    else                            // If it isn't a known entity, just add the whole buffer to the result-string
                        out += buffer;
                    buffer = "";                    // Wipe the buffer
                }
            }
        }
        out += buffer;                              // If there was some data left in the buffer, it should be added to the result-string
        return out;                                 // Return the result
    }

} // namespace xml
