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

namespace t_error
{
    namespace t_colors
    {
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
    };
    namespace t_globals
    {
        bool colors=true;
        std::chrono::high_resolution_clock::time_point timestamp=std::chrono::high_resolution_clock::now();
        std::string time_format="%9.9fs";
    };
    struct t_error_obj
    {
        std::string flag;
        std::string flag_color;
        std::string terminate_message;
        bool terminate;
        FILE *log_file;
        t_error_obj();
        ~t_error_obj();
        template<typename ...Args> void print(std::string message,Args... args);
        void term();
    };
    struct base
    {
        t_error_obj error;
        t_error_obj warning;
        std::vector<t_error_obj> debug;
        base();
    } t_error;
    std::string colorize(std::string color,std::string str);
    void set_colors(bool colors);
    void set_flag(t_error_obj obj,std::string flag);
    void set_flag_color(t_error_obj obj,std::string color);
    void set_log_file(t_error_obj obj,FILE *log_file);
    void set_terminate(t_error_obj obj,bool terminate);
    void set_terminate_message(t_error_obj obj,std::string terminate_message);
    void set_timer(std::chrono::high_resolution_clock::time_point timestamp);
    void reset_timer();
    void set_time_format(std::string time_format);
};

t_error::t_error_obj::t_error_obj()
{
    flag="t_error:";
    flag_color=t_colors::BOLDRED;
    terminate_message="caused the program to terminate.";
    terminate=false;
    log_file=stderr;
}

t_error::t_error_obj::~t_error_obj()
{
    fclose(log_file);
}

template<typename ...Args> void t_error::t_error_obj::t_error_obj::print(std::string message,Args... args)
{
    const double time=std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-t_globals::timestamp).count();
    std::string str="[ "+t_globals::time_format+" ] "+colorize(flag_color,flag)+" "+message;
    fprintf(log_file,str.c_str(),time,args...);
    if(terminate) term();
}

void t_error::t_error_obj::t_error_obj::term()
{
    printf("%s %s\n",colorize(flag_color,flag).c_str(),terminate_message.c_str());
    exit(EXIT_FAILURE);
}

t_error::base::base::base()
{
    error.terminate=true;
    warning.flag="t_waring:";
    warning.flag_color=t_colors::BOLDBLUE;
    const std::string debug_colors[3]={t_colors::BOLDMAGENTA,t_colors::BOLDYELLOW,t_colors::BOLDCYAN};
    #ifdef T_DEBUG
    const size_t dbgsz=T_DEBUG;
    #else
    const size_t dbgsz=3;
    #endif
    debug.resize(dbgsz);
    for(size_t i=0;i<dbgsz;i++) debug[i].flag="t_debug["+std::to_string(i)+"]:";
    for(size_t i=0;i<dbgsz;i++) debug[i].flag_color=debug_colors[i%3];
    for(size_t i=0;i<dbgsz;i++) debug[i].log_file=stdout;
}

std::string t_error::colorize(std::string color,std::string str)
{
    return t_globals::colors?color+str+t_colors::RESET:str;
}

void t_error::set_colors(bool colors)
{
    t_globals::colors=colors;
}

void t_error::set_flag(t_error_obj obj,std::string flag)
{
    obj.flag=flag;
}

void t_error::set_flag_color(t_error_obj obj,std::string color)
{
    obj.flag_color=color;
}

void t_error::set_log_file(t_error_obj obj,FILE *log_file)
{
    obj.log_file=log_file;
}

void t_error::set_terminate(t_error_obj obj,bool terminate)
{
    obj.terminate=terminate;
}

void t_error::set_terminate_message(t_error_obj obj,std::string terminate_message)
{
    obj.terminate_message=terminate_message;
}

void t_error::set_timer(std::chrono::high_resolution_clock::time_point timestamp)
{
    t_globals::timestamp=timestamp;
}

void t_error::reset_timer()
{
    t_globals::timestamp=std::chrono::high_resolution_clock::now();
}

void t_error::set_time_format(std::string time_format)
{
    t_globals::time_format=time_format;
}

#ifdef T_ERROR
#define __ERROR__(str,...) \
{\
    std::string buffer=t_error::colorize(t_error::t_colors::BOLDWHITE,std::string(__FILE__)+":"+std::to_string(__LINE__))+" in "+t_error::colorize(t_error::t_colors::WHITE,std::string(__func__))+": "+str+"\n";\
    t_error::t_error.error.print(buffer,##__VA_ARGS__);\
}
#else
#define __ERROR__(str,...) ;
#endif

#ifdef T_WARNING
#define __WARNING__(str,...) \
{\
    std::string buffer=t_error::colorize(t_error::t_colors::BOLDWHITE,std::string(__FILE__)+":"+std::to_string(__LINE__))+" in "+t_error::colorize(t_error::t_colors::WHITE,std::string(__func__))+": "+str+"\n";\
    t_error::t_error.warning.print(buffer,##__VA_ARGS__);\
}
#else
#define __WARNING__(str,...) ;
#endif

#ifdef T_DEBUG
#define __DEBUG__(level,str,...) \
{\
    if(level<T_DEBUG and level<t_error::t_error.debug.size())\
    {\
        std::string buffer=t_error::colorize(t_error::t_colors::BOLDWHITE,std::string(__FILE__)+":"+std::to_string(__LINE__))+" in "+t_error::colorize(t_error::t_colors::WHITE,std::string(__func__))+": "+str+"\n";\
        t_error::t_error.debug[level].print(buffer,##__VA_ARGS__);\
    }\
}
#else
#define __DEBUG__(level,str,...) ;
#endif
