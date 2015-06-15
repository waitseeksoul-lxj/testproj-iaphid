LOCAL_PATH := $(call my-dir)

# include $(CLEAR_VARS)
# LOCAL_MODULE_TAGS := optional
# LOCAL_PREBUILT_LIBS := libbt_stack.so
# include $(BUILD_MULTI_PREBUILT)

# Prebuild
include ${CLEAR_VARS}
LOCAL_LIB_PATH      :=
LOCAL_MODULE_TAGS   := optional
LOCAL_PREBUILT_LIBS := /lib/arm/libbt_stack_bluetec.a
ifeq ($(TARGET_ARCH), x86)
LOCAL_PREBUILT_LIBS := /build/x86/libbt_stack_bluetec.a
endif
include ${BUILD_MULTI_PREBUILT}

# For libbt_stack
include $(CLEAR_VARS)
include ${LOCAL_PATH}/local-cflags.mk
LOCAL_MODULE        := libbt_stack
LOCAL_MODULE_TAGS   := optional
LOCAL_C_INCLUDES    :=${LOCAL_PATH}/lib/include \
					  ${LOCAL_PATH}/../bt/18.2.4/pset_app/include \
                      ${LOCAL_PATH}/wrapper/src/include \
                      ${LOCAL_PATH}/wrapper/src/avp \
                      ${LOCAL_PATH}/wrapper/src/status \
                      ${LOCAL_PATH}/wrapper/src/gen \
                      ${LOCAL_PATH}/wrapper/src/message \
                      ${LOCAL_PATH}/wrapper/src/pan \
                      ${LOCAL_PATH}/wrapper/src/hfp \
                      ${LOCAL_PATH}/wrapper/src/pbdl \
                      ${LOCAL_PATH}/wrapper/src/spp \
                      ${LOCAL_PATH}/wrapper/src/hid \
		      ${LOCAL_PATH}/wrapper/src/cm \
		      ${LOCAL_PATH}/log \


LOCAL_SRC_FILES         := $(sort $(call all-c-files-under, wrapper))
LOCAL_SRC_FILES         += log/bt_log.cpp
LOCAL_STATIC_LIBRARIES 	:= libbt_stack_bluetec
LOCAL_SHARED_LIBRARIES  := liblog libncore
LOCAL_LDFLAGS           := -lpthread \
						   -lrt \
						   -ldl \
						   -lutil \

include $(BUILD_SHARED_LIBRARY)



# For config files
include $(CLEAR_VARS)
LOCAL_MODULE       := bt_patch.hcd
LOCAL_MODULE_CLASS := ETC
LOCAL_MODULE_TAGS  := optional
LOCAL_MODULE_PATH  := $(TARGET_OUT)/etc/bluetooth
LOCAL_SRC_FILES    := utils/conf/bt_patch.hcd
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE       := bt_stack.conf
LOCAL_MODULE_CLASS := ETC
LOCAL_MODULE_TAGS  := optional
LOCAL_MODULE_PATH  := $(TARGET_OUT)/etc/bluetooth
LOCAL_SRC_FILES    := utils/conf/bt_stack.conf
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE       := bt_vendor.conf
LOCAL_MODULE_CLASS := ETC
LOCAL_MODULE_TAGS  := optional
LOCAL_MODULE_PATH  := $(TARGET_OUT)/etc/bluetooth
LOCAL_SRC_FILES    := utils/conf/bt_vendor.conf
#ifeq ($(TARGET_PRODUCT), dcu_0t)
#    LOCAL_SRC_FILES    := conf/bt_vendor_0t.conf
#endif
#ifeq ($(TARGET_PRODUCT), dcu_e2)
#    LOCAL_SRC_FILES    := conf/bt_vendor_e2.conf
#endif
include $(BUILD_PREBUILT)
#
#
## FOR TEST
#include $(CLEAR_VARS)
#LOCAL_MODULE            := bt_demo
#LOCAL_MODULE_TAGS       := eng
#LOCAL_C_INCLUDES        := $(LOCAL_PATH)/include
#LOCAL_SRC_FILES         := $(sort $(call all-c-files-under, app))
#LOCAL_SHARED_LIBRARIES  := libbt_stack
#include $(BUILD_EXECUTABLE)
include $(call all-subdir-makefiles)

