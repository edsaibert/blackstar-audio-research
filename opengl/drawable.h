#ifndef DRAWABLE_H
#define DRAWABLE_H

/*
    Arquivo com a definição da classe Drawable
*/

#include "../includes.h"
#include "./shader.h"
#include "./tbo.h"

class Drawable
{
public:
    // using complex = std::complex<float>; // definição de tipo para números complexos

    // Construtor
    Drawable(
        std::size_t bufferSize, Shader *shader)
        : bufferSize(bufferSize), shader(shader)
    {
        vertices = new GLfloat[bufferSize * 2];
    }

    ~Drawable()
    {
        delete[] vertices;
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
    }

    // Método virtual que desenha os vértices
    virtual void draw(std::vector<float> buffer)
    {
        // clearScreen();
        bindBuffers();
        normalizeVertices(buffer);
        setVertices();
        bindTextureBuffer();
        updateShaderProgram();
        performDraw();
        unbindBuffers();
    }

    virtual void loadShader() = 0;
    virtual void bindTextureBuffer()
    {
        tbo = new TextureBuffer(bufferSize * 2, vertices, shader->shaderProgram);
        glGenBuffers(1, &bufferID); // Generate bufferID
    }

protected:
    virtual void clearScreen()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    };

    virtual void bindBuffers()
    {
        /*  Função que inicializa os objectos VAO e VBO   */
        glGenVertexArrays(1, &VAO); // Gera um array
        glBindVertexArray(VAO);                                                          // Faz com que VAO seja o array vertex atual

        glGenBuffers(1, &VBO);      //  Gera um buffer
        glBindBuffer(GL_ARRAY_BUFFER, VBO);                                              // Faz com que VBO seja o buffer atual

        // glBufferData(GL_ARRAY_BUFFER, bufferSize * 2 * sizeof(GLfloat), curvePoints, GL_STATIC_DRAW);
        glBufferData(GL_ARRAY_BUFFER, curvePoints.size() * sizeof(glm::vec2), curvePoints.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void *)0); // Define as propriedades do buffer
        glEnableVertexAttribArray(0);                                                    // Habilita o buffer

        glGenBuffers(1, &bufferID); // Generate bufferID
        glBindBuffer(GL_ARRAY_BUFFER, bufferID);

        if (!glIsBuffer(bufferID))
        {
            std::cerr << "Error: OpenGL buffer not initialized." << std::endl;
            return;
        }
    };

    virtual void updateShaderProgram()
    {
        glUseProgram(shader->shaderProgram);
    };

    virtual void setVertices() = 0;
    virtual void normalizeVertices(std::vector<float> buffer) = 0;
    virtual void performDraw() = 0;

    virtual void unbindBuffers()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glUseProgram(0);
    };

    GLuint VAO, VBO, bufferID;
    GLfloat *vertices;
    std::vector<glm::vec2> curvePoints;
    const std::size_t samplesPerChannel = SAMPLE_RATE;
    std::size_t bufferSize, verticesSize;
    // std::vector<float> buffer;

    TextureBuffer *tbo;
    Shader *shader;
};

#endif