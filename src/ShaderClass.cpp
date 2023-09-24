#include <ShaderClass.hpp>

auto get_file_contents(const char *fileName) -> std::string {

  std::ifstream file(fileName, std::ios::binary);
  if (file) {
    return std::string{std::istreambuf_iterator<char>(file),
                       std::istreambuf_iterator<char>()};
  }
  throw std::runtime_error(
      std::format("There is no file with path \"{}\".\n", fileName));
}

Shader::Shader(const char *vertexFile, const char *fragmentFile) {

  std::string vertexCode;
  std::string fragmentCode;
  try {
    vertexCode = get_file_contents(vertexFile);
    fragmentCode = get_file_contents(fragmentFile);
  } catch (std::runtime_error &e) {
    std::cerr << "Caught an exception: " << e.what();
    std::exit(1);
  }

  const char *vertexSource = vertexCode.c_str();
  const char *fragmentSource = fragmentCode.c_str();

  int success;
  std::string infoLog;

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, NULL);
  glCompileShader(vertexShader);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog.data());
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog.data());
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  _ID = glCreateProgram();
  glAttachShader(_ID, vertexShader);
  glAttachShader(_ID, fragmentShader);
  glLinkProgram(_ID);
  glGetProgramiv(_ID, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(_ID, 512, NULL, infoLog.data());
    std::cout << "ERROR::SHADER:PROGRAM::LINKING_FAILED\n" << std::endl;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

auto Shader::activate() const noexcept -> void { glUseProgram(_ID); }

auto Shader::deActivate() const noexcept -> void { glUseProgram(0); }

auto Shader::deleteProgram() const noexcept -> void { glDeleteProgram(_ID); }

auto Shader::setUniformValue(const char *uniformName,
                             float value) const noexcept -> void {
  glUniform1f(glGetUniformLocation(_ID, uniformName), value);
}

auto Shader::getID() const noexcept -> GLuint { return _ID; }
