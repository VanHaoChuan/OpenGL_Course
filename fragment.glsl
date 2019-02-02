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
void main() {
  //vec3 diffuseDir = normalize();
  vec3 lightDir = normalize(lightPos - fragPos);
  vec3 diffuse = dot(lightDir, aNormal) * lightColor;
  fragColor = vec4(diffuse,1.0f);
  //fragColor = vec4(objColor * toyColor,1.0f);// * mix(texture(texture_,coord),texture(textureFace,coord),0.2f);
}
