#include "Renderer.h"
#include "File.h"
#include "Input.h"
#include "OpenGLSetup.h"
#include "stb_image.h"
#include "RendererInterface.h"
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
		GLuint ProgramID = 0;
		GLuint TextureID = 0;
		GLuint transformSBOID;
		GLuint ScreenSizeID = 0;
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
		SD_TRACE("Shader Compiled: {}", shaderName);
		return true;
	}

	static bool LoadTexture(std::filesystem::path& filePath)
	{
		std::string filePathString = filePath.string();
		SD_TRACE("Loading Texture: {}", filePathString);
		int width, height, channels;
		unsigned char* data = stbi_load(filePathString.c_str(), &width, &height, &channels, 4);
		if (!data)
		{
			SD_ASSERT(false, "Faild to load Texture: {}", filePathString);
			return false;
		}
		glGenTextures(1, &g_GlContext.TextureID);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, g_GlContext.TextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB8_ALPHA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);

		SD_TRACE("Texture Loaded: {}", filePathString);
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

			if (!CompileShader(vertShaderID, vertResult->data(), "QuadVertex") ||
				!CompileShader(fragShaderID, fragResult->data(), "QuadFragment"))
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
		
		// Texture Loading
		{
			std::filesystem::path texurePath = "assets/textures/TEXTURE_ATLAS.png";
			LoadTexture(texurePath);
		}

		// Transform Stroge Buffer
		{
			glGenBuffers(1, &g_GlContext.transformSBOID);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, g_GlContext.transformSBOID);
			CelesteGame::glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(Transform) * MAX_TRASNSFORMS,
				g_RenderData.trasforms, GL_DYNAMIC_DRAW);
		}

		// Uniforms
		{
			g_GlContext.ScreenSizeID = glGetUniformLocation(g_GlContext.ProgramID, "screenSize");
		}
		
		glEnable(GL_FRAMEBUFFER_SRGB);
		glDisable(0x809D); //disable multisampling
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_GREATER); 
	
		glUseProgram(g_GlContext.ProgramID);
		return true;
	}

	void GLRender()
	{
		glClearColor(119.0f / 255.0f, 33.0f / 255.0f, 111.0f / 255.0f, 1);
		glClearDepth(0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, g_InputState.ScreenSizeX, g_InputState.ScreenSizeY);
		//glViewport(0, 0, 1200,720);

		// Copy screenSize from CPU to GPU
		{
			Vec2 screenSize = { static_cast<float>(g_InputState.ScreenSizeX), 
				static_cast<float>(g_InputState.ScreenSizeY) };
			glUniform2fv(g_GlContext.ScreenSizeID, 1, &screenSize.X);
		}
		


		// Opaque Objects
		{
			CelesteGame::glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(Transform) * g_RenderData.transformCount,
				g_RenderData.trasforms);
			glDrawArraysInstanced(GL_TRIANGLES, 0, 6, g_RenderData.transformCount);
			g_RenderData.transformCount = 0;
		}
		
		glBindVertexArray(g_GlContext.QuadVAO);
		
	}


	
}