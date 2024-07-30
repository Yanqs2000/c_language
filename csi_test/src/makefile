LICHEE_DIR 	:= /data/lichee
SDK_LIB 	:=
INCLUDE 	+=
CFLAGS  	+= -g -Wall -O3 $(DEFINES) $(INCLUDE)
LIBS    	+= -lm
LDFLAGS 	:=
CXXFLAGS	:= $(CFLAGS)
SOURCE  	:= $(wildcard *.c) $(wildcard *.cpp)
OBJS    	:= $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCE)))
TARGET  	:= csi_test

LICHEE_OUT_SYS	= $(LICHEE_DIR)/out/sun8iw11p1/linux/common/buildroot
CC		= $(LICHEE_OUT_SYS)/host/opt/ext-toolchain/bin/arm-linux-gnueabihf-gcc

.PHONY : everything objs clean distclean rebuild

all : $(TARGET)

objs : $(OBJS)

rebuild: distclean all

clean :
	rm -rf *~
	rm -rf *.o

distclean : clean
	rm -rf $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS) $(LIBS)
