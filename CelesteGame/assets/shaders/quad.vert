#version 430 core

struct Transform
{
	ivec2 AtlasOffset;
	ivec2 SpriteSize;
    vec2 Pos;
    vec2 Size;
};

layout(std430, binding = 0) buffer TransformSBO
{
  Transform transforms[];
};

uniform vec2 screenSize;

layout (location = 0) out vec2 textureCoordsOut;

void main()
{

    Transform transform = transforms[gl_InstanceID];

	vec2 vertices[6] =
	{
	   transform.Pos,                                        // Top Left
       vec2(transform.Pos + vec2(0.0, transform.Size.y)),    // Bottom Left
       vec2(transform.Pos + vec2(transform.Size.x, 0.0)),    // Top Right
       vec2(transform.Pos + vec2(transform.Size.x, 0.0)),    // Top Right
       vec2(transform.Pos + vec2(0.0, transform.Size.y)),    // Bottom Left
       transform.Pos + transform.Size                        // Bottom Right
	};

    float left = transform.AtlasOffset.x;
    float top = transform.AtlasOffset.y;
    float right = transform.AtlasOffset.x + transform.SpriteSize.x;
    float bottom = transform.AtlasOffset.y + transform.SpriteSize.y;

   vec2 textureCoords[6] = 
   {
     vec2(left, top),
     vec2(left, bottom),
     vec2(right, top),
     vec2(right, top),
     vec2(left, bottom),
     vec2(right, bottom),
   };


    // Normalize Position
  {
    vec2 vertexPos = vertices[gl_VertexID];
    vertexPos.y = -vertexPos.y + screenSize.y;
    vertexPos = 2.0 * (vertexPos / screenSize) - 1.0;
    gl_Position = vec4(vertexPos, 0.0, 1.0);
  }

   textureCoordsOut = textureCoords[gl_VertexID];
}