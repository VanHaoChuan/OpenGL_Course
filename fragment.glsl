#version 330 core
out vec4 fragColor;
in vec2 coord;
uniform sampler2D texture_;
uniform sampler2D textureFace;
void main() {
    fragColor = mix(texture(texture_,coord),texture(textureFace,coord),0.2f);
    
}
