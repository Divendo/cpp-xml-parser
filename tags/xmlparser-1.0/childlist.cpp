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

#include "element.h"

namespace xml
{
    // Public:
        childList::iterator childList::begin()
        { return std::list<element>::begin(); }
        childList::const_iterator childList::begin() const
        { return std::list<element>::begin(); }
        childList::iterator childList::end()
        { return std::list<element>::end(); }
        childList::const_iterator childList::end() const
        { return std::list<element>::end(); }

        childList::reverse_iterator childList::rbegin()
        { return std::list<element>::rbegin(); }
        childList::const_reverse_iterator childList::rbegin() const
        { return std::list<element>::rbegin(); }
        childList::reverse_iterator childList::rend()
        { return std::list<element>::rend(); }
        childList::const_reverse_iterator childList::rend() const
        { return std::list<element>::rend(); }

        bool childList::empty() const
        { return std::list<element>::empty(); }
        childList::size_type childList::size() const
        { return std::list<element>::size(); }

        element& childList::front()
        { return std::list<element>::front(); }
        const element& childList::front() const
        { return std::list<element>::front(); }
        element& childList::back()
        { return std::list<element>::back(); }
        const element& childList::back() const
        { return std::list<element>::back(); }

        void childList::clear()
        { std::list<element>::clear(); }

        element* childList::append(const std::string& childName, const std::string& childBody)
        { return append(element(childName, childBody)); }
        element* childList::append(const element& child)
        {
            std::list<element>::push_back(child);
            std::list<element>::back().elementParent = elementParent;
            return &std::list<element>::back();
        }

        int childList::remove(const std::string& childName)
        {
            int count = 0;
            if(!validateName(childName)) return count;
            for(std::list<element>::iterator pos = std::list<element>::begin(); pos != std::list<element>::end(); ++pos)
            {
                if(pos->name() == childName)
                {
                    pos = std::list<element>::erase(pos);
                    ++count;
                }
            }
            return count;
        }

        int childList::removeAll(const std::string& childName)
        {
            int count = 0;
            if(!validateName(childName)) return count;
            for(std::list<element>::iterator pos = std::list<element>::begin(); pos != std::list<element>::end(); ++pos)
            {
                if(pos->name() == childName)
                {
                    pos = std::list<element>::erase(pos);
                    ++count;
                }
                else
                    count += pos->children.removeAll(childName);
            }
            return count;
        }

        childList::iterator childList::remove(const iterator& it)
        { return std::list<element>::erase(it); }
        childList::iterator childList::remove(const iterator& first, const iterator& last)
        { return std::list<element>::erase(first, last); }

        std::list<element*> childList::getByName(const std::string& childName)
        {
            std::list<element*> out;
            if(!validateName(childName)) return out;
            for(std::list<element>::iterator pos = std::list<element>::begin(); pos != std::list<element>::end(); ++pos)
                if(pos->name() == childName) out.push_back(&(*pos));
            return out;
        }

        std::list<const element*> childList::getByName(const std::string& childName) const
        {
            std::list<const element*> out;
            if(!validateName(childName)) return out;
            for(std::list<element>::const_iterator pos = std::list<element>::begin(); pos != std::list<element>::end(); ++pos)
                if(pos->name() == childName) out.push_back(&(*pos));
            return out;
        }

        std::list<element*> childList::getAllByName(const std::string& childName)
        {
            std::list<element*> out;
            std::list<element*> tmp;
            if(!validateName(childName)) return out;
            for(std::list<element>::iterator pos = std::list<element>::begin(); pos != std::list<element>::end(); ++pos)
            {
                if(pos->name() == childName) out.push_back(&(*pos));
                tmp = pos->children.getAllByName(childName);
                out.insert(out.end(), tmp.begin(), tmp.end());
            }
            return out;
        }

        std::list<const element*> childList::getAllByName(const std::string& childName) const
        {
            std::list<const element*> out;
            std::list<const element*> tmp;
            if(!validateName(childName)) return out;
            for(std::list<element>::const_iterator pos = std::list<element>::begin(); pos != std::list<element>::end(); ++pos)
            {
                if(pos->name() == childName) out.push_back(&(*pos));
                tmp = pos->children.getAllByName(childName);
                out.insert(out.end(), tmp.begin(), tmp.end());
            }
            return out;
        }

        element* childList::getFirstByName(const std::string& childName)
        {
            if(!validateName(childName)) return 0;
            for(std::list<element>::iterator pos = std::list<element>::begin(); pos != std::list<element>::end(); ++pos)
                if(pos->name() == childName) return &(*pos);
            return 0;
        }

        const element* childList::getFirstByName(const std::string& childName) const
        {
            if(!validateName(childName)) return 0;
            for(std::list<element>::const_iterator pos = std::list<element>::begin(); pos != std::list<element>::end(); ++pos)
                if(pos->name() == childName) return &(*pos);
            return 0;
        }

        element* childList::getFirstOfAllByName(const std::string& childName)
        {
            element* tmp = 0;
            if(!validateName(childName)) return 0;
            for(std::list<element>::iterator pos = std::list<element>::begin(); pos != std::list<element>::end(); ++pos)
            {
                if(pos->name() == childName) return &(*pos);
                if((tmp = pos->children.getFirstOfAllByName(childName)) != 0)
                    return tmp;
            }
            return 0;
        }
        const element* childList::getFirstOfAllByName(const std::string& childName) const
        {
            const element* tmp = 0;
            if(!validateName(childName)) return 0;
            for(std::list<element>::const_iterator pos = std::list<element>::begin(); pos != std::list<element>::end(); ++pos)
            {
                if(pos->name() == childName) return &(*pos);
                if((tmp = pos->children.getFirstOfAllByName(childName)) != 0)
                    return tmp;
            }
            return 0;
        }

    // Private:
        childList::childList(element* eleParent)
            : elementParent(eleParent) {}

} // namespace xml
