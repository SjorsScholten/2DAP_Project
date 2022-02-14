#pragma once

#include <map>
#include <string>

class Shader;

class Texture2D;

class ResourceManager {
private:
    ResourceManager() = default;

    static std::map<std::string, Shader> _shaders;
    static std::map<std::string, Texture2D> _textures;

    static Shader
    LoadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile = nullptr);

    static Texture2D LoadTextureFromFile(const char *file, bool alpha);

public:
    static Shader
    LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, const std::string &name);

    static Shader GetShader(std::string name);

    static Texture2D LoadTexture(const char *file, bool alpha, const std::string &name);

    static Texture2D GetTexture(const std::string &name);

    static void Clear();
};