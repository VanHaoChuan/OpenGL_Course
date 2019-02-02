#version 330 core
out vec4 fragColor;
//in vec2 coord;
//uniform sampler2D texture_;
//uniform sampler2D textureFace;
in vec3 fragPos;
in vec3 aNormal;
uniform vec3 objColor;
uniform vec3 toyColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 cameraPos;
void main() {
  //vec3 diffuseDir = normalize();
  vec3 lightDir = normalize(lightPos - fragPos);
  vec3 reflectDir = reflect(-lightDir, aNormal);
  vec3 diffuse = max(dot(lightDir, aNormal) * lightColor,0);
  vec3 cameraDir = normalize(cameraPos - fragPos);
  float specularAmount = pow(max(dot(reflectDir,cameraDir),0),32) ;
  vec3 specular = specularAmount * lightColor;
  fragColor = vec4((diffuse + toyColor + specular) * toyColor,1.0f);
  //fragColor = vec4(objColor * toyColor,1.0f);// * mix(texture(texture_,coord),texture(textureFace,coord),0.2f);
}
