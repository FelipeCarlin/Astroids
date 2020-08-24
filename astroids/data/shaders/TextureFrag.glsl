#version 330 core

out vec4 FragColor;

in vec2 v_UV;

uniform sampler2D u_Texture;

void main()
{
    vec4 texColor = texture(u_Texture, v_UV);
    if(texColor.a < 0.1)
        discard;
        
    FragColor = texColor;
}