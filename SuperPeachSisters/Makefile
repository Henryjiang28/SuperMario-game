CC = g++
INCLUDES = -I/usr/X11/include/GL
LIBS = -L/usr/X11/lib -lglut -lGL -lGLU
STD = -std=c++17
CCFLAGS = -Wno-deprecated-declarations

OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))
HEADERS = $(wildcard *.h)

.PHONY: default all clean

PRODUCT = SuperPeachSisters 

all: $(PRODUCT)

%.o: %.cpp $(HEADERS)
	$(CC) -c $(STD) $(CCFLAGS) $(INCLUDES) $< -o $@

$(PRODUCT): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LIBS) -o $@

clean:
	rm -f *.o
	rm -f $(PRODUCT)
