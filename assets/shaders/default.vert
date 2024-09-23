#version 330 core

layout(location = 0) in vec2 aPos;  // Vertex position
layout(location = 1) in vec2 aTexCoord;  // Vertex texture coordinate

out vec2 TexCoord;  // Texture coordinate to pass to fragment shader

void main()
{
    gl_Position = vec4(aPos, 0.0, 1.0);  // Set the position in clip space
    TexCoord = aTexCoord;  // Pass the texture coordinate to the fragment shader
}