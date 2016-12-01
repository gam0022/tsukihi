CFLAGS = -std=c++11 -I . -O2

EOPT = ASYNCIFY=1 USE_GLFW=3 LEGACY_GL_EMULATION=1		# Emscripten specific options
EOPTS = $(addprefix -s $(EMPTY), $(EOPT))	# Add '-s ' to each option

main: main.cpp
	g++ $(CFLAGS) -framework OpenGL -lglfw3 -o tsukihi main.cpp

em: main.cpp
	emcc $(CFLAGS) $(EOPTS) -o tsukihi.html main.cpp
