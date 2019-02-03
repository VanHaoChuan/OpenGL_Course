#version 330 core
layout(location = 1)in vec3 vertics_;
//layout(location = 0)in vec2 UV;
layout(location = 2)in vec3 normal;
layout(location = 3)in vec2 aTexCoord;
out vec3 color;
//out vec2 coord;
out vec3 aNormal;
out vec3 fragPos;
out vec2 texCoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
//uniform mat4 transform;
void main()
{
    fragPos = (model * vec4(vertics_,1.0f)).xyz;
    aNormal = mat3(transpose(inverse(model))) * normal;
    texCoord = aTexCoord;
    gl_Position =  /*transform* */ projection * view * model * vec4(vertics_,1.0f);
    //coord = UV;
}
