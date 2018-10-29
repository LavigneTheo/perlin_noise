#pragma once
#include <algorithm>
#include <iostream>
#include <time.h>
#include "GLFW/glfw3.h"

class Perlin1D {
private:
	float* m_fNoiseSeed1D = nullptr;
	float* m_fPerlinNoise1D = nullptr;
	unsigned int m_size;

	void perlin_noise1D(int nCount, float* fSeed, int nOctaves, float* fOutPut);
public:
	void new_noise(const unsigned int size, int octave);
	void destroy();
	float* get_data() const;
	void draw() const;
};
