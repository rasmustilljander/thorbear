# ----------------------------------------------------------------------
#
# This makefile has been automatically generated by WinGDB 2.3, build 1505
# Do not edit.
#
# Project: TowardsTheSky
#
# ----------------------------------------------------------------------

PLATFORM=unix

UNAME=$(shell uname -o)

ifeq ("$(BUILD_CONFIGURATION)","")
	BUILD_CONFIGURATION=Debug
endif

CC= gcc
CXX= g++
AR= ar
CFLAGS= -g
CXXFLAGS= -g -iquote./source/ -iquote./source/Fmod/inc/
ARFLAGS= cru
LDFLAGS= -lX11 -lpthread -lglfw -lGLEW -lGLU -lGL -lfmodex64
RESULT=spaceout
INTERMEDIATE_DIR=./obj
DESTINATION_DIR=.

RM= rm -f
MKDIR= mkdir -p
INTERMEDIATE_DIR_MK=./obj
DESTINATION_DIR_MK=.

EXCLUDES= %Windows.cpp %Win.cpp source/D3DX_Graphics/%.cpp
SOURCEPATHS= $(filter-out $(EXCLUDES), $(wildcard source/*.cpp) $(wildcard source/*/*.cpp))
SOURCES= $(notdir $(SOURCEPATHS))
HEADERS= $(wildcard source/*.h) $(wildcard source/*/*.h)

VPATH= $(INTERMEDIATE_DIR)

OBJECTNAMES=$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCEPATHS)))
OBJECTPATHS=$(addprefix $(INTERMEDIATE_DIR)/,$(OBJECTNAMES))

$(DESTINATION_DIR)/$(RESULT): $(OBJECTNAMES)
ifeq ("$(wildcard $(DESTINATION_DIR) )","")
	-$(MKDIR) $(DESTINATION_DIR_MK)
endif
	$(CXX) $(CXXFLAGS) $(SYSROOTFLAGS) $(OBJECTPATHS) -o $@ $(LDFLAGS)

$(INTERMEDIATE_DIR)/spaceout.d: $(SOURCES) $(HEADERS)
ifeq ("$(wildcard $(DESTINATION_DIR) )","")
	-$(MKDIR) $(DESTINATION_DIR_MK)
endif
ifeq ("$(wildcard $(INTERMEDIATE_DIR) )","")
	-$(MKDIR) $(INTERMEDIATE_DIR_MK)
endif
	$(CXX) $(CXXFLAGS) -MM $(SOURCEPATHS) > $@

-include $(INTERMEDIATE_DIR)/spaceout.d

clean:
	$(RM) $(DESTINATION_DIR)/$(RESULT)
	$(RM) $(INTERMEDIATE_DIR)/spaceout.d
	$(RM) $(OBJECTPATHS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $(INTERMEDIATE_DIR)/$@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $(INTERMEDIATE_DIR)/$@ $<
