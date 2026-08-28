#include <iostream>
#include <vector>
#include <memory>

int main() {
    constexpr size_t N = 1000;

    // Data setup
    // A vector of floats - continous data:
    std::vector<float> vectorizableData(N, 2.0f);

    // A vector of pointers to floats - not continous:
    std::vector<std::unique_ptr<float>> nonVectorizableData;
    nonVectorizableData.reserve(N);
    for (size_t i = 0; i < N; ++i) {
        nonVectorizableData.push_back(std::make_unique<float>(2.0f));
    }

    // ==========================================
    // 1. Vectorized Loop (SIMD Enabled)
    // Contiguous memory allows loading 4-8 floats per cycle
    // ==========================================
    for (size_t i = 0; i < N; ++i) {
        vectorizableData[i] *= 3.0f;
    }

    // ==========================================
    // 2. Non-Vectorized Loop (No SIMD / Scalar Only)
    // Pointer indirection forces loading 1 float at a time from random memory
    // ==========================================
    for (size_t i = 0; i < N; ++i) {
        *nonVectorizableData[i] *= 3.0f;
    }

    // Prevent dead-code elimination
    std::cout << "Vectorized sample: " << vectorizableData[0] << "\n";
    std::cout << "Scalar sample:     " << *nonVectorizableData[0] << "\n";

    return 0;
}