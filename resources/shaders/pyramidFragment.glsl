#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 texCoord;

uniform sampler2D tex0;
// uniform sampler2D tex1;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main() {
  FragColor =  texture(tex0, texCoord) *
               vec4(lightColor * objectColor, 1.0f);
}
