#version 330 core

out vec4 FragColor;

in vec2 v_UV;

uniform sampler2D Bitmap;

void main()
{
    //FragColor = vec4(v_UV, 0.0f, 1.0f);
    FragColor = texture(Bitmap, v_UV);
}