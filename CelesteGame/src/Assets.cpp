#include "Assets.h"
#include "Logger.h"

namespace CelesteGame
{
	std::string SpriteIDToString(SpriteID spriteID)
	{
		switch (spriteID)
		{
		case SpriteID::DICE:  return "DICE";
		case SpriteID::COUNT: return "COUNT";
		default:			  return "INVALID SPRITE TYPE";
		}
	}

	Sprite GetSptrite(SpriteID spriteID)
	{
		Sprite sprite = {};

		switch (spriteID)
		{
		case SpriteID::DICE:
			sprite.AtlasOffset = { 16, 0 };
			sprite.SpriteSize = { 16, 16 };
			return sprite;

		default:
			SD_ASSERT(false, "INVALID SPRITE ID: {}", SpriteIDToString(spriteID));
			return sprite;
		}


	}
}