#include "RendererInterface.h"

namespace CelesteGame {

	RenderData g_RenderData = {};

	void DrawSprite(SpriteID spiteID, Vec2 pos, Vec2 size)
	{
		Sprite sprite = GetSptrite(spiteID);

		Transform transform = {};
		transform.AtlasOffset = sprite.AtlasOffset;
		transform.SpriteSize = sprite.SpriteSize;
		transform.Pos = pos;
		transform.Size = size;

		g_RenderData.trasforms[g_RenderData.transformCount++] = transform;
	}
}