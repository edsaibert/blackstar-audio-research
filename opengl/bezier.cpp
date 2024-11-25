#include "bezier.h"

void Bezier::normalizeVertices(std::vector<float> buffer)
{
    float maxMagnitude = 0.0;

    /*
        Encontra a amplitude máxima conforme a fórmula |a + bi| = sqrt(a^2 + b^2)
        onde a é a parte real e b é a parte imaginária
    */
    for (const auto &c : buffer)
    {
        float magnitude = std::abs(c);
        if (magnitude > maxMagnitude)
        {
            maxMagnitude = magnitude;
        }
    }

    std::size_t n = buffer.size();
    for (std::size_t i = 0; i < n; i++)
    {
        float frequency = (static_cast<float>(i)*SAMPLE_RATE / n);

        float logFrequency = std::log10(frequency + 1);  // escola logarítmica
        float normalizedFrequency = (logFrequency - std::log10(20)) / (std::log10(20000) - std::log10(20)); // Normaliza entre 20 Hz e 20 kHz

        vertices[i * 2] = normalizedFrequency * 2 - 1;                          // X coordinate entre [-1, 1]
        vertices[i * 2 + 1] = (std::abs(buffer[i]) / maxMagnitude) - 0.5f; // Y coordinate entre [0, 1]
    }
}

void Bezier::setVertices()
{
    int numPoints = 100;
    curvePoints.clear();

    // Make sure there are enough points for a quadratic Bézier
    for (int i = 0; i < bufferSize - 4; i += 2)
    {
        glm::vec2 p0(vertices[i * 2], vertices[i * 2 + 1]);
        glm::vec2 p1(vertices[(i + 1) * 2], vertices[(i + 1) * 2 + 1]);
        glm::vec2 p2(vertices[(i + 2) * 2], vertices[(i + 2) * 2 + 1]);

        for (int j = 0; j < numPoints; j++)
        {
            float t = static_cast<float>(j) / (numPoints - 1);
            glm::vec2 point = (1 - t) * (1 - t) * p0 + 2 * (1 - t) * t * p1 + t * t * p2;

            curvePoints.push_back(point);
            // printf("x: %f, y: %f\n", curvePoints.back().x, curvePoints.back().y);
        }
    }
}

void Bezier::performDraw()
{
    // draw the curve
    // will be necessary to create a shader for this

    // glDrawArrays(GL_LINE_STRIP, 0, bufferSize / 2); // Desenha os v


    glDrawArrays(GL_LINE_STRIP, 0, curvePoints.size());
}