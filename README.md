# t_error
A lightweight error/warning/debug assertion library in C++11
```
/* By BC van Zuiden -- Leiden, July 2016 */
/* Probably very buggy USE AT OWN RISK this will brick everything you own */
/* NOBODY but YOU is liable for anything that happened in result of using this */
/* WARNING: DON'T RUN THIS PROGRAM THIS WILL DESTROY YOUR COMPUTER AND/OR HOUSE */
/* Any copyrighted piece of code within this code is NOT mine */
/* Inclusion of that code is forced upon me by a scary anonymous guy with a gun*/
/* https://github.com/originalsouth/t_error */
/* Please do not remove this comment from the source*/
```
### About
t_error helps you assert your error/warning/debug messages when you want to in a customizable fashion. 

Feel free to reuse and contribute, pull requests are very welcome!
This code is (and forever will be) a work in progress.

### Todo
* Document
* Improve customizability 

### Usage
Include t_error.h in your project, nothing much you need to do.
To assert an error in your code:
```
...
ERROR("Some error nr. %d",91);
...
```
To assert a warning in your code:
```
...
WARNING("Some warning nr. %d",92);
...
```
To print debug messages in your code:
```
...
DEBUG(0,"Some level 0 debug message nr. %d",93);
DEBUG(1,"Some level 1 debug message nr. %d",94);
...
```
Where 0 is the debug level.
By default errors and warnings are printed to stderr.
Debug messages are printed to stdout.
In both cases file pointer can be assigned by the user.
By default output is colored.
You can see a working example in t_error.cc

### Building
The file t_error.cc is an example file run something like:
```
make
```
You can run a demo by typing:
```
make demo
```
To clean run:
```
make clean
```
