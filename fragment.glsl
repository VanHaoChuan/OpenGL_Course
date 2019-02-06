#version 330 core
struct Material
{
  vec3 ambient;
  sampler2D diffuse;
  sampler2D specular;
  float shininess;
};
struct LightPoint
{
  float constant;
  float linear;
  float quadratic;
};
struct LightSpot
{
  float cosPhy;
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
uniform vec3 lightDirUniform;
uniform Material material;
uniform LightPoint lightPoint;
uniform LightSpot lightSpot;
void main() {
  //vec3 diffuseDir = normalize();

  float distance_l = length(max((lightPos - fragPos),0));
  float attenuation = 1.0 / (1.0f + 0.09f * distance_l +
                  0.032f * (distance_l * distance_l));

  vec3 ambient = texture(material.diffuse,texCoord).rgb * ambientColor * material.ambient;
  vec3 lightDir = normalize(lightPos - fragPos);
  vec3 reflectVec = reflect(-lightDir, aNormal);
  vec3 diffuse = texture(material.diffuse,texCoord).rgb * max(dot(lightDir, aNormal),0) * lightColor;
  vec3 cameraVec = normalize(cameraPos - fragPos);
  vec3 specular = pow(max(dot(cameraVec, reflectVec),0), material.shininess) * lightColor * (texture(material.specular,texCoord).rgb + texture(material.diffuse,texCoord).rgb * 0.5f);

float cosTheta = dot(normalize(fragPos - lightPos), -1 * lightDirUniform);
if(cosTheta > lightSpot.cosPhy)
{

  fragColor = vec4((ambient + diffuse + specular),1.0f);
  //inside
}else
{
  //outside
  fragColor = vec4(vec3(1,1,1),1.0f);
}
  //fragColor = vec4(objColor * ,1.0f);// * mix(texture(texture_,coord),texture(textureFace,coord),0.2f);
}
