#pragma once

class Texture2D {
private:
    unsigned int _id;
    unsigned int width, height;
    unsigned int internalFormat;
    unsigned int imageFormat;
    unsigned int wrapS;
    unsigned int wrapT;
    unsigned int filterMin;
    unsigned int filterMax;

public:
    Texture2D();

    const unsigned int &GetID() const{
        return _id;
    }

    void Generate(unsigned int width, unsigned int height, unsigned char *data);

    void Bind() const;
};