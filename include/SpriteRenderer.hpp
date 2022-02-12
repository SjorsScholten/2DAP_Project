#pragma once

#include <Shader.hpp>
#include <Texture.hpp>
#include <glm/glm.hpp>

class SpriteRenderer {
private:
    Shader _shader;
    unsigned int _quadVAO;

    void InitRenderData();

public:
    SpriteRenderer(Shader &shader);
    ~SpriteRenderer();

    void DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color);
};