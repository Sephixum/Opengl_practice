#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D tex0;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main() {
  float ambient = 0.2f;
  vec3 normal = normalize(Normal);
  vec3 lightDirection = normalize(lightPos - FragPos);

  float diffuse = max(dot(normal, lightDirection), 0.0f);
  FragColor = texture(tex0, TexCoord) * vec4(lightColor, 1.0f) * (diffuse + ambient);
}
