#include <ResourceManager.hpp>
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

std::map<std::string, Shader> ResourceManager::_shaders{};
std::map<std::string, Texture2D> ResourceManager::_textures{};

Shader ResourceManager::LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile,
                                   const std::string &name) {
    _shaders[name] = LoadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return _shaders[name];
}

Shader ResourceManager::GetShader(std::string name) {
    return _shaders[name];
}

Texture2D ResourceManager::LoadTexture(const char *file, bool alpha, const std::string &name) {
    _textures[name] = LoadTextureFromFile(file, alpha);
    return _textures[name];
}

Texture2D ResourceManager::GetTexture(const std::string &name) {
    return _textures[name];
}

void ResourceManager::Clear() {
    for (auto[key, value]: _shaders) glDeleteProgram(value.GetID());
    for (auto[key, value]: _textures) glDeleteTextures(1, &value.GetID());
}

std::string ReadFile(const std::string &file) {
    std::ifstream inputStream{file};
    std::stringstream sourceStream;
    sourceStream << inputStream.rdbuf();
    return sourceStream.str();
}

Shader ResourceManager::LoadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile) {
    std::string vertexSource, fragmentSource, geometrySource;
    try {
        vertexSource = ReadFile(vShaderFile);
        fragmentSource = ReadFile(fShaderFile);
        if (gShaderFile) geometrySource = ReadFile(gShaderFile);
    } catch (const std::exception &ex) {
        std::cerr << "ERROR failed to read shader files" << std::endl;
    }
    const char *vShaderCode = vertexSource.c_str();
    const char *fShaderCode = fragmentSource.c_str();
    const char *gShaderCode = geometrySource.c_str();

    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, gShaderCode ? gShaderCode : nullptr);
    return shader;
}

Texture2D ResourceManager::LoadTextureFromFile(const char *file, bool alpha) {
    Texture2D texture;

    if (alpha) {
        texture.SetInternalFormat(GL_RGBA);
        texture.SetImageFormat(GL_RGBA);
    }

    int width, height, nrChannels;
    unsigned char *data = stbi_load(file, &width, &height, &nrChannels, 0);
    texture.Generate(width, height, data);
    stbi_image_free(data);
    return texture;
}