#version 330 core

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec2 a_UV;

out vec2 v_UV;

uniform float u_Aspect;
uniform vec2 u_Pos;
uniform float u_Rot;

void main()
{
    v_UV = a_UV;

    float radiansRot = radians(u_Rot);
    float cs = cos(radiansRot);
    float sn = sin(radiansRot);

    float x = (a_Pos.x * cs - a_Pos.y * sn) + u_Pos.x;
    float y = (a_Pos.x * sn + a_Pos.y * cs) + u_Pos.y;

    y *= u_Aspect;

    gl_Position = vec4(x, y, a_Pos.z, 1.0);
}