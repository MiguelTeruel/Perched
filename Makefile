################################################################################
### MACROS
################################################################################

# COMPILATION MACRO
# $(1) = compiler, $(2) = object file to generate,
# $(3) = src file, $(4) = additional dependencies,
# $(5) = flags

define COMPILE
$(2) : $(3) $(4)
	$(1) -c -o $(2) -g -c $(3) $(5) -std=c++20
endef

# .c to .o EXCHANGER
# $(1) = source file

define C2O
$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(patsubst $(SRC)%, $(OBJ)%, $(1))))
endef

# .c to .o EXCHANGER
# $(1) = source file

define C2H
$(patsubst %.c,%.h,$(patsubst %.cpp,%.hpp,$(1)))
endef

################################################################################
### CONFIG
################################################################################

IrrlichtHome := ./irrlicht-1.8.5
FmodHome := ./fmod

APP := Perched
CCFLAGS := -Wall -pedantic -I$(IrrlichtHome)/include -fsanitize=address -I$(FmodHome)/fmod/core/inc -I$(FmodHome)/fmod/studio/inc -I$(FmodHome)/fmod/fsbank/inc
CCFLAGS := $(CCFLAGS)
CC := ccache g++
C := gcc
MKDIR := mkdir -p
SRC := src
OBJ := obj

SYSTEM := Linux
LIBS := -L$(IrrlichtHome)/lib/$(SYSTEM) -lIrrlicht -lassimp -lglfw -lX11 -lXext -lGL -ldl -Wl,-rpath=lib/ -fsanitize=address,undefined
LIB_FMOD := -L$(FmodHome)/fmod/core/lib/x86_64 -L$(FmodHome)/fmod/studio/lib/x86_64 -lfmod -lfmodstudio -lGL -lm -lpthread -ldl -lrt -lX11

LIBPATH := -Wl,-rpath=lib/

ifdef RELEASE
	CCFLAGS += -g
else
	CCFLAGS += -O3 -ffast-math
endif

ALLCPPS := $(shell find $(SRC) -type f -iname *.cpp)
ALLCS := $(shell find $(SRC) -type f -iname *.c)
ALLOBJ := $(foreach F,$(ALLCPPS) $(ALLCS),$(call C2O,$(F)))
SUBDIRS := $(shell find $(SRC) -type d)
OBJSUBDIRS := $(patsubst $(SRC)%, $(OBJ)%, $(SUBDIRS))


#.PHONY EVITA QUE SE ACTUALICE CONSTANTEMENTE CADA VEZ QUE SE LLAME A MAKE
.PHONY: info
.PHONY: clean

$(APP) : $(OBJSUBDIRS) $(ALLOBJ)
	$(CC) -o $(APP) $(ALLOBJ) $(LIBS) $(LIB_FMOD) $(LIBPATH)

# REGLAS GENERADAS PARA TODOS LOS .c y .cpp
$(foreach F, $(ALLCPPS),$(eval $(call COMPILE,$(CC),$(call C2O,$(F)),$(F),$(call H2O,$(F),$(CCFLAGS)))))
$(foreach F, $(ALLCS),$(eval $(call COMPILE,$(C),$(call C2O,$(F)),$(F),$(call H2O,$(F),$(CFLAGS)))))

#dir: ME OFRECE INFORMACION DE LAS MACROS QUE VOY CREANDO, PARA COMPROBAR QUE FUNCIONAN.

info :
	$(info $(SUBDIRS))
	$(info $(OBJSUBDIRS))
	$(info $(ALLCPPS))
	$(info $(ALLCS))
	$(info $(ALLCSOBJ))
	$(info $(ALLCPPSOBJ))

clean:
	$(RM) $(ALLOBJ)

$(OBJSUBDIRS) :
	$(MKDIR) $(OBJSUBDIRS)
