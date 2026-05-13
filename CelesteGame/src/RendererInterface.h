#pragma once
#include "Math.h"
#include "Assets.h"

namespace CelesteGame {

	constexpr int MAX_TRASNSFORMS = 1000;

	struct Transform
	{
		IVec2 AtlasOffset;
		IVec2 SpriteSize;
		Vec2 Pos;
		Vec2 Size;
	};

	struct RenderData
	{
		int transformCount = 0;
		Transform trasforms[MAX_TRASNSFORMS];
	};

	extern RenderData g_RenderData;

	void DrawSprite(SpriteID spiteID, Vec2 pos, Vec2 size);

}

