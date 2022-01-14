CC = g++
NAME = jspec
VERSION = $(shell python3-config --extension-suffix)
TARGET_LIB = $(NAME)$(VERSION)

INCDIR = jspec2/include
LIBDIR = jspec2/lib
PYTHON_INC = $(shell python3 -m pybind11 --includes)
CFLAGS = -O3 -Wall -shared -std=c++14 -fPIC $(PYTHON_INC) -I$(INCDIR)

#LIBS = -lm -lgsl -lgslcblas
#LIBS =  -L$(LIBDIR) -s -Wl,-rpath=$(LIBDIR) -lm -l:libmuparser.so.2 -lgsl -lgslcblas
LIBS =  -L$(LIBDIR) -s -Wl,-rpath=$(LIBDIR) -lm -lgsl -lgslcblas

SRC = $(wildcard src/*.cc)
SRC += $(wildcard jspec2/src/*.cc)
SRC := $(filter-out jspec2/src/main.cc, $(SRC))
OBJ = $(SRC:.cc=.o)
DEPS = $(wildcard $(INCDIR)/*.h)

#$(info $$SRC is [${SRC}])
#$(info $$OBJ is [${OBJ}])
#$(info $$CFLAGS is [${CFLAGS}])

.PHONE: all
all = $(TARGET_LIB)

$(TARGET_LIB): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

%.o: %.cc $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJ)
