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

#ifndef CHILDRENLIST_H
#define CHILDRENLIST_H

#include <list>
#include <string>

namespace xml
{
    // Forward declaration for the element class
    class element;

    // For the list
    class childList : private std::list<element>
    {
        public:
            // Make the element class a friend, so it can access the private members of this class
            friend class element;

            // Make the types visible
            typedef std::list<element>::iterator iterator;
            typedef std::list<element>::const_iterator const_iterator;
            typedef std::list<element>::reverse_iterator reverse_iterator;
            typedef std::list<element>::const_reverse_iterator const_reverse_iterator;

            // Make some members from std::list<element> public
            iterator begin();
            const_iterator begin() const;
            iterator end();
            const_iterator end() const;

            reverse_iterator rbegin();
            const_reverse_iterator rbegin() const;
            reverse_iterator rend();
            const_reverse_iterator rend() const;

            bool empty() const;
            size_type size() const;

            element& front();
            const element& front() const;
            element& back();
            const element& back() const;

            void clear();

            // Append a child with the given name and body
            // The appended child will be returned
            element* append(const std::string& childName, const std::string& childBody = "");
            element* append(const element& child);

            // Remove all direct children with the given name, returns the number of removed children
            int remove(const std::string& childName);

            // Remove all (direct and indirect) children with the given name, returns the number of removed children
            int removeAll(const std::string& childName);

            // Remove the child pointed by the iterator, returns an iterator pointing to the new location of the element that followed the removed element
            iterator remove(const iterator& it);
            // Remove the children in the range [first, last), returns an iterator pointing to the new location of the element that followed the last removed element
            iterator remove(const iterator& first, const iterator& last);

            // Get all direct children with the given name
            std::list<element*> getByName(const std::string& childName);
            std::list<const element*> getByName(const std::string& childName) const;

            // Get all (direct and indirect) children with the given name
            std::list<element*> getAllByName(const std::string& childName);
            std::list<const element*> getAllByName(const std::string& childName) const;

            // Get the first direct child with the given name, returns 0 if there wasn't a child with the given name
            element* getFirstByName(const std::string& childName);
            const element* getFirstByName(const std::string& childName) const;

            // Get the first of all (direct and indirect) children with the given name, returns 0 if there wasn't a child with the given name
            element* getFirstOfAllByName(const std::string& childName);
            const element* getFirstOfAllByName(const std::string& childName) const;

        private:
            // Constructor, private because only an element may create an instance of this class
            childList(element* eleParent);

            // The parent element, this is the parent of all of the elements in this list
            element* elementParent;
    };

} // namespace xml

#endif // CHILDRENLIST_H
