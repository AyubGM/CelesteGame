#pragma once
#include "Math.h"
#include <string>
namespace CelesteGame {

	enum class SpriteID
	{
		DICE,

		COUNT
	};

	struct Sprite
	{
		IVec2 AtlasOffset;
		IVec2 SpriteSize;
	};
	
	std::string SpriteIDToString(SpriteID spriteID);
	Sprite GetSptrite(SpriteID spriteID);
	

}
