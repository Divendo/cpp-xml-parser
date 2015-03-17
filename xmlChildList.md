**xml::childList**

The xml::childList represents a list of [xml::element](xmlElement.md)s, being the children of another element. You can not construct an instance of this class yourself, only the [xml::element](xmlElement.md) class can (and only that class should be able to do so).




## iterator begin() and const\_iterator begin() const ##
Returns a `iterator` or `const_iterator` to the begin of [std::list](http://www.cplusplus.com/reference/stl/list/) of elements. This is a `std::list<xml::element>::iterator` or `std::list<xml::element>::const_iterator`

## iterator end() and const\_iterator end() const ##
Returns a `iterator` or `const_iterator` to the end of [std::list](http://www.cplusplus.com/reference/stl/list/) of elements. This is a `std::list<xml::element>::iterator` or `std::list<xml::element>::const_iterator`

## reverse\_iterator rbegin() and const\_reverse\_iterator rbegin() const ##
Returns a `iterator` or `const_iterator` to the begin of [std::list](http://www.cplusplus.com/reference/stl/list/) of elements. This is a `std::list<xml::element>::reverse_iterator` or `std::list<xml::element>::const_reverse_iterator`

## reverse\_iterator rend() and const\_reverse\_iterator rend() const ##
Returns a `reverse_iterator` or `const_reverse_iterator` to the end of [std::list](http://www.cplusplus.com/reference/stl/list/) of elements. This is a `std::list<xml::element>::reverse_iterator` or `std::list<xml::element>::const_reverse_iterator`

## bool empty() const ##
Returns true if the list is empty, otherwise false is returned.

## size\_type size() const ##
Returns the number of elements in the list.

## element& front() ##
Returns a reference to the first element in the list.

## const element& front() const ##
Returns a constant reference to the first element in the list.

## element& back() ##
Returns a reference to the first last in the list.

## const element& back() const ##
Returns a constant reference to the last element in the list.

## void clear() ##
Deletes all elements from the list.

## element**append(const std::string& childName, const std::string& childBody) ##
Appends a element to the list using _childName_ as name and _childBody_ as body (defaults to `""`). A pointer to the appended child is returned.**

## element**append(const element& child) ##
Appends a copy of the given element to the list. A pointer to the appended child is returned.**

## int remove(const std::string& childName) ##
Removes all direct children (not children of children) with the given name. Returns the number of removed children.

## int removeAll(const std::string& childName) ##
Removes all children (direct and indirect) with the given name. Returns the number of removed children.

## iterator remove(const iterator& it) ##
Removes the child pointer by the given iterator, returns an iterator pointing to the new location of the element that followed the removed element.

## iterator remove(const iterator& first, const iterator& last) ##
Removes the children in the range [first, last), returns an iterator pointing to the new location of the element that followed the last removed element.

## std::list<element`*`> getByName(const std::string& childName) ##
Get all direct children with the given name.

## std::list<const element`*`> getByName(const std::string& childName) const ##
Get all direct children with the given name.

## std::list<element`*`> getAllByName(const std::string& childName) ##
Get all (direct and indirect) children with the given name.

## std::list<const element`*`> getAllByName(const std::string& childName) const ##
Get all (direct and indirect) children with the given name.

## element`*` getFirstByName(const std::string& childName) ##
Get the first direct child with the given name, returns 0 if there wasn't a child with the given name.

## const element`*` getFirstByName(const std::string& childName) const ##
Get the first direct child with the given name, returns 0 if there wasn't a child with the given name.

## element`*` getFirstOfAllByName(const std::string& childName) ##
Get the first of all (direct and indirect) children with the given name, returns 0 if there wasn't a child with the given name.

## const element`*` getFirstOfAllByName(const std::string& childName) const ##
Get the first of all (direct and indirect) children with the given name, returns 0 if there wasn't a child with the given name