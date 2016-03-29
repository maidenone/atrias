# Syntax #

//!

@brief fileDescription

//! Description of the variable

  * Tags for files:
    * @file fileName
    * @author authorName
      * Include one @author tag for each author.

  * Tags for functions:
    * @fn functionName
    * @param parameterName parameterDescription
      * Include one @param tag for each parameter.
    * @return returnDescription
    * @see functionName
      * Include one @see tag for each function to link to.

  * Tags for classes/structs:
    * @class className

  * Tags for enumerations:
    * TODO

  * Tags for #define
    * @def

## Example File ##
```
//! @file example.cpp
//! @author The First Author
//! @author The Second Author
//! @brief A brief description of this file.
//!
//! A longer, detailed description of this file.

//! @brief A brief description of the #define
//!
//! A longer, detailed description of the #define.
#define something 0

//! @typedef

//! @enum

//! @struct

//! @class



#include <cstdlib>

using namespace std;

//! @fn main
//! @param argc Required command line argument. Not used.
//! @param argv Required command line argument. Not used.
//! @return A return value of 0 signals successful execution. A non-zero return value signals an error.
//! @brief Prints "Hello, World." to the console.
int main(int argc, char** argv)
{
    cout << "Hello, World." << endl;
}
```


# Creating the HTML files #
creating the HTML files is  one of the most simple parts of the whole process.

First open terminal and navigate to the directory where your code is. if you need help with this check

http://www.unixguide.net/linux/linuxshortcuts.shtml

and see the "7.3 Basic operations" section.

Once in the desired directory type
```
doxygen -g <config-file>
```
into terminal. This creates a template configuration file that can be easily modified to fit your preferences.

Once you have your preferences set up (by editing the configuration file),
type
```
doxygen <config_file>
```
in terminal.

### Acessing the HTML File ###
Now that you have created the HTML data files open the folder labeled "HTML" and click on the "index" file.



## This is a rudimentary tutorial and does NOT include all of Doxygen's features, for full information visit www.Doxygen.org and click on the "manual" tab on the left side of the screen. Also you should refer to this page in the event of problems with the installation or any part of this Wiki. ##


```
sudo apt-get install doxygen
```