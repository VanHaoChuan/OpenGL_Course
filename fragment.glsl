#version 330 core
struct Material
{
  vec3 ambient;
  sampler2D diffuse;
  sampler2D specular;
  float shininess;
};
out vec4 fragColor;
//in vec2 coord;
//uniform sampler2D texture_;
//uniform sampler2D textureFace;
in vec3 fragPos;
in vec3 aNormal;
in vec2 texCoord;
uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 cameraPos;
uniform Material material;

void main() {
  //vec3 diffuseDir = normalize();
  vec3 ambient = texture(material.diffuse,texCoord).rgb * ambientColor * material.ambient;
  vec3 lightDir = normalize(lightPos - fragPos);
  vec3 reflectVec = reflect(-lightDir, aNormal);
  vec3 diffuse = texture(material.diffuse,texCoord).rgb * max(dot(lightDir, aNormal),0) * lightColor;
  vec3 cameraVec = normalize(cameraPos - fragPos);
  vec3 specular = pow(max(dot(cameraVec, reflectVec),0), material.shininess) * lightColor * (texture(material.specular,texCoord).rgb + texture(material.diffuse,texCoord).rgb * 0.5f);
  fragColor = vec4((diffuse + ambient + specular) * objColor,1.0f);
  //fragColor = vec4(objColor * ,1.0f);// * mix(texture(texture_,coord),texture(textureFace,coord),0.2f);
}
