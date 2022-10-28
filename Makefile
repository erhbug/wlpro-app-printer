# This Makefile is provided as an example of how to build a process that can
# communicate with a Storyboard application.  It may require modifications in
# order to build on your host system.  Please see ReadMe.html for a complete
# explanation

SB_ROOT = /opt/poky/3.1.3/sysroots/cortexa9t2hf-neon-poky-linux-gnueabi/
SB_INC = -I$(SB_ROOT)/include
SB_LIB = -L$(SB_ROOT)/usr/lib

# Windows user add this
#CFLAGS+= -DGRE_TARGET_OS_win32

# Linux users add this 
#CFLAGS+= -DGRE_TARGET_OS_linux -mfloat-abi=hard
CXXFLAGS += -DGRE_TARGET_OS_linux -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard
SB_LIB += -lpthread -lsqlite3

all: main.c
	$(CC) $(CXXFLAGS) $(SB_INC) -Og -g -Wall main.c serial.c app_input.c -o printer $(SB_LIB)
clean:
	rm -f printer 
