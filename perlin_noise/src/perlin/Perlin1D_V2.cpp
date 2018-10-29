#include "Perlin1D_V2.h"


Perlin1D_V2::Perlin1D_V2() {
	
}

void Perlin1D_V2::make_rand() {
	for (unsigned int i = 0; i < m_max_vertices; i++) {
		*(m_random + i) = (float)rand() / (float)RAND_MAX;
	}
		
}

float Perlin1D_V2::eval(const float& x){

	int xMin = (int)x;
	float t = x - xMin;

	return lerp(m_random[xMin], m_random[xMin + 1], t);
}
float Perlin1D_V2::eval_periodic(const float& x) {
	int xi = (int)x;
	int xMin = xi % (int)m_max_vertices;
	float t = x - xi;
	int xMax = (xMin == m_max_vertices - 1) ? 0 : xMin + 1;

	return lerp(m_random[xMin], m_random[xMax], t);
}

float Perlin1D_V2::eval_periodic_cosine(const float& x) {
	int xi = (int)x;
	int xMin = xi % (int)m_max_vertices;
	float t = x - xi;
	int xMax = (xMin == m_max_vertices - 1) ? 0 : xMin + 1;

	float remap_t = (1 - cosf(M_PI * t)) * 0.5f;

	return lerp(m_random[xMin], m_random[xMax], remap_t);
}

float Perlin1D_V2::eval_periodic_smoothstep(const float& x) {
	int xi = (int)x;
	int xMin = xi % (int)m_max_vertices;
	float t = x - xi;
	int xMax = (xMin == m_max_vertices - 1) ? 0 : xMin + 1;

	float remap_t = t * t * (3 - 2 * t);

	return lerp(m_random[xMin], m_random[xMax], remap_t);
}

float Perlin1D_V2::eval_signed_periodic_smoothstep(const float& x) {
	int kMaxVerticesMask = m_max_vertices - 1;
	/*
	 * If x = -9.5 for instance, x must equal -10 but (int) -9.5 = -9,
	 * that is why the boolean expression is here. If x < 0 it will remove 1 before rounding
	 */
	int xi = (int)x - (x < 0 && x != (int)x);
	float t = x - xi;
	// Modulo using &
	int xMin = xi & kMaxVerticesMask;
	int xMax = (xMin + 1) & kMaxVerticesMask;

	float remap_t = t * t * (3 - 2 * t);

	return lerp(m_random[xMin], m_random[xMax], remap_t);
}

float Perlin1D_V2::lerp(const float& xLow, const float& xHigh, const float& t) {
	return xLow * (1 - t) + xHigh * t;
}

void Perlin1D_V2::create_noise(const int& num_steps) {
	if (m_perlin != nullptr)
		free(m_perlin);

	m_perlin = (float*)malloc(sizeof(float) * num_steps);
	m_size = num_steps;

	make_rand();

	for (int i = 0; i < num_steps; i++) {
		float x = i / (float)(num_steps - 1) * m_max_vertices;
		m_perlin[i] = eval_signed_periodic_smoothstep(x);
	}

}
void Perlin1D_V2::draw() {
	if (m_perlin == nullptr)
		return;

	for (int i = 0; i < m_size; i++)
		glVertex2f((i / (float)m_size * 2 - 1), m_perlin[i] * 2 - 1);
}