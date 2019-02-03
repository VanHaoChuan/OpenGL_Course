#version 330 core
struct Material
{
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};
out vec4 fragColor;
//in vec2 coord;
//uniform sampler2D texture_;
//uniform sampler2D textureFace;
in vec3 fragPos;
in vec3 aNormal;
uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 cameraPos;
uniform Material material;

void main() {
  //vec3 diffuseDir = normalize();
  vec3 ambient = ambientColor * material.ambient;
  vec3 lightDir = normalize(lightPos - fragPos);
  vec3 reflectVec = reflect(-lightDir, aNormal);
  vec3 diffuse = max(dot(lightDir, aNormal) * lightColor,0) * material.diffuse;
  vec3 cameraVec = normalize(cameraPos - fragPos);
  vec3 specular = pow(max(dot(cameraVec, reflectVec),0), material.shininess) * lightColor * material.specular;
  fragColor = vec4((diffuse + ambient + specular) * objColor,1.0f);
  //fragColor = vec4(objColor * ,1.0f);// * mix(texture(texture_,coord),texture(textureFace,coord),0.2f);
}
