# Conventions for developing code for ATRIAS #

ROS srvs should be defined in respective packages, not in atrias\_msgs. ROS srv names should be in CamelCase.

Trailing whitespace is evil.

Opening curly brackets for C functions go on the same line. Closing brackets go on its own line, aligned with the function statement. (This is pretty unclear and could be worded better. Ask me in person and I'll explain.)

There should be three spaces between the end of code and the beginning of an inline comment.

## Modelines ##
Each source file should contain a Vim modeline (at the end of the file, so it's out of the way) that tells Vim what indentation style to use.

For space-based indentation, use:
```
// vim: expandtab:sts=4
```

For tab-based indentation, use:
```
// vim: noexpandtab
```

## Commenting Convention ##
We are using [Doxygen](http://www.stack.nl/~dimitri/doxygen/) to document the code base. Doxygen is a comment parser that will generate HTML (or LaTeX) output similar to JavaDoc. This is an example of what a Doxygen HTML file can look like [Asterisk code documentation](http://www.asterisk.org/doxygen/trunk/acl_8c.html).

Doxygen only parses special comment blocks. There are several ways to make a special comment block, but for the sake of constancy we will be using the JavaDoc comment block style as shown below.

```
/**
 * this comment will be parsed by Doxygen
 */
```

Regular comments are not parsed by Doxygen.
```
/*
 * this comment will _NOT_ be parsed by Doxygen
 */

// this comment will _NOT_ be parsed by Doxygen
```


### Parts of code that should be commented ###
  * head of files
  * global/class wide variables
  * structs and enums
  * functions and macros

### Head of File ###
```
/** @file
 *  @author Mr. Foo Bar III
 *  @brief A short description of what the file does.
 *
 *  A more detailed description starts here about the file.
 */
#include <stdio.h>
int main(void) {return 0;}
```

### Global/Class Wide Variables ###
```
/**
 * @brief The total number of packets that have been sent and/or recieved by
 * the control module.
 */
static unsigned long int packet_count;
```

### Structs and Enums ###
Doxygen comments that go after the block they are describing must use the < character.

```
/**
 * @brief Each supported file format is described by the following fields.
 */
struct ast_format {
	char name[80];		/**< Name of format */
	int format;		/**< Format of frames it uses/provides (one only) */
};

/** 
 *  @brief An enum description
 *  
 *  More detailed enum description.
 */

enum TEnum { 
    TVal1, /**< enum value TVal1. */  
    TVal2, /**< enum value TVal2. */  
    TVal3  /**< enum value TVal3. */  
} 
```

### Functions and Macros ###
HTML tags, @note, and @code can be added for extra output and style in the generated HTML files.
```
/** @brief Add ASTOBJ components to a struct (with locking support).
 *
 * @param type The datatype of the object.
 * @param namelen The length to make the name char array.
 * @param hashes The number of containers the object can be present in.
 *
 * This macro adds components to a struct to make it an ASTOBJ and includes
 * support for locking.
 *
 * <b>Sample Usage:</b>
 * @code
 * struct sample_struct {
 *    ASTOBJ_COMPONENTS_FULL(struct sample_struct,1,1);
 * };
 * @endcode
 */
#define ASTOBJ_COMPONENTS_FULL(type,namelen,hashes) \
	ASTOBJ_COMPONENTS_NOLOCK_FULL(type,namelen,hashes); \
	ast_mutex_t _lock;

/** 
 * @brief Determines the highest message number in use for a given user and mailbox folder.
 * @param vmu 
 * @param dir the folder the mailbox folder to look for messages. Used to construct the SQL where clause.
 *
 * This method is used when mailboxes are stored on the filesystem. (not ODBC and not IMAP).
 * Typical use to set the msgnum would be to take the value returned from this method and add one to it.
 *
 * @note Should always be called with a lock already set on dir.
 * @return the value of zero or greater to indicate the last message index in use, -1 to indicate none.
 */
static int last_message_index(struct ast_vm_user *vmu, char *dir);
```

### Where to Put Comments ###
Put doxygen comments where the code block is defined. This can be in a .h or .c file. Macros will typically be defined in a .h file and functions in .c files.