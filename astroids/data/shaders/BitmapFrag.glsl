#version 330 core

out vec4 FragColor;

in vec2 vUV;

uniform sampler2D Bitmap;

void main()
{
    FragColor = texture(Bitmap, vUV);
}