LICHEE_DIR 	:= /home/tl/workspace/relase_space/LinuxSDK
SDK_LIB 	:=
INCLUDE 	+=
CFLAGS  	+= -g -Wall -O3 $(DEFINES) $(INCLUDE)
LIBS    	+= -lm
LDFLAGS 	:=
CXXFLAGS	:= $(CFLAGS)
SOURCE  	:= $(wildcard *.c) $(wildcard *.cpp)
OBJS    	:= $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCE)))
TARGET  	:= csi_test

LICHEE_OUT_SYS	= $(LICHEE_DIR)/out/a40i_h/tla40if-evm/buildroot/buildroot
CC		= $(LICHEE_OUT_SYS)/host/bin/arm-linux-gnueabihf-gcc

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
