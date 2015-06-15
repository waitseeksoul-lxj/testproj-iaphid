#ifndef   __PSET_BT_IAP_HID_LOG_H__
#define   __PSET_BT_IAP_HID_LOG_H__
#include "iap_hid_debug.h"

#ifdef __cplusplus
extern "C"{
#endif

void BLOGI(int module, const char* fmt, ...);
void BLOGD(int module, const char* fmt, ...);
void BLOGW(int module, const char* fmt, ...);
void BLOGE(int module, const char* fmt, ...);

#define 	BLOG_IAP_HID_TASK  0x01

#define LOGI(module, fmt, arg...) BLOGI(module, fmt, ##arg)
#define LOGW(module, fmt, arg...) BLOGW(module, fmt, ##arg)
#define LOGD(module, fmt, arg...) BLOGD(module, fmt, ##arg)
#define LOGE(module, fmt, arg...) BLOGE(module, fmt, ##arg)

#define IAPHIDlOGI(fmt, arg...)    LOGI(BLOG_IAP_HID_TASK, fmt, ##arg)
#define IAPHIDlOGW(fmt, arg...)    LOGW(BLOG_IAP_HID_TASK, fmt, ##arg)
#define IAPHIDlOGD(fmt, arg...)    LOGD(BLOG_IAP_HID_TASK, fmt, ##arg)
#define IAPHIDlOGE(fmt, arg...)    LOGE(BLOG_IAP_HID_TASK, fmt, ##arg)


#ifdef __cplusplus
}
#endif

#endif
