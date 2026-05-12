#include "gl_renderer.h"
#include "File.h"
#include "Input.h"
#include "OpenGLSetup.h"

namespace CelesteGame {

	static void APIENTRY GLDebugCallbackFn(GLenum source, GLenum type, GLuint id, GLenum severity,
		GLsizei length, const GLchar* message, const void* user)
	{
		if (severity == GL_DEBUG_SEVERITY_LOW ||
			severity == GL_DEBUG_SEVERITY_MEDIUM || 
			severity == GL_DEBUG_SEVERITY_HIGH)
		{
			SD_ASSERT(false, "OpenGL Error: {}", message);
		}
		else
		{
			SD_TRACE( "{}", message);
		}
	}

	struct GLContext
	{
		GLuint ProgramID;
		// I might need it
		GLuint QuadVAO = 0;
	};

	static GLContext g_GlContext;

	static bool CompileShader(GLuint shaderID, const char* source, const char* shaderName)
	{
		glShaderSource(shaderID, 1, &source, nullptr);
		glCompileShader(shaderID);

		int success;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			constexpr int LOG_SIZE = 2048;
			char shaderLog[LOG_SIZE] = {};
			glGetShaderInfoLog(shaderID, LOG_SIZE, nullptr, shaderLog);
			SD_ASSERT(false, "Failed to compile {} Shader: {}", shaderName, shaderLog);
			return false;
		}
		return true;
	}

	bool GLInit(BumpAllocator& transientStorage)
	{
		LoadGlFunctions();

		glDebugMessageCallback(&GLDebugCallbackFn, nullptr);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glEnable(GL_DEBUG_OUTPUT);

		GLuint vertShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		{
			std::filesystem::path vertShaderPath = "assets/shaders/quad.vert";
			std::filesystem::path fragShaderPath = "assets/shaders/quad.frag";

			

			size_t vertSize = std::filesystem::file_size(vertShaderPath);
			size_t fragSize = std::filesystem::file_size(fragShaderPath);

			char* vertMem = static_cast<char*>(transientStorage.alloc(vertSize + 1));
			char* fragMem = static_cast<char*>(transientStorage.alloc(fragSize + 1));

			auto vertResult = ReadFile(vertShaderPath, std::span<char>{vertMem, vertSize + 1});
			auto fragResult = ReadFile(fragShaderPath, std::span<char>{fragMem, fragSize + 1});

			if (!vertResult || !fragResult)
			{
			
				SD_ASSERT(false, "Failed to load shaders: vert: {} frag: {}",
					vertResult ? "Success" : "Fail",
					fragResult ? "Success" : "Fail");
				return false;
			}

			if (!CompileShader(vertShaderID, vertResult->data(), "Vertex") ||
				!CompileShader(fragShaderID, fragResult->data(), "Fragment"))
			{
				return false;
			}

			g_GlContext.ProgramID = glCreateProgram();
			glAttachShader(g_GlContext.ProgramID, vertShaderID);
			glAttachShader(g_GlContext.ProgramID, fragShaderID);
			glLinkProgram(g_GlContext.ProgramID);

			glDetachShader(g_GlContext.ProgramID, vertShaderID);
			glDetachShader(g_GlContext.ProgramID, fragShaderID);
			glDeleteShader(vertShaderID);
			glDeleteShader(fragShaderID);
		}

		
		glGenVertexArrays(1, &g_GlContext.QuadVAO);
		glBindVertexArray(g_GlContext.QuadVAO);
		
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL); 
	
		glUseProgram(g_GlContext.ProgramID);
		return true;
	}

	void GLRender()
	{
		glClearColor(119.0f / 255.0f, 33.0f / 255.0f, 111.0f / 255.0f, 1);
		glClearDepth(0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, g_InputState.ScreenSizeX, g_InputState.ScreenSizeY);

		
		//glBindVertexArray(g_GlContext.QuadVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}


	
}