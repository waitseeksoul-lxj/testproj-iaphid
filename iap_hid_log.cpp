#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <sys/time.h>
//#include "bt_task_declare.h"
#include "iap_hid_debug.h"

#define  PLATFROM_TMAP

#ifdef PLATFROM_TMAP
    #define USE_LOGCAT
#endif

#ifdef USE_LOGCAT
#include "ncore/NCTypesDefine.h"
#include "ncore/NCLog.h"

#define  NC_LOG_TAG "iaphid"
using namespace nutshell;
#define LOG_DBG(...)    NCLOGI(__VA_ARGS__)
#else
#define LOG_DBG(...)    printf(__VA_ARGS__);fflush(stdout)
#endif

#define BLOG_IAP_HID_TASK  0x01

#define MAX_LOG_SIZE (10240)

typedef void (*handlerLogFunc)(const char *tag, char *log);
extern handlerLogFunc btSendLog;
static char buf_time[20];

const char *getLogTag(int module)
{
    switch ( module )
    {
        case BLOG_IAP_HID_TASK:
            return "IAPHID";
        default:
            return "";
    }
}

char *getLogTime()
{
#ifdef USE_LOGCAT
    buf_time[0] = '\0';
#else
    struct timeval time;
    struct tm *tmp;

    /* Get Current time */
    gettimeofday(&time, NULL);
    tmp = localtime(&time.tv_sec);
    sprintf(buf_time, "%02d:%02d:%02d:%03d ", tmp->tm_hour, tmp->tm_min, tmp->tm_sec, (int)(time.tv_usec/1000));
#endif
    return buf_time;
}

void logTrim(char *str)
{
    if(strrchr(str, '\n') == NULL)
    {
        strcat(str, "\n");
    }
}

#if 0
void ALOGI(const char* fmt, ...)
{
    va_list argp;
    char tmpLog[MAX_LOG_SIZE];

    memset(tmpLog, 0, sizeof(tmpLog));

    va_start( argp, fmt );

    vsprintf(tmpLog, fmt, argp);
    logTrim(tmpLog);

    va_end( argp );

    if (ALOG_INFO >= ALOG_LEVEL)
    {
        LOG_DBG("%s[SYSTEM]: %s", getLogTime(), tmpLog);
    }
}

void ALOGE(const char* fmt, ...)
{
    va_list argp;
    char tmpLog[MAX_LOG_SIZE];

    memset(tmpLog, 0, sizeof(tmpLog));

    va_start( argp, fmt );

    vsprintf(tmpLog, fmt, argp);
    logTrim(tmpLog);

    va_end( argp );

    if (ALOG_ERROR >= ALOG_LEVEL)
    {
        LOG_DBG("\033[;31m%s[SYSTEM][Error] %s\033[m", getLogTime(), tmpLog);
    }
}

void ALOGD(const char* fmt, ...)
{
    va_list argp;
    char tmpLog[MAX_LOG_SIZE];

    memset(tmpLog, 0, sizeof(tmpLog));

    va_start( argp, fmt );

    vsprintf(tmpLog, fmt, argp);
    logTrim(tmpLog);

    va_end( argp );

    if (ALOG_DEBUG >= ALOG_LEVEL)
    {
        LOG_DBG("%s[SYSTEM]: %s", getLogTime(), tmpLog);
    }
}

void ALOGW(const char* fmt, ...)
{
    va_list argp;
    char tmpLog[MAX_LOG_SIZE];

    memset(tmpLog, 0, sizeof(tmpLog));

    va_start( argp, fmt );

    vsprintf(tmpLog, fmt, argp);
    logTrim(tmpLog);

    va_end( argp );

    if (ALOG_WARNING >= ALOG_LEVEL)
    {
        LOG_DBG("%s[SYSTEM]: %s", getLogTime(), tmpLog);
    }
}
#endif

void BLOGI(int module, const char* fmt, ...)
{
    va_list argp;
    char tmpLog[MAX_LOG_SIZE];
    const char *tag = getLogTag(module);

    memset(tmpLog, 0, sizeof(tmpLog));

    va_start( argp, fmt );

    vsprintf(tmpLog, fmt, argp);
    logTrim(tmpLog);

    va_end( argp );

#if 0
    if(module == TASK_MAX)
    {
        if(btSendLog != NULL)
        {
            btSendLog(tag, tmpLog);
        }
    }
#endif
    LOG_DBG("%s[%s]: %s", getLogTime(), tag, tmpLog);
    return ;
}

void BLOGE(int module, const char* fmt, ...)
{
    va_list argp;
    char tmpLog[MAX_LOG_SIZE];
    const char *tag = getLogTag(module);

    memset(tmpLog, 0, sizeof(tmpLog));

    va_start( argp, fmt );

    vsprintf(tmpLog, fmt, argp);
    logTrim(tmpLog);

    va_end( argp );

    LOG_DBG("\033[;31m%s[Error][%s]: %s\033[m", getLogTime(), tag, tmpLog);
    return ;
}

void BLOGD(int module, const char* fmt, ...)
{
    va_list argp;
    char tmpLog[MAX_LOG_SIZE];
    const char *tag = getLogTag(module);

    memset(tmpLog, 0, sizeof(tmpLog));

    va_start( argp, fmt );

    vsprintf(tmpLog, fmt, argp);
    logTrim(tmpLog);

    va_end( argp );

    LOG_DBG("%s[%s]: %s", getLogTime(), tag, tmpLog);
    return ;
}

void BLOGW(int module, const char* fmt, ...)
{
    va_list argp;
    char tmpLog[MAX_LOG_SIZE];
    const char *tag = getLogTag(module);

    memset(tmpLog, 0, sizeof(tmpLog));

    va_start( argp, fmt );

    vsprintf(tmpLog, fmt, argp);
    logTrim(tmpLog);

    va_end( argp );

    LOG_DBG("%s[%s]: %s", getLogTime(), tag, tmpLog);
    return ;
}
