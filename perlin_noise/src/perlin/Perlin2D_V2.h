#pragma once

#include <algorithm>
#include "GLFW/glfw3.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <fstream>
#include <random>
#include <functional>

class Perlin2D_V2 {
	static const unsigned int m_max_vertices = 512;
	int m_size;
	float m_random[m_max_vertices ];
	float m_random_hash[m_max_vertices];
	int m_permutation_table[2 * m_max_vertices];
	float* m_perlin = nullptr;
	
	float eval_signed_periodic_smoothstep(const float& x, const float& y);
	float eval_signed_periodic_smoothstep_hash(const float& x, const float& y);
	float lerp(const float& xLow, const float& xHigh, const float& t);


public:
	Perlin2D_V2() {}
	~Perlin2D_V2() { if (m_perlin != nullptr) free(m_perlin);}

	void create_noise(const int& num_steps);
	void create_noise_fractal_sum(const int& layers);
	void make_rand();
	void make_rand_hash();
	void draw();

};
