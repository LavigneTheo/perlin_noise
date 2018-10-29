#include "Perlin2D.h"


void Perlin2D::new_noise(const unsigned int& width, const unsigned int& height, int octave) {
	m_width = width;
	m_height = height;

	m_fNoiseSeed2D   = (float*)malloc(sizeof(float) * width * height);
	m_fPerlinNoise2D = (float*)malloc(sizeof(float) * width * height);

	srand(time(NULL));

	for (int i = 0; i < width * height; i++) 
		m_fNoiseSeed2D[i] = (float)rand() / (float)RAND_MAX;

	perlin_noise2D(m_fNoiseSeed2D, octave, m_fPerlinNoise2D);
	
}

void Perlin2D::perlin_noise2D(float* fSeed, int nOctaves, float* fOutPut) {
	for (int y = 0; y < m_width; y++) {
		for (int x = 0; x < m_height; x++) {
			float fNoise = 0.0f;
			float fScale = 1.0f;
			float fScaleAcc = 0.0f;

			for (int o = 0; o < nOctaves; o++)
			{
				int nPitch = m_width >> o;
				int nSampleX1 = (x / nPitch) * nPitch;
				int nSampleY1 = (y / nPitch) * nPitch;

				int nSampleX2 = (nSampleX1 + nPitch) % m_width;
				int nSampleY2 = (nSampleY1 + nPitch) % m_width;

				float fBlendX = (float)(x - nSampleX1) / (float)nPitch;
				float fBlendY = (float)(y - nSampleY1) / (float)nPitch;

				float fSampleT = (1.0f - fBlendX) * fSeed[nSampleY1 * m_width + nSampleX1] + fBlendX * fSeed[nSampleY1 * m_width + nSampleX2];
				float fSampleB = (1.0f - fBlendX) * fSeed[nSampleY2 * m_width + nSampleX1] + fBlendX * fSeed[nSampleY2 * m_width + nSampleX2];

				fScaleAcc += fScale;
				fNoise += (fBlendY * (fSampleB - fSampleT) + fSampleT) * fScale;
				fScale = fScale / m_bias;
			}
			//scale to seed range
			fOutPut[y * m_width + x] = fNoise / fScaleAcc;
		}
	}

	char path[] = "image.bmp";
	m_image_writer.write_bmp(m_width, m_height, path, m_fPerlinNoise2D);
}

void Perlin2D::destroy() {
	if (m_fNoiseSeed2D != nullptr)
		delete m_fNoiseSeed2D;
	if (m_fPerlinNoise2D != nullptr)
		delete m_fPerlinNoise2D;
}
float* Perlin2D::get_data() const {
	return m_fPerlinNoise2D;
}

unsigned int Perlin2D::get_width() const {
	return m_width;
}
unsigned int Perlin2D::get_height() const {
	return m_height;
}

void Perlin2D::change_bias(const float& value) {
	if (m_bias + value < 0.2f)
		m_bias = 0.2f;
	else
		m_bias += value;
}

float Perlin2D::get_bias() {
	return m_bias;
}

void Perlin2D::draw() const {
	if (m_fPerlinNoise2D == nullptr)
		return;

	float height_cell = 2 / (float)m_height;
	float width_cell = 2 / (float)m_width;

	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			glColor3f(m_fPerlinNoise2D[y * m_height + x], m_fPerlinNoise2D[y * m_height + x], m_fPerlinNoise2D[y * m_height + x]);
			glVertex2f(width_cell * x - 1, height_cell * y -1);
			glVertex2f(width_cell * (x + 1) - 1, height_cell * y - 1);
			glVertex2f(width_cell * (x + 1) - 1, height_cell * (y + 1) - 1);
			glVertex2f(width_cell * x - 1, height_cell * (y + 1) - 1);
		}
	}
		
}