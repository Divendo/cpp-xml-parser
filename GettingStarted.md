# Introduction #

Before reading this guide, you're required to have succesfully installed `<`xmlParser`>`. This isn't very hard to do, so if you haven't please go to [this page](Home#Installing.md).
To understand the contents of this page you're required to know XML.


# Starting the project #
As always in C++, you start your project by creating a _main.cpp_ file. After you've done this, copy all files from `<`xmlParser`>` to your project's location and add them to your project. Now include the file _xml_ in _main.cpp_, and for this tutorial we'll also need `<string>`, `<fstream>` and `<iostream>`. So we've got:
```
#include "xml"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

int main()
{
}
```

# The XML file #
In this tutorial we're going to read a note which is stored in XML. So create a file called _note.xml_ in the same directory where you will later execute your compiled program. Put the following XML-code in _note.xml_:
```
<?xml version="1.0" encoding="ISO-8859-1"?>
<note>
 <sender>Captain Kirk</sender>
 <receiver>Scotty</receiver>
 <message>Beam me up!</message>
</note>
```

# Creating the program #

## Reading the document ##
Reading the XML-document is really simple. Just create a [xml::document](xmlDocument.md), open the file containing the XML-code and read it.
```
// Create an instance of xml::document, then open the file and read the contents
xml::document doc;                          
ifstream file("note.xml");
file>>doc;
file.close();
```

## Showing it's contents ##
Now we're going to show the contents of the file.
```
// From the document, we need the root element
// From the root element we need one of it's children
// From it's children we want the first one who's named "sender"
xml::element* sender = doc.root.children.getFirstByName("sender");
cout<<sender->body<<" said to ";
```

Of course you can use the same method again to retrieve the other elements, but since this tutorial is made to show how `<`xmlParser`>` works we'll use another method.
```
// Of course we can use the same way of retrieving the data
// This is just to show another possibility
// Now we're not retrieving the root element via the document
// We're retrieving it using the parent() function of the sender element (the root element is it's parent)
xml::element* receiver = sender->parent()->children.getFirstByName("receiver");
cout<<receiver->body<<": \"";
```

As you may have noticed, temporarily storing the pointer to the element isn't necessary:
```
// We'll retrieve the last element and use it in one statement
cout<<doc.root.children.getFirstByName("message")->body<<"\"\n";
```

## Complete code ##

The complete code will be:
```
#include "xml"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    // Create an instance of xml::document, then open the file and read the contents
    xml::document doc;                          
    ifstream file("note.xml");
    file>>doc;
    file.close();

    // From the document, we need the root element
    // From the root element we need one of it's children
    // From it's children we want the first one who's named "sender"
    xml::element* sender = doc.root.children.getFirstByName("sender");
    cout<<sender->body<<" said to ";

    // Of course we can use the same way of retrieving the data
    // This is just to show another possibility
    // Now we're not retrieving the root element via the document
    // We're retrieving it using the parent() function of the sender element (the root element is it's parent)
    xml::element* receiver = sender->parent()->children.getFirstByName("receiver");
    cout<<receiver->body<<": \"";

    // We'll retrieve the last element and use it in one statement
    cout<<doc.root.children.getFirstByName("message")->body<<"\"\n";

    // Wait for an enter, in case the program isn't started from commandline
    cin.get();
    return 0;
}
```