#pragma once
#include "Perlin1D.h"

void Perlin1D::new_noise(const unsigned int size, int octave) {

	destroy();

	m_size = size;

	m_fNoiseSeed1D = new float[size];
	m_fPerlinNoise1D = new float[size];

	srand(time(NULL));

	for (int i = 0; i < size; i++) {
		m_fNoiseSeed1D[i] = 0.95f;//(float)rand() / (float)RAND_MAX;
	}

	perlin_noise1D(size, m_fNoiseSeed1D, octave, m_fPerlinNoise1D);
}

void Perlin1D::perlin_noise1D(int nCount, float* fSeed, int nOctaves, float* fOutPut) {
	for (int x = 0; x < nCount; x++) {
		float fNoise = 0.0f;
		float fScale = 1.0f;
		float fScaleAcc = 0.0f;

		for (int o = 0; o < nOctaves; o++)
		{
			int nPitch = nCount >> o;
			//Define the two points for interpolation
			int nSample1 = (x / nPitch) * nPitch;
			int nSample2 = (nSample1 + nPitch) % nCount;

			float fBlend = (float)(x - nSample1) / nPitch;
			//Linear interpolation
			float fSample = (1.0f - fBlend) * fSeed[nSample1] + fBlend * fSeed[nSample2];
			fNoise += fSample * fScale;
			fScaleAcc += fScale;
			fScale = fScale / 2;
		}

		//scale to seed range
		fOutPut[x] = fNoise / fScaleAcc;
	}
}

void Perlin1D::destroy() {
	if (m_fNoiseSeed1D != nullptr)
		delete m_fNoiseSeed1D;
	if (m_fPerlinNoise1D != nullptr)
		delete m_fPerlinNoise1D;
}

float* Perlin1D::get_data() const {
	return m_fPerlinNoise1D;
}

void Perlin1D::draw() const {
	if (m_fPerlinNoise1D == nullptr)
		return;
	for(int i = 0; i < m_size; i++)
		glVertex2f((i / (float)m_size * 2 - 1), m_fPerlinNoise1D[i]);
}