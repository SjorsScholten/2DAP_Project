#include <ResourceManager.hpp>
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Shader.hpp>
#include <Texture.hpp>

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
    for(auto [key,value] : _shaders) glDeleteProgram(value.GetID());
    for(auto [key,value] : _textures) glDeleteTextures(1, &value.GetID());
}

std::string ReadFile(const std::string &file){
    std::ifstream inputStream{file};
    std::stringstream sourceStream;
    sourceStream << inputStream.rdbuf();
    return sourceStream.str();
}

Shader ResourceManager::LoadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile) {
    std::string vertexSource, fragmentSource, geometrySource;
    try{
        vertexSource = ReadFile(vShaderFile);
        fragmentSource = ReadFile(fShaderFile);
        if(gShaderFile) geometrySource = ReadFile(gShaderFile);
    } catch (const std::exception &ex){
        std::cerr << "ERROR failed to read shader files" << std::endl;
    }
    const char *vShaderCode = vertexSource.c_str();
    const char *fShaderCode = fragmentSource.c_str();
    const char *gShaderCode = geometrySource.c_str();

    Shader shader;
    shader.Compile
}

Texture2D ResourceManager::LoadTextureFromFile(const char *file, bool alpha) {

}