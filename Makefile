CC=g++
CFLAGS=-c -Wall -std=c++11
SOURCES=main.cpp grid.cpp RNG.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=schelling.out

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *o all
