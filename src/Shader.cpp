#include <Shader.hpp>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

unsigned int CompileShader(const int type, const char *source) {
    auto shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "ERROR shader compilation failed:\n" << infoLog << std::endl;
    }
    return shader;
}

void Shader::Compile(const char *vSource, const char *fSource, const char *gSource = nullptr) {
    unsigned int vShader, fShader, gShader;

    { //compile shaders
        vShader = CompileShader(GL_VERTEX_SHADER, vSource);
        fShader = CompileShader(GL_FRAGMENT_SHADER, vSource);
        if (gSource) gShader = CompileShader(GL_GEOMETRY_SHADER, gSource);
    }

    { //Create and link shader program
        _id = glCreateProgram();

        glAttachShader(_id, vShader);
        glAttachShader(_id, fShader);
        if (gSource) glAttachShader(_id, gShader);

        glLinkProgram(_id);

        int success;
        char infoLog[512];
        glGetProgramiv(_id, GL_LINK_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(_id, 512, nullptr, infoLog);
            std::cerr << "ERROR linking shader program failed:\n" << infoLog << std::endl;
        }
    }

    {//Clean shader
        glDeleteShader(vShader);
        glDeleteShader(fShader);
        if (gSource) glDeleteShader(gShader);
    }
}

Shader &Shader::Use() {
    glUseProgram(_id);
    return *this;
}

void Shader::SetMatrix4(const char *name, const glm::mat4 &mat, bool useShader) {
    if (useShader) Use();
    glUniformMatrix4fv(glGetUniformLocation(_id, name), 1, false, glm::value_ptr(mat));
}

void Shader::SetVector3f(const char *name, const glm::vec3 &vec, bool useShader) {
    if (useShader) Use();
    glUniform3f(glGetUniformLocation(_id, name), vec.x, vec.y, vec.z);

}
