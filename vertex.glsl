#version 330 core
layout(location = 1)in vec3 vertics_;
layout(location = 0)in vec2 UV;
out vec3 color;
out vec2 coord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
//uniform mat4 transform;
void main()
{
    gl_Position =  /*transform* */ projection * view * model * vec4(vertics_,1.0f);
    coord = UV;
}
