#include "pset_bt_iap_hid_if.h"
#include "pset_bt_iap_hid_private.h"
#include "pset_bt_iap_hid_log.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

IapHidFuncMng  hidMng;

static void BtIapHidCheckParam(void);


#if 0
#include "pset_types.h"
#include "wrp_bt_private.h"
#include "pset_bt_hid_if.h"
#include "wrp_bt_hid_evt.h"

/**/
void BTAppHidInitTouchScreen(void);

static void BtIapHidCheckParam(void);


/************************************************************************
NAME:
*************************************************************************/
uint8 BtAppHidConnectReq(bdaddr deviceAddr)
{
    /*call the bluetec func*/
    wrp_bdaddr local_addr;
    IAPHIDlOGI("[WRP]HID: %s \n",__func__);
    wrpBaddrConvertFromApp(&local_addr, &deviceAddr);     
    BtHidConnectReq(local_addr);
    return 0;
}


/************************************************************************
NAME:
*************************************************************************/
uint8 BtAppHidDisconnectReq(void)
{
    /*call the bluetec func*/
    IAPHIDlOGI("[WRP]HID: %s \n",__func__);
    BtHidDisconnectReq();
    return 0;
}
#endif

/************************************************************************
NAME:
*************************************************************************/
uint8  BtAppiPhoneHidGetReportDesciptor(uint8* data, uint16 * length)
{
    if(data != NULL)
    {
        memcpy(data, MouseReportDescriptor, 52);
        if(length != NULL)
        {
            *length = 52;
        }
        IAPHIDlOGI("length is %d\n", *length);
    }
    else
    {
        IAPHIDlOGI("pointer data is NULL\n");
        if(length != NULL)
            *length = 0;
    }

    return 0x00;
}


