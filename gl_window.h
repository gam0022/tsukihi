#ifndef _GL_WINDOW_
#define _GL_WINDOW_

#ifdef EMSCRIPTEN
    #include <emscripten/emscripten.h>
    #define GL_GLEXT_PROTOTYPES
    #define EGL_EGLEXT_PROTOTYPES
#endif

#include <GLFW/glfw3.h>

#include <string>
#include <cstdlib>
#include <cstdio>
#include <vector>

#include "material.h"

namespace tsukihi {
	static constexpr char quadVertexShader[] = R"##(
		attribute vec4 position;
		attribute vec2 uv;
		varying vec2 vUv;
		void main() {
			gl_Position = position;
			vUv = uv;
		}
	)##";

	static constexpr char quaduFragmentShader[] =  R"##(
		varying vec2 vUv;
		uniform sampler2D texture;
		void main() {
			gl_FragColor = texture2D( texture, vUv );
		}
	)##";

	static constexpr GLfloat planeVertices[] = {
		-1.0f,  1.0f, 0.0f,	// position
		0.0f,  0.0f,		// uv
		-1.0f, -1.0f, 0.0f,
		0.0f,  1.0f,
		1.0f, -1.0f, 0.0f,
		1.0f,  1.0f,
		1.0f,  1.0f, 0.0f,
		1.0f,  0.0f,
	};

	static constexpr GLushort planeIndices[] = {0, 1, 3, 2};

	class GLWindow {
    public:
		int width, height;

		GLFWwindow* window;
		GLuint programObject;
		GLuint vertexShader, fragmentShader;
		GLuint textureId;
		GLubyte *pixels;

		GLuint loadShader( GLenum type, const char *src ) {
			GLuint shader;

			shader = glCreateShader( type );
			glShaderSource( shader, 1, &src, 0 );
			glCompileShader( shader );

			return shader;
		}

		GLuint setupTex() {
			GLuint textureId;

			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glGenTextures(1, &textureId);
			glBindTexture(GL_TEXTURE_2D, textureId);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textureId);

			return textureId;
		}

		void setupVtx(GLuint positionLoc, GLuint texCoordLoc, GLuint samplerLoc) {
			GLuint vertexPosObject, indexObject;

			glGenBuffers(1, &vertexPosObject);
			glBindBuffer(GL_ARRAY_BUFFER, vertexPosObject );
			glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW );

			glGenBuffers(1, &indexObject);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexObject);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(planeIndices), planeIndices, GL_STATIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, vertexPosObject);
			glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE, 5 * 4, 0);
			glVertexAttribPointer(texCoordLoc, 2, GL_FLOAT, GL_FALSE, 5 * 4, (const GLvoid *)(3 * 4));
			glEnableVertexAttribArray(positionLoc);
			glEnableVertexAttribArray(texCoordLoc);

			glUniform1i(samplerLoc, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexObject);
		}

		void display(const Color *image) {
			// Update Texture
			store_image_to_pixels(image, width, height, pixels);
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);

			// Draw
			glClear(GL_COLOR_BUFFER_BIT);
			glDrawElements(GL_TRIANGLE_STRIP, sizeof(planeIndices)/sizeof(planeIndices[0]), GL_UNSIGNED_SHORT, 0);

			// GLFW
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		GLWindow(const int width, const int height) : width(width), height(height) {
			// GLFW
			glfwInit();
			window = glfwCreateWindow(width, height, "tsukihi", nullptr, nullptr);
			if (!window) {
				glfwTerminate();
			}
			glfwMakeContextCurrent(window);
			glClearColor(0.0, 0.0, 0.0, 1.0);


			// OpenGL
			pixels = new GLubyte[width * height * 3];
			
			// shader
			vertexShader = loadShader( GL_VERTEX_SHADER, quadVertexShader );
			fragmentShader = loadShader( GL_FRAGMENT_SHADER, quaduFragmentShader );

			programObject = glCreateProgram();
			glAttachShader(programObject, vertexShader);
			glAttachShader(programObject, fragmentShader);
			glLinkProgram(programObject);
			glUseProgram(programObject);

			// texture
			textureId = setupTex();
			GLuint positionLoc = glGetAttribLocation(programObject, "position");
			GLuint texCoordLoc = glGetAttribLocation(programObject, "uv");
			GLuint samplerLoc  = glGetUniformLocation(programObject, "texture");
			setupVtx(positionLoc, texCoordLoc, samplerLoc);
		}

		~GLWindow() {
			// OpenGL
			glDeleteTextures(1, &textureId);
			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);
			glDeleteProgram(programObject);

			delete pixels;
			
			// GLFW
			glfwTerminate();
		}
	};
};

#endif
