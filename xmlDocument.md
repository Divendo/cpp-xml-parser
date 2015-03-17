**xml::document**

The xml::document class represents the entire xml-document. You've acces to alle elements in the document through the [root element](#xml::element_root.md).




## xml::element root ##
This is the root element of the document. See [xml::element](xmlElement.md) for more info about the [xml::element](xmlElement.md) class.

## document(const element& root, const std::string& initEncoding) ##
Default constructor of the document class, this initialises the [root element](#xml::element_root.md) with _root_ and the encoding with _initEncoding_. The root element defaults to an empty element named _"root"_, the encoding defaults to _"ISO-8859-1"_.

## document(const std::string& rootName, const std::string& initEncoding) ##
Another constructor for the document class. This one initialises the root element with _rootName_ as name. The encoding is initialised with _initEncoding_, which defaults to _"ISO-8859-1"_.

## std::string toString() const ##
Convert the entire XML document to a string containing the xml code.

## void setEncoding(const std::string& newEncoding) ##
Changes the encoding attribute of the document. The encoding may not be empty, if it is it will automatically be changed to _"ISO-8859-1"_.

## std::string encoding() const ##
Get the value of the encoding attribute of the document.

## void parse(std::istream& in) throw(parseError) ##
Parse the document from the given stream. This function can throw a [xml::parseError](xmlParseError.md) when something goes wrong.

## void parse(const std::string& str) throw(parseError) ##
Parse the document from the given string. This function can throw a [xml::parseError](xmlParseError.md) when something goes wrong.

## friend std::ostream& operator<<(std::ostream& out, const document& doc) ##
This is a friend function, and not a member of the class. This can be used to write the entire document as xml-code to an output stream.