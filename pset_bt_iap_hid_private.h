#ifndef __PSET_BT_IAP_HID_PRIVATE_H__
#define __PSET_BT_IAP_HID_PRIVATE_H__
//#include "pset_types.h"

#define PSET_IAP_HID_MAX_DOT_COUNTER       10
#define PSET_IAP_HID_MAX_SERIAL_COUNTER    3

/*Defaukt screen information*/
#define WRP_HID_DEFAULT_LOCAL_WIDTH      800
#define WRP_HID_DEFAULT_LOCAL_HIGHT       480
#define WRP_HID_DEFAULT_REMOTE_WIDTH   1920
#define WRP_HID_DEFAULT_REMOTE_HIGHT    1080

/* the maximum displacement value: localHight/20, localWidth/20 */
#define MAX_PRESS_PERCENT                            20
#if 0
/*
    len  || opcode other || opcode
  2bytes || 2bytes       || other
*/

#define WRP_HID_APP_HEADER  4

#define HOST_HID_APP_SET_PHONE_MODE_REQ 0x1000
#define HOST_HID_APP_TOUCH_REQ          0x1001
#define HOST_HID_APP_PUSH_KEY_REQ       0x1002
#define HOST_HID_APP_RESUME_UI_REQ      0x1003
#define HOST_HID_APP_SPEECH_RECO_REQ    0x1004
#define HOST_HID_APP_VOLUME_CONTROL_REQ 0x1005
#define HOST_HID_APP_PLAYER_CONTROL_REQ 0x1006
#define HOST_HID_APP_STATUS_CONTROL_REQ 0x1007

/*Indication*/
#define HOST_HID_APP_INIT_IND           0x1100
#define HOST_HID_APP_CALL_STATE_IND     0x2100
#define HOST_HID_APP_BT_DEV_LIST_IND    0x3100
#define HOST_HID_APP_BT_STATE_IND       0x3101
#define HOST_HID_APP_BT_REV_DATA_IND    0x3103
#define HOST_HID_APP_SCREEN_DATA_IND    0x4100
#define HOST_HID_APP_ERROR_CMD_IND      0xFFFF



void BTAppHidInitTouchScreen(void);

typedef enum
{
    WRP_HID_APP_READY,
    WRP_HID_APP_CONNECTIING,
    WRP_HID_APP_CONNECTED,
    WRP_HID_APP_DISCONNECTING,   
}WRP_HID_APP_STATUS;
#endif

#if 0
uint8 MouseReportDescriptor[50] = {
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x02,                    // USAGE (Mouse)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x09, 0x01,                    //   USAGE (Pointer)
    0xa1, 0x00,                    //   COLLECTION (Physical)
    0x05, 0x09,                    //      USAGE_PAGE (Button)
    0x19, 0x01,                    //      USAGE_MINIMUM (Button 1)
    0x29, 0x03,                    //      USAGE_MAXIMUM (Button 3)
    0x15, 0x00,                    //      LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //      LOGICAL_MAXIMUM (1)
    0x95, 0x03,                    //      REPORT_COUNT (3)
    0x75, 0x01,                    //      REPORT_SIZE (1)
    0x81, 0x02,                    //      INPUT (Data,Var,Abs)
    0x95, 0x01,                    //      REPORT_COUNT (1)
    0x75, 0x05,                    //      REPORT_SIZE (5)
    0x81, 0x03,                    //      INPUT (Cnst,Var,Abs)
    0x05, 0x01,                    //      USAGE_PAGE (Generic Desktop)
    0x09, 0x30,                    //      USAGE (X)
    0x09, 0x31,                    //      USAGE (Y)
    0x15, 0x81,                    //      LOGICAL_MINIMUM (-127)
    0x25, 0x7f,                    //      LOGICAL_MAXIMUM (127)
    0x75, 0x08,                    //      REPORT_SIZE (8)
    0x95, 0x02,                    //      REPORT_COUNT (2)
    0x81, 0x06,                    //      INPUT (Data,Var,Rel)
    0xc0,                              //   END_COLLECTION
    0xc0                               // END_COLLECTION
};
#endif

uint8 MouseReportDescriptor[52] = {
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x02,                    // USAGE (Mouse)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x09, 0x01,                    //   USAGE (Pointer)
    0xa1, 0x00,                    //   COLLECTION (Physical)
    0x05, 0x09,                    //      USAGE_PAGE (Button)
    0x19, 0x01,                    //      USAGE_MINIMUM (Button 1)
    0x29, 0x03,                    //      USAGE_MAXIMUM (Button 3)
    0x15, 0x00,                    //      LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //      LOGICAL_MAXIMUM (1)
    0x95, 0x03,                    //      REPORT_COUNT (3)
    0x75, 0x01,                    //      REPORT_SIZE (1)
    0x81, 0x02,                    //      INPUT (Data,Var,Abs)
    0x95, 0x01,                    //      REPORT_COUNT (1)
    0x75, 0x05,                    //      REPORT_SIZE (5)
    0x81, 0x01,                    //      INPUT (Cnst,Var,Abs)
    0x05, 0x01,                    //      USAGE_PAGE (Generic Desktop)
    0x09, 0x30,                    //      USAGE (X)
    0x09, 0x31,                    //      USAGE (Y)
    0x16, 0x01, 0x80,          //      LOGICAL_MINIMUM (-32767)
    0x26, 0xFF, 0x7F,          //      LOGICAL_MAXIMUM (32767)
    0x75, 0x10,                    //      REPORT_SIZE (16)
    0x95, 0x02,                    //      REPORT_COUNT (2)
    0x81, 0x06,                    //      INPUT (Data,Var,Rel)
    0xc0,                              //   END_COLLECTION
    0xc0                               // END_COLLECTION
};


#if 1
typedef enum
{
    IAP_HID_VH_NONE = 0x00,
    IAP_HID_VH_V = 0x01,
    IAP_HID_VH_H = 0x02
}PSET_IAP_HID_VH_STATUS;
#endif

typedef struct
{
    /*Remote Phone Information*/
    uint16 screenHight;
    uint16 screenWidth;
    uint8  screenVH; /*1-H, 2-V*/


    /*Local Information*/
    uint16 localHight;
    uint16 localWidth;
    
    /*Set X and Y successfully*/
    int16  prevX;
    int16  prevY;

    /*want to set X,Y*/
    int16  wantX;
    int16  wantY;

    uint8  dotCount;   /*Continue press*/
    uint8  serialCount;/*Continue release*/

    uint8  needAdjust;// true need adjust

    /* when send phone successfully, save the UI x,y*/
    int16   lastXref;
    int16   lastYref;
    
    /* the max move displace, when press drog*/
    uint16  maxXDis;
    uint16  maxYDis;

    uint16 pendingCmd;

}IapHidFuncMng;


#endif
