LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE:= libsoxr
LOCAL_SRC_FILES :=soxr/soxr.c \
soxr/data-io.c \
soxr/dbesi0.c \
soxr/filter.c \
soxr/fft4g64.c \
soxr/cr.c \
soxr/cr32.c \
soxr/fft4g32.c \
soxr/cr64.c \
soxr/vr32.c \
soxr/cr32s.c \
soxr/pffft32s.c \
soxr/util32s.c

LOCAL_C_INCLUDES :=$(LOCAL_PATH)/soxr
LOCAL_LDLIBS+=
LOCAL_CFLAGS +=-pie -fPIE -fPIC -DSOXR_LIB -DSOXR_VISIBILITY -Dsoxr_lsr_EXPORTS -mfloat-abi=softfp -mfpu=neon -v
LOCAL_LDFLAGS +=-pie -fPIE -lz -llog
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE:= soxr-test
LOCAL_SRC_FILES:= $(LOCAL_PATH)/soxr.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/soxr
LOCAL_C_INCLUDES+=$(LOCAL_PATH)
LOCAL_STATIC_LIBRARIES:= libsoxr
LOCAL_LDLIBS+= -llog
LOCAL_CFLAGS+=-fPIE
LOCAL_LDFLAGS+=-fPIE -pie
include $(BUILD_SHARED_LIBRARY)
