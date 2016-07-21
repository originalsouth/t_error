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
__ERROR__("Some error nr. %d",91);
...
```
To assert a warning in your code:
```
...
__WARNING__("Some warning nr. %d",92);
...
```
To print debug messages in your code:
```
...
__DEBUG__(0,"Some level 0 debug message nr. %d",93);
__DEBUG__(1,"Some level 1 debug message nr. %d",94);
...
```
Where initial integer is the debug level.
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
It should produce something like:
```
Normal
Hello World!

Assert errors
Hello World!
[ 0.000030871s ] t_error: t_error.cc:21 in main: Oh no! error #42 occured: The world stopped turning :(
t_error: caused the program to terminate.

Assert warnings (and errors)
[ 0.000020045s ] t_waring: t_error.cc:16 in main: You can try, but nobody is listening...
Hello World!
[ 0.000053081s ] t_error: t_error.cc:21 in main: Oh no! error #42 occured: The world stopped turning :(
t_error: caused the program to terminate.

Assert debug messeges up until level 1 (error and warnings)
[ 0.000018020s ] t_waring: t_error.cc:16 in main: You can try, but nobody is listening...
[ 0.000037506s ] t_debug[0]: t_error.cc:17 in main: Clean the machine it's full of bugs.
Hello World!
[ 0.000062650s ] t_error: t_error.cc:21 in main: Oh no! error #42 occured: The world stopped turning :(
t_error: caused the program to terminate.

Assert debug messeges up until level 2 (error and warnings)
[ 0.000017391s ] t_waring: t_error.cc:16 in main: You can try, but nobody is listening...
[ 0.000036039s ] t_debug[0]: t_error.cc:17 in main: Clean the machine it's full of bugs.
Hello World!
[ 0.000058529s ] t_debug[1]: t_error.cc:19 in main: Have you cleaned that buggy machine yet?
[ 0.000063767s ] t_error: t_error.cc:21 in main: Oh no! error #42 occured: The world stopped turning :(
t_error: caused the program to terminate.

Assert debug messeges up until level 3 (error and warnings)
[ 0.000019207s ] t_waring: t_error.cc:16 in main: You can try, but nobody is listening...
[ 0.000046236s ] t_debug[0]: t_error.cc:17 in main: Clean the machine it's full of bugs.
Hello World!
[ 0.000069913s ] t_debug[1]: t_error.cc:19 in main: Have you cleaned that buggy machine yet?
[ 0.000074523s ] t_debug[2]: t_error.cc:20 in main: All I hear is bzzzz bzzzzzzzzzzzz...
[ 0.000081018s ] t_error: t_error.cc:21 in main: Oh no! error #42 occured: The world stopped turning :(
t_error: caused the program to terminate.
```
To clean run:
```
make clean
```
