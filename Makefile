TITLEID     := VGLCAMERA
TARGET		:= trooper
SOURCES		:= ./src
			
INCLUDES	:= -Iinclude

LIBS = -lvitaGL -lSceLibKernel_stub -lSceAppMgr_stub -lSceAppUtil_stub -lmathneon \
	-lc -lSceCommonDialog_stub -lm -lSceGxm_stub -lSceDisplay_stub -lSceSysmodule_stub \
	-lvitashark -lSceShaccCg_stub -lSceKernelDmacMgr_stub -lstdc++ -lSceCtrl_stub \
	-ltoloader -lSceShaccCgExt -ltaihen_stub

CFILES   := $(foreach dir,$(SOURCES), $(wildcard $(dir)/*.c))
CPPFILES   := $(foreach dir,$(SOURCES), $(wildcard $(dir)/*.cpp))
BINFILES := $(foreach dir,$(DATA), $(wildcard $(dir)/*.bin))
OBJS     := $(addsuffix .o,$(BINFILES)) $(CFILES:.c=.o) $(CPPFILES:.cpp=.o) 

FLAGS = HAVE_VITA3K_SUPPORT=1 LOG_ERRORS=2 HAVE_SHARK_LOG=1 DEBUG_GLSL_TRANSLATOR=1 DEBUG_GLSL_PREPROCESSOR=1

PREFIX  =  arm-vita-eabi
CC      = $(PREFIX)-gcc
CXX      = $(PREFIX)-g++
CFLAGS  = -g -Wl,-q -O2 -ftree-vectorize
CXXFLAGS  = $(CFLAGS) -fno-exceptions -std=gnu++11 -fpermissive -fexceptions $(INCLUDES)
ASFLAGS = $(CFLAGS)

all: $(TARGET).vpk

$(TARGET).vpk: eboot.bin
	vita-mksfoex -s TITLE_ID=$(TITLEID) "$(TARGET)" param.sfo
	vita-pack-vpk -s param.sfo -b eboot.bin \
		-a resources/models/stormtrooper.obj=resources/models/stormtrooper.obj \
		-a resources/models/stormtrooper.png=resources/models/stormtrooper.png \
		-a resources/textures/wood-box.jpg=resources/textures/wood-box.jpg \
		-a resources/shaders/light.vert=resources/shaders/light.vert \
		-a resources/shaders/light.frag=resources/shaders/light.frag \
		-a resources/shaders/phong.vert=resources/shaders/phong.vert \
		-a resources/shaders/phong.frag=resources/shaders/phong.frag $@

eboot.bin: $(TARGET).velf
	vita-make-fself -s $< eboot.bin	
	
%.velf: %.elf
	vita-elf-create $< $@
	
$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@
	
clean:
	@rm -rf *.velf *.elf *.vpk $(OBJS) param.sfo eboot.bin
