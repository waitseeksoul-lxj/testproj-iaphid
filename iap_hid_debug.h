#ifndef __IAP_HID_DEBUG_H__
#define __IAP_HID_DEBUG_H__

#ifdef __cplusplus
extern "C"{
#endif

/* define log degbu module */
#define STACK_DEBUG   (0)
#define STACKDM_DEBUG (1)

#if 0
#define LOGI(module, fmt, arg...) bt_log_info(module, fmt, ##arg)
#define LOGW(module, fmt, arg...) bt_log_warn(module, fmt, ##arg)
#define LOGD(module, fmt, arg...) bt_log_debug(module, fmt, ##arg)
#define LOGE(module, fmt, arg...) bt_log_error(module, fmt, ##arg)

void bt_log_info(uint16 module, const uint8* fmt, ...);
void bt_log_warn(uint16 module, const uint8* fmt, ...);
void bt_log_debug(uint16 module, const uint8* fmt, ...);
void bt_log_error(uint16 module, const uint8* fmt, ...);
#else

#define ALOG_INFO       (0)
#define ALOG_DEBUG      (1)
#define ALOG_WARNING    (2)
#define ALOG_ERROR      (3)
#define ALOG_LEVEL ALOG_INFO

#if 0
void ALOGI(const char* fmt, ...);
void ALOGE(const char* fmt, ...);
void ALOGD(const char* fmt, ...);
void ALOGW(const char* fmt, ...);
#endif

void BLOGI(int module, const char* fmt, ...);
void BLOGD(int module, const char* fmt, ...);
void BLOGW(int module, const char* fmt, ...);
void BLOGE(int module, const char* fmt, ...);

#define LOGI(module, fmt, arg...) BLOGI(module, fmt, ##arg)
#define LOGW(module, fmt, arg...) BLOGW(module, fmt, ##arg)
#define LOGD(module, fmt, arg...) BLOGD(module, fmt, ##arg)
#define LOGE(module, fmt, arg...) BLOGE(module, fmt, ##arg)

#endif

#ifdef __cplusplus
}
#endif

#endif
