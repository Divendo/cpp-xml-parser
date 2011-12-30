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

#ifndef PARSEERROR_H
#define PARSEERROR_H

#include <string>

namespace xml
{
    class parseError
    {
        public:
            enum errorType
            {
                unknown,            // An unknown error occurred
                unexpectedEnd,      // The input data-stream ended unexpectedly, i.e. the xml-document to read wasn't a complete xml-document
                readingError,       // The error occurred while reading data from the stream
                invalidTagname,     // An invalid tag name was discovered (info will hold the name of the tag)
                unclosedElement     // An element wasn't closed properly (info will hold the name of the unclosed tag)
            };

            errorType type;         // The type of the error
            int line;               // The line where the error occurred, if not applicable this is -1
            int pos;                // The position where the error occurred, if not applicable this is -1
            std::string info;       // Extra info

            parseError(const errorType& type = unknown, const int& line = -1, const int& pos = -1, const std::string& info = "");
    };

} // namespace xml

#endif // PARSEERROR_H
