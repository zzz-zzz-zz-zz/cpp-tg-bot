#ifndef __TGBOT_MACRO
#define __TGBOT_MACRO

/**
 * Gathering of useful macroses
 **/

#include "_ext.hpp"

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif


// Omit json::out_of_range exception
#define OMIT(code)\
    try {\
    code\
    ;\
    }\
    catch\
    (json::out_of_range &e)\
    { }\

// Identical sleep() for Windows/Non-Windows platforms
#ifdef _WIN32
    #define sleep(seconds) Sleep(seconds)
#endif

// Exit with message in stderr
#define ABORT(msg) std::cerr << "ABORT: " << msg << std::endl;\
                exit(1);


#endif // __TGBOT_MACRO