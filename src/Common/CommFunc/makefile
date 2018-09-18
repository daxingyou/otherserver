#
# makefile 
#

include ../../ServerEngine/makefile_lib

TAF_INCLUDE = ../../../tool/taf/taf/include

SOURCE_FILE:=$(wildcard *.cpp) $(wildcard *.c)
OBJ_FILE:=$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCE_FILE)))

all: $(OBJ_FILE)
	$(AR) q ../$(LIB_FILE) $(OBJ_FILE)

%.o:%.cpp
	$(CXX) $(CXX_FLAGS) -c $<  -I./  -I$(TAF_INCLUDE) $(INC_COMM) 

%.o:%.c
	$(CXX) $(CXX_FLAGS) -c $<  -I./ -I$(TAF_INCLUDE) $(INC_COMM) -I./

clean:
	rm -rf *.o

