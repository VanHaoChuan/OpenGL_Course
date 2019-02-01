#version 330 core
layout(location = 4)in vec3 vertics_;
layout(location = 2)in vec3 color_;
layout(location = 0)in vec2 UV_;
out vec3 color;
out vec2 coord;
void main()
{
    gl_Position = vec4(vertics_.x,vertics_.y,vertics_.z,1.0f);
    coord = UV_;
}