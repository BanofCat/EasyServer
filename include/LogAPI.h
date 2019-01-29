#ifndef __BAN_20190129_LOG_API_H__
#define __BAN_20190129_LOG_API_H__

#include <time.h>
#include <sstream>
#include <iostream>
#include <string.h>

#ifdef PRINT_LOG_RC
    #include "PrintLog_rc.h"
#else

    #define MARK_LOG()

    #define LOG_TRACE_FMT(...)
    #define LOG_DEBUG_FMT(...)
    #define LOG_INFO_FMT(...)
    #define LOG_WARN_FMT(...)
    #define LOG_ERROR_FMT(...)
    #define LOG_FATAL_FMT(...)

    #define LOG_TRACE_STM(...)
    #define LOG_DEBUG_STM(...)
    #define LOG_INFO_STM(...)
    #define LOG_WARN_STM(...)
    #define LOG_ERROR_STM(...)
    #define LOG_FATAL_STM(...)
#endif 


#endif //__BAN_20190129_LOG_API_H__