CXX := g++
LDFLAGS := -lSDL2

ifeq ($(OS),Windows_NT)
	LDFLAGS := -lmingw32 -lSDL2main $(LDFLAGS) -lopengl32
else
	LDFLAGS := $(LDFLAGS) -lGL
endif

everything: dir
	make tri
	make hex

tri:
	$(CXX) src/triangle.cpp -o bin/triangle.exe $(LDFLAGS)
    
hex:
	$(CXX) src/hexagon.cpp -o bin/hexagon.exe $(LDFLAGS)

dir:
	if [ ! -d "./bin" ]; then mkdir -p bin; fi