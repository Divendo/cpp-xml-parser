**xml::parseError**

The xml::parseError contains info about an error which occurred while parsing.




## enum errorType ##
This enumeration can have 5 different values:
| **Value** | **Meaning** |
|:----------|:------------|
| unknown | An unknown error occurred |
| unexpectedEnd | The input data-stream ended unexpectedly, i.e. the xml-document to read wasn't a complete xml-document |
| readingError | The error occurred while reading data from the stream |
| invalidTagname | An invalid tag name was discovered ([info](#std::string_info.md) will hold the name of the tag) |
| unclosedElement | An element wasn't closed properly ([info](#std::string_info.md) will hold the name of the unclosed tag) |

## errorType type ##
The type of the error.

## int line ##
The line where the error occurred, if not applicable this is -1.

## int pos ##
The position where the error occurred, if not applicable this is -1.

## std::string info ##
Extra info, only used if [type](#errorType_type.md) is `invalidTagname` or `unclosedElement`.

## parseError(const errorType& type, const int& line, const int& pos, const std::string& info) ##
Default constructor. Initialises [type](#errorType_type.md) with _type_ (default to `unknown`), [line](#int_line.md) with _line_ (defaults to `-1`), [pos](#int_pos.md) with _pos_ (defaults to `-1`) and [info](#std::string_info.md) with _info_ (defaults to `""`)