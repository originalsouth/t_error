/* By BC van Zuiden -- Leiden, July 2016 */
/* Probably very buggy USE AT OWN RISK this will brick everything you own */
/* NOBODY but YOU is liable for anything that happened in result of using this */
/* WARNING: DON'T RUN THIS PROGRAM THIS WILL DESTROY YOUR COMPUTER AND/OR HOUSE */
/* Any copyrighted piece of code within this code is NOT mine */
/* Inclusion of that code is forced upon me by a scary anonymous guy with a gun*/
/* https://github.com/originalsouth/t_error */
/* Please do not remove this comment from the source*/

#include <cstdio>
#include <cstdlib>
#include "t_error.h"

int main()
{
    WARNING("You can try, but nobody is listening...");
    DEBUG(0,"Clean the machine it's full of bugs.");
    printf("Hello World!\n");
    DEBUG(1,"Have you cleaned that buggy machine yet?");
    DEBUG(2,"All I hear is bzzzz bzzzzzzzzzzzz...");
    ERROR("Oh no! The world stopped turning :(");
    return EXIT_SUCCESS;
}
