#ifndef __BAN_20190129_PRINT_LOG_H__
#define __BAN_20190129_PRINT_LOG_H__

#include<sys/time.h>

#define LEVEL_TRACE     'T'
#define LEVEL_DEBUG     'D'
#define LEVEL_INFO      'N'
#define LEVEL_WARN      'W'
#define LEVEL_ERROR     'E'
#define LEVEL_FATAL     'F'

#define PrintTime_s()                   \
        {                               \
            struct timeval tv;          \
            gettimeofday(&tv, NULL);    \
            char tmp[64];               \
            strftime(tmp, sizeof(tmp), "[%Y-%m-%d %H:%M:%S", localtime(&tv.tv_sec));    \
            fprintf(stderr, "%s.%ld]", tmp, tv.tv_usec);                                \
        }

#define Str(x) #x

#define Str2Map(arg)  Str(arg) << ":" << arg << ", "

#define Filename(x) strrchr(x,'/')?strrchr(x,'/')+1:x

#define FormatLog(level, format_str, ...)               \
    {                                                   \
        PrintTime_s();                                  \
        fprintf(stderr, "[%c][%s][%s][%d]",level, Filename(__FILE__), __FUNCTION__, __LINE__);         \
        fprintf(stderr, format_str, ## __VA_ARGS__);    \
        fprintf(stderr, "\n");                          \
    }                    

#define LogFile(level, msg_str, file_fd)        \
    {                                           \
        PrintTime_s();                          \
        fprintf(stderr, "[%c][%s][%s][%d]",level, Filename(__FILE__), __FUNCTION__, __LINE__);         \
        fprintf(file_fd, "%s\n", msg_str);      \
    }

#define StreamLog(level, stream_str)                \
    {                                               \
        std::stringstream ss;                       \
        ss << stream_str;                           \
        FormatLog(level, "%s", ss.str().c_str());   \
    }

#define MarkLog() FormatLog('N', "__ %s __", __FUNCTION__)

#define MARK_LOG() MarkLog()
    
#define LOG_TRACE_FMT(format_str, ...)      \
    FormatLog(LEVEL_TRACE, format_str, ## __VA_ARGS__) 

#define LOG_DEBUG_FMT(format_str, ...)      \
    FormatLog(LEVEL_DEBUG, format_str, ## __VA_ARGS__)

#define LOG_INFO_FMT(format_str, ...)       \
    FormatLog(LEVEL_INFO, format_str, ## __VA_ARGS__)

#define LOG_WARN_FMT(format_str, ...)       \
    FormatLog(LEVEL_WARN, format_str, ## __VA_ARGS__)

#define LOG_ERROR_FMT(format_str, ...)      \
    FormatLog(LEVEL_ERROR, format_str, ## __VA_ARGS__) 

#define LOG_FATAL_FMT(format_str, ...)      \
    FormatLog(LEVEL_FATAL, format_str, ## __VA_ARGS__)


#define LOG_TRACE_STM(stream_str)    StreamLog(LEVEL_TRACE, stream_str)

#define LOG_DEBUG_STM(stream_str)    StreamLog(LEVEL_DEBUG, stream_str)

#define LOG_INFO_STM(stream_str)     StreamLog(LEVEL_INFO, stream_str)

#define LOG_WARN_STM(stream_str)     StreamLog(LEVEL_WARN, stream_str)

#define LOG_ERROR_STM(stream_str)    StreamLog(LEVEL_ERROR, stream_str)

#define LOG_FATAL_STM(stream_str)    StreamLog(LEVEL_FATAL, stream_str)



#endif // !__BAN_20190129_PRINT_LOG_H__