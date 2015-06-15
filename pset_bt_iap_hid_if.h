//#ifdef PSET_INCLUDE_HID

#ifndef __PSET_BT_IAP_HID_IF_H_
#define __PSET_BT_IAP_HID_IF_H_

#ifdef __cplusplus
extern "C" {
#endif

//#include "pset_common.h"
//#include <string.h>
//#include <stdlib.h>
#define   BUFFER_SIZE   1024

typedef unsigned char  uint8;
typedef unsigned short uint16;

typedef char  int8;
typedef short int16;

#if 0
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint32_t uint24;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
#endif
/************************************************************************
    Following APIs should be used when send HID report to Apple device.
*************************************************************************/

uint8 BtAppiPhoneHidGetReportDesciptor(uint8 * data, uint16 * length);

uint8 BtAppiPhoneHidSettingReq(uint16 localX, uint16 localY, uint16 remoteX, uint16 remoteY, uint8 remoteVH);

uint8 BtAppiPhoneHidReportReq(uint8 key, uint16 X, uint16 Y, uint16 reserved, uint8 type, uint8* data, uint16* length, uint8* adjust);

uint8 BtAppiPhoneSendReportResult(uint16 response);

uint8 BtAppiPhoneHidInitTouchScreen(uint8* data, uint16* length);

/************************************************************************
    Following APIs should be used for callback function struction.
*************************************************************************/
typedef enum
{
    SEND_REPORT_HID = 0x00,
    SEND_REPORT_ASSISTIVE_TOUCH = 0x01
}MESSAGE_TYPE;

typedef enum
{
    HID_EVT_SUCCESS = 0x00,
    HID_EVT_ILLEGAL_PARAM = 0x01,
    HID_EVT_DEVICE_BUSY = 0x02,
    HID_BUFFER_MALLOC_FAILURE = 0x03,
    HID_POINTER_NULL = 0x04
}RETURN_VAL;

typedef enum
{
    IAP_HID_DATA_ASK_IDLE = 0x0000,
    IAP_HID_DATA_ASK_BUSY = 0x0001
}REQ_STATUS;

#if 0
typedef struct
{
    uint8   reportType;
    uint16  reportLen;
    uint8   *report;
} BT_HID_DATA_IND_T;

typedef struct
{
    uint16  status;
} BT_HID_SETTING_CFM_T;
#endif

#ifdef __cplusplus
}
#endif

#endif//__PSET_BT_HID_IF_H_

//#endif //#ifdef PSET_INCLUDE_HID

