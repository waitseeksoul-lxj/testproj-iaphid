#include <stdio.h>
#include "./../pset_bt_iap_hid_if.h"


static void prtInfo()
{
    printf("0 exit!!!\n");
    printf("1 rescan\n");
    printf("2 get status \n");
    printf("3 yet no defined\n");
    printf("4 yet no defined\n");
    printf("5 yet no defined\n");
}

static int getNum()
{
    char getStr[100];
    int ret = 0;
    printf("Please input number: \n");
    scanf("%s", getStr);
    ret = atoi(getStr);
    printf("ret = [%d]\n", ret);
    return ret;
}

int  main(int argc, char **argv)
{

    uint8 flag = 0x01;

    printf("-------------------------enter main -------------------------\n");

    printf(" gupnp is running \n ");

    uint8 data[1024];
    uint16 length = 1024;
    uint8 adjust = 0x00;

    BtAppiPhoneHidSettingReq(400, 800, 1024, 1096, 0x02);

    //BtAppiPhoneHidReportReq(0x01, 400, 200, 0x0000, 0x01, data, length, adjust);

    while(flag){
        prtInfo();
        int type =  getNum();
        switch(type){
        case 1:
        {
            int xbit;
            int ybit;
            printf("please input the x, y bit map\n");
            scanf("%d", &xbit);
            scanf("%d", &ybit);
            BtAppiPhoneHidReportReq(0x01, xbit, ybit, 0x0000, 0x00, data, &length, &adjust);

            if(length > 0)
            {
                printf("the length is : %x %d\n", length, length);
                int i = 0;
                for(; i < length; i++)
                {
                    printf("%x  %d \n", data[i], data[i]);
                }
                printf("the adjust is: %d %x\n", adjust, adjust);
            }
            
            uint16 result = 0x00;
            printf("set send result. \n");
            BtAppiPhoneSendReportResult(result);

            BtAppiPhoneHidReportReq(0x00, xbit, ybit, 0x0000, 0x00, data, &length, &adjust);

            if(length > 0)
            {
                printf("the length is : %x %d\n", length, length);
                int i = 0;
                for(; i < length; i++)
                {
                    printf("%x  %d \n", data[i], data[i]);
                }
                printf("the adjust is: %d %x\n", adjust, adjust);
            }
            
            result = 0x00;
            printf("set send result. \n");
            BtAppiPhoneSendReportResult(result);

            break;
        }
        case 2:
        {
            printf("need to adjust to call init func. \n");
            BtAppiPhoneHidInitTouchScreen(data, &length);
            if(length > 0)
            {
                printf("the length is : %x %d\n", length, length);
                int i = 0;
                for(; i< length; i++)
                {
                    printf("%x  %d \n", data[i], data[i]);
                }
            }

            uint16 result = 0x00;
            printf("set send result. \n");
            BtAppiPhoneSendReportResult(result);
            
            break;
        }
        case 3:
        {
            uint8  desc[100];
            uint16 length = 0;
            printf("get the report descriptor: \n");
            BtAppiPhoneHidGetReportDesciptor(desc, &length);
            if(length > 0)
            {
                
                printf("the length is : %x %d\n", length, length);
                int i = 0;
                for(; i< length; )
                {
                    printf("%.2x  %.2x \n", desc[i], desc[i+1]);
                    i += 2;
                }
            }    

            break;   
        }
        case 4:
        {
                uint16 result = 0x00;
                printf("set send result. \n");
                BtAppiPhoneSendReportResult(result);
        }
        case 5:
            break;
        case 0:
            flag = 0x00;
        default:
            break;
        }
    }


    printf("exit while(flag) %d\n", __LINE__);

    printf("-------------------------exit main process-------------------------\n");

    return 0x00;
}
