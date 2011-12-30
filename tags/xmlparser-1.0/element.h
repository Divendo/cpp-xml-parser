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

#ifndef TAG_H
#define TAG_H

#include <string>
#include <map>
#include <ostream>

#include "childlist.h"

namespace xml
{
    class element
    {
        public:
            // Make the childList class a friend, so it can access the private members of this class
            friend class childList;

            // Typedef the attribute map iterators
            typedef std::map<std::string, std::string>::iterator iterator;
            typedef std::map<std::string, std::string>::const_iterator const_iterator;
            typedef std::map<std::string, std::string>::reverse_iterator reverse_iterator;
            typedef std::map<std::string, std::string>::const_reverse_iterator const_reverse_iterator;

            // Public members variables
            std::string body;                                           // Body of the element
            childList children;                                         // Children of the element

            // Constructor
            // If the given elementName isn't valid or if there isn't a elementName given, "tag" will be used
            element(const std::string& elementName = "tag", const std::string& body = "");

            // Copy constructor
            element(const element& other);
            // Assignment operator
            element& operator=(const element& other);

            // Get or set the name of the element
            bool rename(const std::string& newName);                    // Returns true if the name was valid, otherwise it returns false
            std::string name() const;                                   // Returns the name of the element

            // Get the parent of this element
            element* parent();
            const element* parent() const;

            // Illegal characters in the name of an attribute will be replaced by the attribute-replacement-character
            bool setReplacementChar(const char& newChr);                // Change the attribute-replacement-character to the given character
                                                                        // Returns false if the given character isn't valid (i.e. it isn't a valid xml name character, or xml names can not always start with it)
            char replacementChar() const;                               // Returns the the attribute-replacement-character
            void useDefault(const bool& use);                           // Whether or not to use the default attribute-replacement-character
                                                                        // The default attribute-replacement-character is used by all elements by default
            // Set or get the default character
            static bool setDefaultReplacementChar(const char& newChr);  // Change the default attribute-replacement-character
                                                                        // Returns false if the given character isn't valid (i.e. it isn't a valid xml name character, or xml names can not always start with it)
            static char defaultReplacementChar();                       // Returns the default attribute-replacement-character

            // Iterators for the attributes
            iterator begin();
            const_iterator begin() const;
            iterator end();
            const_iterator end() const;

            // Reverse iterators for the attributes
            reverse_iterator rbegin();
            const_reverse_iterator rbegin() const;
            reverse_iterator rend();
            const_reverse_iterator rend() const;

            // Get attribute values, if the attribute doesn't exist an empty string is returned
            std::string getAttribute(const std::string attrName) const; // Get the value of the attribute with the given name
            std::string operator[](const std::string& attrName) const;  // Get the value of the attribute with the given name
            std::string& operator[](const std::string& attrName);       // Get a reference to the value of the attribute with the given name
                                                                        // If the attribute doesn't exist, the function will create one with the given name
                                                                        // Any illegal characters in the name will be replaced by the attribute-replacement-character

            // Change the value of an attribute
            // If the attribute does not already exist, the function will try to create one
            // Any illegal characters in the name will be replaced by the attribute-replacement-character
            void setAttribute(const std::string& attrName, const std::string& newValue);

            // Checks if an attribute exists, returns true if so and false if not
            bool attributeExists(const std::string& attrName) const;

            // Remove an attribute, returns true if succesful and false if not (i.e. the attribute didn't exist)
            bool removeAttribute(const std::string& attrName);

            // Friend function to write the document as a string to a output stream
            friend std::ostream& operator<<(std::ostream& out, const element& t);

            // Function to convert the document to a string
            std::string toString() const;

        protected:
            // Static
                static char staticChrReplacement;                       // Default character to replace illegal characters in attributes' names with
                static bool validateReplacementChar(const char& chr);   // Returns true if the given character is a valid attribute-replacement-character, otherwise it returns false

            // Local
            std::string strName;                                        // Name of the element
            std::map<std::string, std::string> mapAttrs;                // Attributes of the element
            char chrReplacement;                                        // Character to replace illegal characters in attributes' names with
            element* elementParent;                                     // The parent of this element

            // Function to replace any illegal characters with the attribute-replacement-character
            std::string replaceIllegalChars(std::string str);

            // Function to copy from the data from another element to this element
            void copyFrom(const element& other);
    };

    // Function to validate a name
    bool validateName(const std::string& name);

    // Function to convert text to XML-entities
    std::string toXmlEntities(const std::string& str);

    // Function to convert XML-entities to normal text
    std::string fromXmlEntities(const std::string& str);

} // namespace xml

#endif // TAG_H
