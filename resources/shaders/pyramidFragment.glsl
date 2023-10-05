#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D tex0;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main() {
  float ambient = 0.2f;
  vec3 normal = normalize(Normal);
  vec3 lightDirection = normalize(lightPos - FragPos);

  float diffuse = max(dot(normal, lightDirection), 0.0f);

  float specularStrength = 0.5f;
  vec3 viewDirection = normalize(viewPos - FragPos);
  vec3 reflectDir = reflect(-lightDirection, normal);
  float spec = pow(max(dot(viewDirection, reflectDir), 0.0f), 32);
  float specular = specularStrength * spec;

  FragColor = texture(tex0, TexCoord) * vec4(lightColor, 1.0f) * (ambient + diffuse + specular);
}
