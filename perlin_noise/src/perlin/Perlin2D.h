#pragma once

#include <iostream>
#include <time.h>
#include "GLFW/glfw3.h"
#include "../ImageWriter.h"

class Perlin2D {
private:
	float* m_fNoiseSeed2D = nullptr;
	float* m_fPerlinNoise2D = nullptr;
	float m_bias = 2;
	unsigned int m_width, m_height;
	ImageWriter m_image_writer;

	void perlin_noise2D(float* fSeed, int nOctaves, float* fOutPut);
public:
	void new_noise(const unsigned int& width, const unsigned int& height, int octave);
	void destroy();
	float* get_data() const;
	void draw() const;

	unsigned int get_width() const;
	unsigned int get_height() const;

	float get_bias();
	void change_bias(const float& value);
};
