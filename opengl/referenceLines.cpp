#include "referenceLines.h"

void ReferenceLines::normalizeVertices(std::vector<float> buffer){
    float maxMagnitude = 0.0;

    // fazer copia do buffer
    std::vector<float> copyBuffer = buffer;

    /*
        Encontra a amplitude máxima conforme a fórmula |a + bi| = sqrt(a^2 + b^2)
        onde a é a parte real e b é a parte imaginária
    */
    for (const auto &c : copyBuffer)
    {
        float magnitude = std::abs(c);
        if (magnitude > maxMagnitude)
        {
            maxMagnitude = magnitude;
        }
    }

    std::size_t n = copyBuffer.size();
    for (std::size_t i = 0; i < n; i++)
    {
        float frequency = (static_cast<float>(i)*SAMPLE_RATE / n);

        float logFrequency = std::log10(frequency + 1);  // escola logarítmica
        float normalizedFrequency = (logFrequency - std::log10(20)) / (std::log10(20000) - std::log10(20)); // Normaliza entre 20 Hz e 20 kHz

        vertices[i * 2] = normalizedFrequency * 2 - 1;                          // X coordinate entre [-1, 1]
        vertices[i * 2 + 1] = (std::abs(copyBuffer[i]) / maxMagnitude) - 0.5f; // Y coordinate entre [0, 1]
    } 
}

// Defina a taxa de amostragem e o tamanho da FFT
const float sampleRate = 48000.0f;  // 48 kHz
const float f_min = 20.0f;          // 20 Hz (frequência mínima)
const float f_max = 20000.0f;       // 20 kHz (frequência máxima)

// Calcula a frequência correspondente ao índice x em escala linear
float getFrequencyAtIndex(int x, int bufferSize) {
    // Frequência linear
    float frequencyLinear = (static_cast<float>(x) * sampleRate) / static_cast<float>(bufferSize);

    // Frequência logarítmica
    float frequencyLog = f_min * pow(f_max / f_min, static_cast<float>(x) / static_cast<float>(bufferSize));

    // Exemplo de uso: retorne a frequência logarítmica
    return frequencyLog;
}

void ReferenceLines::setVertices(){
    curvePoints.clear();

    for(int i = 0; i < bufferSize; i += 20){
        glm::vec2 p0(vertices[i*2], 0.5f);
        glm::vec2 p1(vertices[i*2], -0.5f);

        float f = getFrequencyAtIndex(i*2, bufferSize);
        if (f < 800.0f){
            printf("f: %f\n", f);
        }
        curvePoints.push_back(p0);
        curvePoints.push_back(p1);
        }
}

void ReferenceLines::performDraw(){
    glDrawArrays(GL_LINES, 0, curvePoints.size());
}