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
#include <string>
#include <vector>
#include <chrono>
#include <fenv.h>

namespace t_colors
{
    bool colors=true;
    const std::string RESET="\033[0m";
    const std::string BLACK="\033[30m";
    const std::string RED="\033[31m";
    const std::string GREEN="\033[32m";
    const std::string YELLOW="\033[33m";
    const std::string BLUE="\033[34m";
    const std::string MAGENTA="\033[35m";
    const std::string CYAN="\033[36m";
    const std::string WHITE="\033[37m";
    const std::string BOLDBLACK="\033[1m\033[30m";
    const std::string BOLDRED="\033[1m\033[31m";
    const std::string BOLDGREEN="\033[1m\033[32m";
    const std::string BOLDYELLOW="\033[1m\033[33m";
    const std::string BOLDBLUE="\033[1m\033[34m";
    const std::string BOLDMAGENTA="\033[1m\033[35m";
    const std::string BOLDCYAN="\033[1m\033[36m";
    const std::string BOLDWHITE="\033[1m\033[37m";
    std::string colorize(std::string color,std::string str);
};

std::string t_colors::colorize(std::string color,std::string str)
{
    return colors?color+str+RESET:str;
}

namespace t_error
{
    std::chrono::high_resolution_clock::time_point begin=std::chrono::high_resolution_clock::now();;
    std::string TIME_FMT="%9.9fs";
    struct t_error_obj
    {
        std::string FLAG;
        std::string TERM_MSG;
        bool terminate;
        FILE *log_file;
        t_error_obj();
        ~t_error_obj();
        template<typename ...Args> void print(std::string message,Args... args);
        void term();
    };
}

t_error::t_error_obj::t_error_obj()
{
    FLAG=t_colors::colorize(t_colors::BOLDRED,"t_error:");
    TERM_MSG="caused the program to terminate.";
    terminate=false;
    log_file=stderr;
}

t_error::t_error_obj::~t_error_obj()
{
    fclose(log_file);
}

template<typename ...Args> void t_error::t_error_obj::print(std::string message,Args... args)
{
    const double time=std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-begin).count();
    std::string str="[ "+TIME_FMT+" ] "+FLAG+" "+message;
    fprintf(log_file,str.c_str(),time,args...);
    if(terminate) term();
}

void t_error::t_error_obj::term()
{
    printf("%s %s\n",FLAG.c_str(),TERM_MSG.c_str());
    exit(EXIT_FAILURE);
}

namespace base
{
    struct base
    {
        t_error::t_error_obj error;
        t_error::t_error_obj warning;
        std::vector<t_error::t_error_obj> debug;
        base();
    } t_error;
};

base::base::base()
{
    error.terminate=true;
    warning.FLAG=t_colors::colorize(t_colors::BOLDBLUE,"t_waring:");
    const std::string debug_colors[3]={t_colors::BOLDMAGENTA,t_colors::BOLDYELLOW,t_colors::BOLDCYAN};
    #ifdef T_DEBUG
    const size_t dbgsz=T_DEBUG;
    #else
    const size_t dbgsz=3;
    #endif
    debug.resize(dbgsz);
    for(size_t i=0;i<dbgsz;i++) debug[i].FLAG=t_colors::colorize(debug_colors[i],"t_debug["+std::to_string(i)+"]:");
    for(size_t i=0;i<dbgsz;i++) debug[i].log_file=stdout;
}

#ifdef T_ERROR
#define ERROR(str,...) \
{\
    std::string buffer=t_colors::colorize(t_colors::BOLDWHITE,std::string(__FILE__)+":"+std::to_string(__LINE__))+" in "+t_colors::colorize(t_colors::WHITE,std::string(__func__))+": "+str+"\n";\
    base::t_error.error.print(buffer,##__VA_ARGS__);\
}
#else
#define ERROR(str,...) ;
#endif

#ifdef T_WARNING
#define WARNING(str,...) \
{\
    std::string buffer=t_colors::colorize(t_colors::BOLDWHITE,std::string(__FILE__)+":"+std::to_string(__LINE__))+" in "+t_colors::colorize(t_colors::WHITE,std::string(__func__))+": "+str+"\n";\
    base::t_error.warning.print(buffer,##__VA_ARGS__);\
}
#else
#define WARNING(str,...) ;
#endif

#ifdef T_DEBUG
#define DEBUG(level,str,...) \
{\
    if(level<T_DEBUG and level<base::t_error.debug.size())\
    {\
        std::string buffer=t_colors::colorize(t_colors::BOLDWHITE,std::string(__FILE__)+":"+std::to_string(__LINE__))+" in "+t_colors::colorize(t_colors::WHITE,std::string(__func__))+": "+str+"\n";\
        base::t_error.debug[level].print(buffer,##__VA_ARGS__);\
    }\
}
#else
#define DEBUG(level,str,...) ;
#endif
