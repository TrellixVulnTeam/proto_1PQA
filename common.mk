# Get the current OS and architecture
OS ?= $(shell uname -s)
# Default to i386 for now
#####CPU ?= $(shell uname -m)
CPU ?= i386

# Set the default compilers and flags
CC = gcc
CXX = g++
CFLAGS ?= -O3 -g -finline-limit=20000 -L$(ROOT)
CXXFLAGS ?= $(CFLAGS)

# Include platform-specific rules
include $(ROOT)/platforms/$(OS).$(CPU).mk

# Set the default shared library filename suffix
SHLIB_SUFFIX ?= so

# Don't build into subdirectories by default
DIRS ?=

# Don't require any libraries by default
LIBS ?= 

# Set the default include directories
INCLUDE_DIRS ?= $(ROOT)/include $(ROOT)/heaplayers $(ROOT)/heaplayers/util

# Recurse into subdirectories for the 'clean' and 'build' targets
RECURSIVE_TARGETS ?= clean build

# Build by default
all: build

# Just remove the targets
clean::
ifneq ($(TARGETS),)
	@rm -f $(TARGETS)
endif

# Set the default source and include files with wildcards
SRCS ?= $(wildcard *.c) $(wildcard *.cpp) $(wildcard *.cc) $(wildcard *.C)
OBJS ?= $(addprefix obj/, $(patsubst %.c, %.o, $(patsubst %.cpp, %.o, $(patsubst %.cc, %.o, $(patsubst %.C, %.o, $(SRCS))))))
INCLUDES ?= $(wildcard *.h) $(wildcard *.hpp) $(wildcard *.hh) $(wildcard *.H) $(wildcard $(addsuffix /*.h, $(INCLUDE_DIRS))) $(wildcard $(addsuffix /*.hpp, $(INCLUDE_DIRS))) $(wildcard $(addsuffix /*.hh, $(INCLUDE_DIRS))) $(wildcard $(addsuffix /*.H, $(INCLUDE_DIRS)))

# Generate flags to link required libraries and get includes
LIBFLAGS = $(addprefix -l, $(LIBS))
INCFLAGS = $(addprefix -I, $(INCLUDE_DIRS))

build:: $(TARGETS)

obj/%.o: %.c
	@mkdir -p obj
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

obj/%.o: %.cpp
	@mkdir -p obj
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -c $< -o $@
	
obj/%.o: %.cc
	@mkdir -p obj
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -c $< -o $@
	
obj/%.o: %.C
	@mkdir -p obj
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -c $< -o $@

$(filter %.$(SHLIB_SUFFIX), $(TARGETS)):: $(OBJS) $(INCLUDES)
	$(CXXLIB) $(CXXFLAGS) $(INCFLAGS) $(OBJS) -o $@ $(LIBFLAGS)

$(filter-out %.$(SHLIB_SUFFIX), $(TARGETS)):: $(OBJS) $(INCLUDES)
	$(CXX) $(CXXFLAGS) $(INCFLAGS) $(OBJS) -o $@ $(LIBFLAGS)

$(RECURSIVE_TARGETS)::
	@for dir in $(DIRS); do \
	  $(MAKE) -C $$dir $@; \
	done
