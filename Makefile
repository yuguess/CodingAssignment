CC=g++ 
CFLAGS=-std=c++0x
LDFLAGS=-L./
#LDFLAGS = -L/usr/local/lib -L/usr/lib -L/home/dalong/infrastructure/bin/debug -lz -lpthread -lrt -lconnector -llogger -lnetworks -lxsim -ldatamanip -lcommonutils -lsnappy 
DEBUG = -g
BIN=./

INCLUDE=./

SOURCES= Main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=$(BIN)/colDiff

all: $(EXECUTABLE)  

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) -c $(CFLAGS) $(DEBUG)  $(INCLUDE) $< -o $@

# --- remove binary and executable files
clean:
	rm $(OBJECTS) $(EXECUTABLE)
