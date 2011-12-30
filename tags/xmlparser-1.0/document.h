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

#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "element.h"
#include "parseerror.h"

#include <istream>
#include <ostream>

namespace xml
{

    class document
    {
        public:
            // The root element of the document
            element root;

            // Constructor
            // Initialise the root element with 'root'
            // Initialise the encoding with 'initEncodig', this may not be an empty string and may not contain a "
            document(const element& root = element("root"), const std::string& initEncoding = "ISO-8859-1");
            // Constructor
            // Initialise the root element with the given name
            // Initialise the encoding with the given encoding, this may not be an empty string and may not contain a "
            document(const std::string& rootName, const std::string& initEncoding = "ISO-8859-1");

            // Friend function to write the document as a string to a output stream
            friend std::ostream& operator<<(std::ostream& out, const document& doc);

            // Function to convert the document to a string
            std::string toString() const;

            // Change the encoding (it may not be an empty string and may not contain a ")
            void setEncoding(const std::string& newEncoding);

            // Get the encoding
            std::string encoding() const;

            // Read a xml document from an input stream
            void parse(std::istream& in) throw(parseError);

            // Read a xml document from the given string
            void parse(const std::string& str) throw(parseError);

        protected:
            // The encoding of the document
            std::string strEncoding;

        private:
            std::istream* parseStream;
            int parseLine;
            int parsePos;

            void parseDocumentStart() throw(parseError);            // Starts the parsing of a document, parses the start of the document (the <?xml?> tag)
            element parseElement() throw(parseError);               // Parses one element and returns the parsed element
                                                                    // This function assumes that the opening < has already been removed from the stream
    };

    // Function to read a document from an input stream
    std::istream& operator>>(std::istream& in, document& doc) throw(parseError);

} // namespace xml

#endif // DOCUMENT_H
