LOCAL_PATH := $(call my-dir)


# compile IAP HID lib: libbt_iaphid

include $(CLEAR_VARS)

LOCAL_MODULE        := libbt_iaphid

LOCAL_MODULE_TAGS   := optional

LOCAL_C_INCLUDES    := ${LOCAL_PATH}/pset_bt_iap_hid_if.h\
                       ${LOCAL_PATH}/pset_bt_iap_hid_log.h\
                       ${LOCAL_PATH}/pset_bt_iap_hid_private.h\
                       ${LOCAL_PATH}/iap_hid_debug.h



LOCAL_SRC_FILES         := pset_bt_iap_hid_if.c
LOCAL_SRC_FILES         += iap_hid_log.cpp
#LOCAL_STATIC_LIBRARIES 	:= libbt_stack_bluetec

LOCAL_SHARED_LIBRARIES  := liblog libncore
LOCAL_LDFLAGS           := -lpthread \
                           -lrt \
                           -ldl \
                           -lutil \

include $(BUILD_SHARED_LIBRARY)




# complie test for libbt_iaphid

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional

LOCAL_MODULE    := test_iaphid

LOCAL_C_INCLUDES += $(LOCAL_PATH)/pset_bt_iap_hid_if.h\


LOCAL_SRC_FILES := test/test_iap_hid.c


LOCAL_SHARED_LIBRARIES := libbt_iaphid


include $(BUILD_EXECUTABLE)



include $(call all-subdir-makefiles)

