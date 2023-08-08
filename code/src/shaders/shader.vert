#version 330 core

layout (location = 0) in vec3 aPos;
/* layout (location = 1) in vec3 aColor; */
/* layout (location = 2) in vec2 aTexCoord; */

out vec3 Color;
/* out vec2 TexCoord; */

uniform vec color;
uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vec4(aPos, 1.0f);
    Color = aColor;
    /* TexCoord = aTexCoord; */
}
