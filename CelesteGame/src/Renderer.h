#pragma once

#include "Logger.h"
//TEMP
#include "BumpAllocator.h"

namespace CelesteGame {

	bool GLInit(BumpAllocator& transientStorage);
	void GLRender();

	void* PlatformLoadGLFunction(const char* fnName);
	void LoadGlFunctions();

}


