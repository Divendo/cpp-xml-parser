**xml::element**

The xml::element class represents an element of a xml-document.




## std::string body ##
The body of the element. This simply is all data in the element, which doesn't belong to a child. That's whitespaces included as well!

## xml::childList children ##
A list of all of the children of this element, see [xml::childList](xmlChildList.md) for more info.

## element(const std::string& elementName, const std::string& body) ##
Default constructor. Constructs the element using _elementName_ as name and _body_ as body. _elementName_ defaults to _"tag"_, also if an invalid name is specified the name is changed to _"tag"_

## bool rename(const std::string& newName) ##
Changes the name of the element, returns true if changed succesful and false otherwise (i.e. the new name wasn't valid)

## std::string name() const ##
Returns the current name

## element`*` parent() ##
Returns a pointer to the parent of this element. If this element doesn't  have a parent, 0 is returned.

## const element`*` parent() const ##
Returns a const pointer to the parent of this element. If this element doesn't  have a parent, 0 is returned.

## bool setReplacementChar(const char& newChr) ##
Changes the _attribute-replacement-character_, any invalid characters in an attribute's name are replaced by this character. This function only changes the _attribute-replacement-character_ for this element. For others the default is still used. If _newChr_ isn't a valid character, false is returned (and the _attribute-replacement-character_ isn't changed) otherwise true is returned.

## char replacementChar() const ##
Returns the _attribute-replacement-character_ used for this element, if no _attribute-replacement-character_ is given the default _attribute-replacement-character_ is returned.

## void useDefault(const bool& use) ##
Whether to use the default _attribute-replacement-character_ or not.

## static bool setDefaultReplacementChar(const char& newChr) ##
**Static function**, this function changes the default _attribute-replacement-character_. By default this is `'_'`. If _newChr_ isn't a valid character, false is returned (and the _attribute-replacement-character_ isn't changed) otherwise true is returned.

## static char defaultReplacementChar(); ##
**Static function**, returns the default _attribute-replacement-character_.

## iterator begin() and const\_iterator begin() const ##
Returns a `iterator` or `const_iterator` to the begin of [std::map](http://www.cplusplus.com/reference/stl/map/) of attributes. This is a `std::map<std::string, std::string>::iterator` or `std::map<std::string, std::string>::const_iterator`

## iterator end() and const\_iterator end() const ##
Returns a `iterator` or `const_iterator` to the end of [std::map](http://www.cplusplus.com/reference/stl/map/) of attributes. This is a `std::map<std::string, std::string>::iterator` or `std::map<std::string, std::string>::const_iterator`

## reverse\_iterator rbegin() and const\_reverse\_iterator rbegin() const ##
Returns a `iterator` or `const_iterator` to the begin of [std::map](http://www.cplusplus.com/reference/stl/map/) of attributes. This is a `std::map<std::string, std::string>::reverse_iterator` or `std::map<std::string, std::string>::const_reverse_iterator`

## reverse\_iterator rend() and const\_reverse\_iterator rend() const ##
Returns a `reverse_iterator` or `const_reverse_iterator` to the end of [std::map](http://www.cplusplus.com/reference/stl/map/) of attributes. This is a `std::map<std::string, std::string>::reverse_iterator` or `std::map<std::string, std::string>::const_reverse_iterator`

## std::string getAttribute(const std::string attrName) const ##
Get the value of an attribute by name, if the attribute doesn't exist an empty string is returned.

## std::string operator[.md](.md)(const std::string& attrName) const ##
Get the value of an attribute by name, if the attribute doesn't exist an empty string is returned.

## std::string& operator[.md](.md)(const std::string& attrName); ##
Get a reference to the value of an attribute by name, if the attribute doesn't exist it's created and a reference to it's value (an empty string) is returned. Any illegal characters in the name are replaced by the _attribute-replacement-character_.

## void setAttribute(const std::string& attrName, const std::string& newValue) ##
Change the value of an attribute, if the attribute didn't exist it's created. Any illegal characters in the name are replaced by the _attribute-replacement-character_.

## bool attributeExists(const std::string& attrName) const ##
Check if the attribute with the given name exists. Returns true if it does, and false otherwise.

## bool removeAttribute(const std::string& attrName) ##
Removes the attribute with the given name. Returns true if succesful, false otherwise (i.e. the attribute didn't exist)

## std::string toString() const ##
Returns a string containing the xml-code for the element.

## friend std::ostream& operator<<(std::ostream& out, const element& t) ##
This is a friend function, and not a member of the class. This can be used to write the element as xml-code to an output stream.