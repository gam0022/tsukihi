#ifndef _GL_WINDOW_
#define _GL_WINDOW_

#include <GLFW/glfw3.h>

#include <string>
#include <cstdlib>
#include <cstdio>
#include <vector>

#include "math.h"
#include "material.h"

#define SCREEN_WIDTH  (256)
#define SCREEN_HEIGHT (256)



namespace tsukihi {
	static constexpr char s_vShaderStr[] =  
		"attribute vec4 a_position;   \n"
		"attribute vec2 a_texCoord;   \n"
		"varying vec2 v_texCoord;     \n"
		"void main()                  \n"
		"{                            \n"
		"   gl_Position = a_position; \n"
		"   v_texCoord = a_texCoord;  \n"
		"}                            \n";

	static constexpr char s_fShaderStr[] =  
		"#ifdef GL_ES\n"
		"precision mediump float;                            \n"
		"#endif\n"
		"varying vec2 v_texCoord;                            \n"
		"uniform sampler2D s_texture;                        \n"
		"void main()                                         \n"
		"{                                                   \n"
		"  gl_FragColor = texture2D( s_texture, v_texCoord );\n"
		"}                                                   \n";

	static constexpr GLfloat	s_vertices[] = {
		-1.0f,  1.0f, 0.0f,		// Position 0
		0.0f,  0.0f,			// TexCoord 0
		-1.0f, -1.0f, 0.0f,
		0.0f,  1.0f,
		1.0f, -1.0f, 0.0f,
		1.0f,  1.0f,
		1.0f,  1.0f, 0.0f,
		1.0f,  0.0f,
	};

	static constexpr GLushort	s_indices[] = { 0, 1, 3, 2 };
	static GLubyte pixels[ SCREEN_WIDTH * SCREEN_HEIGHT * 3 ];

	class GLWindow {
    public:

		GLFWwindow* window;
		GLuint	programObject;
		GLuint	vertexShader, fragmentShader;
		GLuint	textureId;

		GLuint load_shader( GLenum type, const char *src )
		{
			GLuint	shader;

			shader = glCreateShader( type );
			glShaderSource( shader, 1, &src, 0 );
			glCompileShader( shader );

			return shader;
		}

		GLuint setup_tex()
		{
			int		i, j, k;
			GLuint		textureId;

			glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
			glGenTextures( 1, &textureId );
			glBindTexture( GL_TEXTURE_2D, textureId );
			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
			glActiveTexture( GL_TEXTURE0 );
			glBindTexture( GL_TEXTURE_2D, textureId );

			return textureId;
		}

		void setup_vtx( GLuint positionLoc, GLuint texCoordLoc, GLuint samplerLoc )
		{
			GLuint	s_vertexPosObject, s_indexObject;
			glGenBuffers(1, &s_vertexPosObject);
			glBindBuffer(GL_ARRAY_BUFFER, s_vertexPosObject );
			glBufferData(GL_ARRAY_BUFFER, sizeof(s_vertices), s_vertices, GL_STATIC_DRAW );

			glGenBuffers(1, &s_indexObject);
			glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, s_indexObject );
			glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(s_indices), s_indices, GL_STATIC_DRAW );

			glBindBuffer(GL_ARRAY_BUFFER, s_vertexPosObject);
			glVertexAttribPointer( positionLoc, 3, GL_FLOAT, GL_FALSE, 5 * 4, 0 );
			glVertexAttribPointer( texCoordLoc, 2, GL_FLOAT, GL_FALSE, 5 * 4, (const GLvoid *)(3 * 4) );
			glEnableVertexAttribArray( positionLoc );
			glEnableVertexAttribArray( texCoordLoc );

			glUniform1i( samplerLoc, 0 );
			glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, s_indexObject );
		}

		void display(const Color *image) {
			if (image != NULL) {
				store_image_to_pixels(image, SCREEN_WIDTH, SCREEN_HEIGHT, pixels);
			}
			glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pixels );

			glClear(GL_COLOR_BUFFER_BIT);
			glDrawElements( GL_TRIANGLE_STRIP, sizeof(s_indices)/sizeof(s_indices[0]), GL_UNSIGNED_SHORT, 0 );

			glfwSwapBuffers(window);
		}

		GLWindow() {
			GLuint	positionLoc, texCoordLoc, samplerLoc;

			// init GLFW
			glfwInit();
			window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "tsukihi", nullptr, nullptr);
			if (!window) {
				glfwTerminate();
			}
			glfwMakeContextCurrent(window);

			// init scene
			vertexShader = load_shader( GL_VERTEX_SHADER, s_vShaderStr );
			fragmentShader = load_shader( GL_FRAGMENT_SHADER, s_fShaderStr );

			programObject = glCreateProgram();
			glAttachShader( programObject, vertexShader );
			glAttachShader( programObject, fragmentShader );
			glLinkProgram( programObject );
			glUseProgram( programObject );

			positionLoc = glGetAttribLocation( programObject, "a_position" );
			texCoordLoc = glGetAttribLocation( programObject, "a_texCoord" );
			samplerLoc = glGetUniformLocation( programObject, "s_texture" );

			textureId = setup_tex();
			setup_vtx( positionLoc, texCoordLoc, samplerLoc );
		}

		~GLWindow() {
			glDeleteTextures(1, &textureId);
			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);
			glDeleteProgram(programObject);
		}
	};
};

#endif
