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
    __WARNING__("You can try, but nobody is listening...");
    __DEBUG__(0,"Clean the machine it's full of bugs.");
    printf("%s\n",t_error::colorize(t_error::t_colors::GREEN,"Hello World!").c_str());
    __DEBUG__(1,"Have you cleaned that buggy machine yet?");
    __DEBUG__(2,"All I hear is bzzzz bzzzzzzzzzzzz...");
    __ERROR__("Oh no! error #%d occured: The world stopped turning :(",052);
    return EXIT_SUCCESS;
}