/************************************************************************
NAME:
*************************************************************************/
uint8 BtAppiPhoneHidReportReq(uint8 key, uint16 X, uint16 Y, uint16 reserved, uint8 type, uint8* data, uint16* length, uint8* adjust)
{
    if(hidMng.pendingCmd != IAP_HID_DATA_ASK_IDLE)
    {
        return HID_EVT_DEVICE_BUSY;
    }
    
    uint16 xNewRef = 0, yNewRef = 0,  xAbs = 0, yAbs = 0;
    /*call the bluetec func*/
    IAPHIDlOGI("[iap]HID: %s,%.2X,%.2X,%.2X \n",__func__,key, X, Y, reserved);

    BtIapHidCheckParam();

     //operate bit sequence as 01 01 01 01 00
    if(key == 1 && hidMng.serialCount > 0)
    {
        int16  maxXadd = hidMng.lastXref + hidMng.maxXDis;
        int16  maxXreduce = hidMng.lastXref -hidMng.maxXDis;
        int16  maxYadd = hidMng.lastYref + hidMng.maxYDis;
        int16  maxYreduce = hidMng.lastYref -hidMng.maxYDis;
        
        //  lastXref + maxXDis < xRef
        if(X > maxXadd)
        {
            X = maxXadd;
            IAPHIDlOGI("******1 new xRef: %.2x\n", X);
        }
        //  xRef < lastXref - maxXDis 
        else if(X < maxXreduce)
        {
            X = maxXreduce;
            IAPHIDlOGI("******2 new xRef: %.2x\n", X);
        }

        //  lastYref + maxYDis < yRef
        if(Y > maxYadd)
        {
            Y = maxYadd;
            IAPHIDlOGI("******3 new yRef: %.2x\n", Y);
        }
         //  yRef < lastYref - maxYDis 
        else if(Y < maxYreduce)
        {
            Y = maxYreduce;
            IAPHIDlOGI("******4 new yRef: %.2x\n", Y);
        }
     }
    
    if(key == 1)
    {
        hidMng.lastXref = X;
        hidMng.lastYref = Y;
        IAPHIDlOGI("save xref: %.2x yref: %.2x \n", hidMng.lastXref, hidMng.lastYref);
    }

    /* get Ref */
    if(hidMng.screenVH ==IAP_HID_VH_V)
    {
        /*New local width diplay on local screen*/
        uint16 newWidth = hidMng.screenHight * hidMng.localHight / hidMng.screenWidth;
        /*Not in the display area check*/
        if(X<((hidMng.localWidth-newWidth)/2)) /*On LEFT-USELESS-AREA*/
        {
            /*ZERO X*/
            xAbs = 0;
            /*Local LOW->HIGH, phone LOW->HIGH*/
            yAbs =  (long)Y *  hidMng.screenWidth /  hidMng.localHight;
            IAPHIDlOGI("[WRP]HIDNEW->ACASE: %d,%d",xAbs, yAbs);
        }
        else if(X>(newWidth+(hidMng.localWidth-newWidth)/2)) /*On RIGHT-USELESS-AREA*/
        {
            /*MAX X*/
            xAbs =  hidMng.screenHight;
            /*Local LOW->HIGH, phone LOW->HIGH*/
            yAbs =  (long)Y *  hidMng.screenWidth /  hidMng.localHight;
            IAPHIDlOGI("[WRP]HIDNEW->BCASE: %d,%d",xAbs, yAbs);
        }
        else/*Normal Area*/
        {
            /*X-USLESS TOUCH AREA*/
            xAbs =  (long)(X-( hidMng.localWidth-newWidth)/2) *  hidMng.screenWidth /  hidMng.localHight;
            yAbs = (long)Y *  hidMng.screenWidth /  hidMng.localHight;
            IAPHIDlOGI("[WRP]HIDNEW->CCASE: %d,%d",xAbs, yAbs);
        }

        xAbs = (xAbs>hidMng.screenHight) ? hidMng.screenHight : xAbs;
        yAbs = (yAbs>hidMng.screenWidth) ? hidMng.screenWidth: yAbs;
 
    }
    else
    {
        IAPHIDlOGI("[WRP]HIDLOCAL: %.2x,%.2x,%.2x,%.2x,%.2x,%.2x",hidMng.screenWidth, hidMng.screenHight , hidMng.localWidth, hidMng.localHight, hidMng.prevX, hidMng.prevY);
        xAbs = (long)X *  hidMng.screenWidth /  hidMng.localWidth;
        yAbs = (long)Y *  hidMng.screenHight /  hidMng.localHight;
        xAbs = (xAbs>hidMng.screenWidth) ? hidMng.screenWidth : xAbs;
        yAbs = (yAbs>hidMng.screenHight) ? hidMng.screenHight: yAbs;
    }
    
    xNewRef = xAbs -  hidMng.prevX;
    yNewRef = yAbs -  hidMng.prevY;
    /*save the want seting value, after success, change prev value*/
    hidMng.wantX = xAbs;
    hidMng.wantY = yAbs;
    IAPHIDlOGI("[WRP]HIDNEW: %.2X,%.2X",xNewRef, yNewRef);

    /*set pending status, no send data again.*/
    hidMng.pendingCmd = IAP_HID_DATA_ASK_BUSY;

    //BtHidSendDataReq(key, xNewRef, yNewRef, reserved);


    //reqest type ( HID  0x00, Assistive Touch 0x01)
    if(type == 0x00)
    {
            uint8  message[5] = {0,0,0,0,0};

            if(key == 0x01)
            {
                // bit-0 is left button and value 1 as press
                message[0]  |=  0x1;
            }
            //X  relative position
            message[1] = xNewRef & 0xff;
            message[2] = xNewRef >> 8;
            //Y relative position
            message[3] = yNewRef & 0xff;
            message[4] = yNewRef >> 8;

            IAPHIDlOGI("messg: %.2x\n", message[0]);
            IAPHIDlOGI("messg: %.2x,  %.2x \n", message[1], message[2]);
            IAPHIDlOGI("messg: %.2x,  %.2x \n", message[3], message[4]);

            if(data != NULL)
            {
                memcpy(data, message, 5);
                if(length != NULL)
                {
                    *length = 0x05;
                }
            }
    }

    if(key == 0)
    {
        /* dotCount when key release */
        hidMng.dotCount ++;
        /* count to 10 points */
        if(hidMng.dotCount % PSET_IAP_HID_MAX_DOT_COUNTER == 0)
        {
            hidMng.needAdjust = 1;
            if(adjust != NULL)
            {
                *adjust = 0x01;
            }
        }

        /* action is a slide */
        if(hidMng.serialCount >= PSET_IAP_HID_MAX_SERIAL_COUNTER)
        {
            hidMng.needAdjust = 1;
            if(data != NULL)
            {
                *adjust = 0x01;
            }
        }
        hidMng.serialCount = 0;
    }
    else
    {
        hidMng.serialCount ++;
    }

    return HID_EVT_SUCCESS;
}

/************************************************************************
NAME:
*************************************************************************/
uint8 BtAppiPhoneHidInitTouchScreen(uint8* data, uint16* length)
{
    IAPHIDlOGI("BtAppiPhoneHidInitTouchScreen\n");
    /* move to left corner */
    int16   X = 0 - hidMng.screenWidth;
    int16   Y = 0 - hidMng.screenHight;

    /*Screen zero pointor is difference with V and H*/
    if(hidMng.screenVH == IAP_HID_VH_V)
    {
        X = 0 - hidMng.screenHight;
        Y = 0 - hidMng.screenWidth;
    }
    IAPHIDlOGI("BTAppHidInitTouchScreen,X=%d,Y=%d",X,Y);
    hidMng.wantX = 0;
    hidMng.wantY = 0;
    IAPHIDlOGI("BTAppHidInitTouchScreen, X = %.2x, Y= %.2x", X, Y);

    uint8 message[5] = {0,0,0,0,0};

    message[0]  |= 0x01;
    message[1] = X & 0xff;
    message[2] = X >> 8;
    message[3] = Y &0xff;
    message[4] = Y >> 8;
    
    IAPHIDlOGI("messg: %.2x\n", message[0]);
    IAPHIDlOGI("messg: %.2x,  %.2x \n", message[1], message[2]);
    IAPHIDlOGI("messg: %.2x,  %.2x \n", message[3], message[4]);

    if(data != NULL)
    {
        memcpy(data, message, 5);        
        if(length != NULL)
        {
            *length = 0x05;
        }
    }
    else
    {
        return  HID_POINTER_NULL;
    }
    
    return HID_EVT_SUCCESS;
}

