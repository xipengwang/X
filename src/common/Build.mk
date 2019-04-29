SRCS = $(shell ls *.c)
OBJS = $(SRCS:%.c=%.o)
HEADERS = std_util.h

CFLAGS := $(CFLAGS_STD) -I..
LDFLAGS := $(LDFLAGS_STD)
DEPS := $(DEPS_STD)
HDEPS := $(HEADERS)

include $(BUILD_COMMON)

all: $(LIB_PATH)/libcommon.a
	@/usr/bin/true

$(LIB_PATH)/libcommon.a: $(OBJS) $(DEPS)
	@$(AR) rcs $@ $^

clean:
	@rm -rf *.o $(LIB_PATH)/libcommon.a
