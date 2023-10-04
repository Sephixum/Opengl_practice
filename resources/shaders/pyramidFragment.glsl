#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 texCoord;

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main() {
  vec4 textures = mix(texture(tex0, texCoord),
                  texture(tex1, texCoord),
                  1.0f);
  // FragColor =  textures * vec4(lightColor * objectColor, 1.0f);
  FragColor =  textures;
}
