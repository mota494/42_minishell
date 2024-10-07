# Functions HOORAY

```c

#include <unistd.h>
#include <stdlib.h>
#include <linux/limits.h>

char *getcwd(char *buffer, size_t size); //returns the current directory, MAX_PATH can be used as size

int chdir(const char *prt); //changes the current working directory considering the path (*prt) given, return 0 on sucess and -1 if an errors occurs

int access(const char *path, int amode); 
/*checks if a file or directory can be accessed according to the mode given
: F_OK, tests for file existence; R_OK tests for read permission; W_OK tests for writing permission and X_OK test for execution permission*/

char *getenv(const char *name); //searches for the variable with *name and returns it's value string

```

# Usefull links

[Blackberry's QNX developers documentation](https://www.qnx.com/developers/docs/7.1/#com.qnx.doc.neutrino.lib_ref/topic/about.html)

[Jarret B Bash documentation](https://www.linux.org/threads/bash-03-%E2%80%93-command-line-processing.38676/)

[GNU Bash Manual](https://www.gnu.org/software/bash/manual/html_node/Shell-Parameter-Expansion.html)

[User and built-in variables](https://pressbooks.senecapolytechnic.ca/uli101/chapter/variables-in-shell-scripting/)
