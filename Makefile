WX_CONFIG = `wx-config --cppflags --libs`
APP = pi
objects = main.o

all: $(objects)
	g++ -o $(APP) $(objects) $(WX_CONFIG)

main.o: main.cxx
	g++ -c main.cxx $(WX_CONFIG)
	
.PHONY: clean
clean:
	rm $(APP) $(objects)
