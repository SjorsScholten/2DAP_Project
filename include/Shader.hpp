#pragma once

#include <string>
#include <glm/glm.hpp>

class Shader {
private:
    unsigned int _id;

public:
    Shader() = default;

    const unsigned int &GetID() const{
        return _id;
    }

    void Compile(const char *vSource, const char *fSource, const char *gSource = nullptr);

    Shader &Use();

    void SetMatrix4(const char *name, const glm::mat4 &mat, bool useShader = false);

    void SetVector3f(const char *name, const glm::vec3 &vec, bool useShader = false);
};
