#ifndef REFERENCE_LINES_H
#define REFERENCE_LINES_H

#include "../includes.h"
#include "drawable.h"

class ReferenceLines : public Drawable
{
public:
    ReferenceLines(std::size_t bufferSize, Shader *shader) : Drawable(bufferSize, shader) {}

    ~ReferenceLines() {}

    void loadShader() override
    {
        shader->vertexShaderPath = "./opengl/vertexBezier.vert";
        shader->fragmentShaderPath = "./opengl/fragmentReferenceLines.frag";
        shader->compileShaders();
    };

protected:
    void normalizeVertices(std::vector<float> buffer) override;
    void setVertices() override;
    void performDraw() override;
    
};

#endif