#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 texCoord;

uniform sampler2D tex0;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main() {
  float ambientStrength = 0.1f;
  vec3 ambient = ambientStrength * lightColor;

  vec3 result = ambient * objectColor;
  FragColor =  texture(tex0, texCoord) *
               vec4(result, 1.0f);
}
