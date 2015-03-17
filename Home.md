# Introduction #

This documentation explains how to use `<`xmlParser`>`


# Installing #

To start using `<`xmlParser`>`, download the latest version of the code at the [download page](http://code.google.com/p/cpp-xml-parser/downloads). To start using it, simply extract all the files to your harddrive. It's the easiest to place them in the same folder as your project, or a folder in that folder (e.g. create a folder called _xmlparser_ in your project folder, and place the files there). Then add the files to your project, how to do this differs per IDE. Then include the file named _"xml"_ in your code, and you're ready to use `<`xmlParser`>`!

# Example code #
Do you want to know how using `<`xmlParser`>` looks like, before you download it? This is how:
```
// Including some standard C++ libraries
#include <iostream>
#include <fstream>
// Including <xmlParser> is as easy as this
#include "xmlparser/xml"

= Getting started =
To get started using 

using namespace std;

int main()
{
    // Open the xml-document file, read it's contents and close the file
    ifstream inFile("document.xml");
    xml::document doc;
    inFile>>doc;
    inFile.close();

    // Add an element to the document, then add some children to that element
    xml::element* date = doc.root.children.append("date");
    date->setAttribute("what", "New year's day of 2012");
    date->children.append("year", "2012");
    date->children.append("month", "01");
    date->children.append("day", "01");

    // Now we're done editting the document, write back the changes to the file
    ofstream outFile("document.xml");
    outFile<<doc;
    outFile.close();

    // Show what we did, wait for an enter and then close the application
    cout<<"The current date has been added to the xml-document!\n";
    cin.get();
    return 0;
}
```

# Getting started #
To get started using `<`xmlParser`>`, read the [getting started](GettingStarted.md) wiki-page.

# Namespace #
Everything in this library is written inside the namespace _xml_.

# Note before using #
CDATA ([issue 1](https://code.google.com/p/cpp-xml-parser/issues/detail?id=1)) and comments ([issue 2](https://code.google.com/p/cpp-xml-parser/issues/detail?id=2)) aren't supported yet