/************************************************************************
NAME:
*************************************************************************/
uint8 BtAppiPhoneHidSettingReq(uint16 localX, uint16 localY, uint16 remoteX, uint16 remoteY, uint8 remoteVH)
{
    uint8 status = HID_EVT_SUCCESS;
    
    if((localX != 0XFFFF) && (localY != 0XFFFF))
    {
        hidMng.localHight = localX;
        hidMng.localWidth = localY;
    }
    if((remoteX != 0XFFFF) && (remoteY != 0XFFFF))
    {
        hidMng.screenHight = remoteX;
        hidMng.screenWidth = remoteY;
    }    
    if(remoteVH != 0XFF)
    {
        if((remoteVH>=IAP_HID_VH_V) && (remoteVH<=IAP_HID_VH_H))
            hidMng.screenVH = remoteVH;
        else
            status = HID_EVT_ILLEGAL_PARAM;
    }

    BtIapHidCheckParam();
    
    if(hidMng.localHight > hidMng.localWidth)
    {
           uint16 temp = hidMng.localHight;
           hidMng.localHight = hidMng.localWidth;
           hidMng.localWidth = temp;
    }

    if(hidMng.screenHight > hidMng.screenWidth)
    {
           uint16 temp = hidMng.screenHight;
           hidMng.screenHight = hidMng.screenWidth;
           hidMng.screenWidth = temp;
    }

    if(hidMng.screenVH == IAP_HID_VH_V)
    {
        //when the screen is vertical, the max x and y moving displacement.
        uint16 newWidth = hidMng.screenHight * hidMng.localHight / hidMng.screenWidth;

        hidMng.maxXDis = newWidth / MAX_PRESS_PERCENT;
        //hidMng->hid.maxXDis = hidMng->hid.localWidth / MAX_PRESS_PERCENT;
        hidMng.maxYDis = hidMng.localHight / MAX_PRESS_PERCENT;
    }
    else if(hidMng.screenVH = IAP_HID_VH_H)
    {
        //when the screen is horizontal, the max x and y moving displacement.
        hidMng.maxXDis = hidMng.localWidth / MAX_PRESS_PERCENT;
        hidMng.maxYDis = hidMng.localHight / MAX_PRESS_PERCENT;
    }
    IAPHIDlOGI("maxXDis: %.2x, maxYDis: %.2x \n", hidMng.maxXDis, hidMng.maxYDis);
    
    /*Anyway init screen again*/
    //BTAppHidInitTouchScreen();
    
    return status;
}


/************************************************************************
NAME:
*************************************************************************/
uint8 BtAppiPhoneSendReportResult(uint16 response)
{
    if(response == 0x0000)
    {
        hidMng.prevX = hidMng.wantX;
        hidMng.prevY = hidMng.wantY;
    }
    IAPHIDlOGI("prevX: %.2x, prevY: %.2x \n", hidMng.prevX, hidMng.prevY);

    hidMng.pendingCmd = IAP_HID_DATA_ASK_IDLE;

    return HID_EVT_SUCCESS;
}

static void BtIapHidCheckParam(void)
{
    if((hidMng.localHight==0) ||(hidMng.localWidth) ==0)
    {
        hidMng.localWidth = WRP_HID_DEFAULT_LOCAL_WIDTH;
        hidMng.localHight  = WRP_HID_DEFAULT_LOCAL_HIGHT;       
    }

    if((hidMng.screenHight==0) ||(hidMng.screenWidth) ==0)
    {
        hidMng.screenWidth = WRP_HID_DEFAULT_REMOTE_WIDTH;
        hidMng.screenHight  = WRP_HID_DEFAULT_REMOTE_HIGHT;       
    }

    if((hidMng.maxXDis ==0) || (hidMng.maxYDis==0))
    {
        if(hidMng.screenVH == IAP_HID_VH_V)
        {
            //when the screen is vertical, the max x and y moving displacement.
            uint16 newWidth = hidMng.screenHight * hidMng.localHight / hidMng.screenWidth;

            hidMng.maxXDis = newWidth / MAX_PRESS_PERCENT;
            //hidMng->hid.maxXDis = hidMng->hid.localWidth / MAX_PRESS_PERCENT;
            hidMng.maxYDis = hidMng.localHight / MAX_PRESS_PERCENT;
        }
        else if(hidMng.screenVH = IAP_HID_VH_H)
        {
            //when the screen is horizontal, the max x and y moving displacement.
            hidMng.maxXDis = hidMng.localWidth / MAX_PRESS_PERCENT;
            hidMng.maxYDis = hidMng.localHight / MAX_PRESS_PERCENT;
        }
    }
    
}
