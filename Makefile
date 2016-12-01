CFLAGS = -std=c++11 -I . -framework GLUT -framework OpenGL

main: main.cpp
	g++ $(CFLAGS) -o tsukihi main.cpp

em: main.cpp
	emcc $(CFLAGS) -o tsukihi.html main.cpp
