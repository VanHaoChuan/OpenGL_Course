#version 330 core
layout(location = 1)in vec3 vertics_;
//layout(location = 0)in vec2 UV;
layout(location = 2)in vec3 normal;
out vec3 color;
//out vec2 coord;
out vec3 aNormal;
out vec3 fragPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
//uniform mat4 transform;
void main()
{
    fragPos = vec3(model * vec4(vertics_,1.0f));
    aNormal = mat3(model) * normal;

    gl_Position =  /*transform* */ projection * view * model * vec4(vertics_,1.0f);
    //coord = UV;
}
