#version 330 core

in vec3 Color;
/* in vec2 TexCoord; */

out vec4 FragColor;

/* uniform sampler2D texture1; */
/* uniform sampler2D texture2; */

void main() {
    /* FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), */
    /* 0.3); */
    FragColor = vec4(Color, 1.0);
}
