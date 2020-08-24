#version 330 core

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec2 a_UV;

out vec2 v_UV;

uniform float u_Aspect;
uniform vec2 u_Pos;
uniform float u_Rot;
uniform float u_Scale;

void main()
{
    v_UV = a_UV;

    float radiansRot = radians(u_Rot);
    float cs = cos(radiansRot);
    float sn = sin(radiansRot);

    // NOTE(felipe): Scale.
    float xScaled = a_Pos.x * u_Scale;
    float yScaled = a_Pos.y * u_Scale;

    // NOTE(felipe): Rotation.
    float xRot = (xScaled * cs - yScaled * sn);
    float yRot = (xScaled * sn + yScaled * cs);

    // NOTE(felipe): Translation.
    float x = xRot + u_Pos.x;
    float y = yRot + u_Pos.y;

    y /= u_Aspect;

    gl_Position = vec4(x, y, a_Pos.z, 1.0);
}