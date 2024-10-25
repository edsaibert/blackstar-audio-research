#include "../includes.h"

/*
    Implementa uma classe TBO OpenGL (Texture Buffer Object)
*/

class TextureBuffer
{
public:
    TextureBuffer(std::size_t bufferSize, GLfloat *buffer, GLuint shaderProgram) : bufferSize(bufferSize), buffer(buffer), shaderProgram(shaderProgram)
    {
        genBuffers();
        genTextures();
        getTBOUniform();
    }

    ~TextureBuffer()
    {
        glDeleteBuffers(1, &TBO);
        glDeleteTextures(1, &TBO_tex);
    }

protected:
    void genTextures()
    {
        glGenTextures(1, &TBO_tex);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_BUFFER, TBO_tex);
        glTexBuffer(GL_TEXTURE_BUFFER, GL_R32F, TBO);
    }

    void genBuffers()
    {
        glGenBuffers(1, &TBO);
        glBindBuffer(GL_TEXTURE_BUFFER, TBO);
        glBufferData(GL_TEXTURE_BUFFER, bufferSize * sizeof(GLfloat), &buffer[0], GL_STATIC_DRAW);
        glBindBuffer(GL_TEXTURE_BUFFER, 0);
    }

    void getTBOUniform()
    {
        GLuint myTBOUniform = glGetUniformLocation(shaderProgram, "controlPoints");
        // shaderProgram exists
        if (myTBOUniform != -1)
        {
            glUniform1i(myTBOUniform, 0);
        }
    }

    GLfloat *buffer;
    GLuint shaderProgram;
    std::size_t bufferSize;
    GLuint TBO, TBO_tex;
};