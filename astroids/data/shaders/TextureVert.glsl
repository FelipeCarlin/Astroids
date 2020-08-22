#version 330 core

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec2 a_UV;

out vec2 v_UV;

uniform vec2 u_Pos;

void main()
{
    v_UV = a_UV;
    
    gl_Position = vec4(a_Pos.x + u_Pos.x, a_Pos.y + u_Pos.y, a_Pos.z, 1.0);
}