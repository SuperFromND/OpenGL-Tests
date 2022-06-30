everything:
	make tri
	make hex

tri:
	g++ src/triangle.cpp -o bin/triangle.exe -mwindows -lmingw32 -lSDL2main -lSDL2 -lopengl32
    
hex:
	g++ src/hexagon.cpp -o bin/hexagon.exe -mwindows -lmingw32 -lSDL2main -lSDL2 -lopengl32