#include "Perlin2D_V2.h"

float Perlin2D_V2::eval_signed_periodic_smoothstep(const float& x, const float& y) {
	int total_vertices = m_max_vertices * m_max_vertices ;
	int table_size_mask = m_max_vertices - 1;
	int xi = std::floor(x);
	int yi = std::floor(y);

	float tx = x - xi;
	float ty = y - yi;

	int xi_low = xi & table_size_mask;
	int xi_high = (xi_low + 1) & table_size_mask;
	int yi_low = yi & table_size_mask;
	int yi_high = (yi_low + 1) & table_size_mask;

	//find random value
	float c00 = m_random[yi_low * m_max_vertices + xi_low];
	float c10 = m_random[yi_low * m_max_vertices + xi_high];
	float c01 = m_random[yi_high * m_max_vertices + xi_low];
	float c11 = m_random[yi_high * m_max_vertices + xi_high];

	float remap_tx = tx * tx * (3 - 2 * tx);
	float remap_ty = ty * ty * (3 - 2 * ty);

	float nx0 = lerp(c00, c10, remap_tx);
	float nx1 = lerp(c01, c11, remap_tx);

	return lerp(nx0, nx1, remap_ty);
}

float Perlin2D_V2::eval_signed_periodic_smoothstep_hash(const float& x, const float& y) {
	int total_vertices = m_max_vertices * m_max_vertices;
	int table_size_mask = m_max_vertices - 1;
	int xi = std::floor(x);
	int yi = std::floor(y);

	float tx = x - xi;
	float ty = y - yi;

	int xi_low = xi & table_size_mask;
	int xi_high = (xi_low + 1) & table_size_mask;
	int yi_low = yi & table_size_mask;
	int yi_high = (yi_low + 1) & table_size_mask;

	//find random value
	float c00 = m_random[m_permutation_table[m_permutation_table[xi_low] + yi_low]];
	float c10 = m_random[m_permutation_table[m_permutation_table[xi_high] + yi_low]];
	float c01 = m_random[m_permutation_table[m_permutation_table[xi_low] + yi_high]];
	float c11 = m_random[m_permutation_table[m_permutation_table[xi_high] + yi_high]];

	float remap_tx = tx * tx * (3 - 2 * tx);
	float remap_ty = ty * ty * (3 - 2 * ty);

	float nx0 = lerp(c00, c10, remap_tx);
	float nx1 = lerp(c01, c11, remap_tx);

	return lerp(nx0, nx1, remap_ty);
}

float Perlin2D_V2::lerp(const float& xLow, const float& xHigh, const float& t) {
	return xLow * (1 - t) + xHigh * t;
}

void Perlin2D_V2::make_rand_hash() {
	
	std::mt19937 gen1(1001);
	std::uniform_real_distribution<> distrFloat(0, 1);
	auto rand_float = std::bind(distrFloat, gen1);

	for (int i = 0; i < m_max_vertices; i++) {
		//m_random[i] = rand_float();
		m_random[i] = rand()/(float) RAND_MAX;
		m_permutation_table[i] = i;
	}
	
	std::mt19937 gen(1001);
	std::uniform_int_distribution<> distrUint;
	auto randInt = std::bind(distrUint, gen);

	for (int i = 0; i < m_max_vertices; i++) {
		unsigned random_index = randInt() &( m_max_vertices - 1);
		std::swap(m_permutation_table[i], m_permutation_table[random_index]);
		m_permutation_table[i + m_max_vertices] = m_permutation_table[i];
	}

}

void Perlin2D_V2::create_noise(const int& num_steps) {
	unsigned imageWidth = 512;
	unsigned imageHeight = 512;
	if (m_perlin == nullptr)
		m_perlin = (float*)malloc(sizeof(float) * 512 * 512);

	make_rand_hash();

	// generate value noise
	float frequency = 1;
	for (unsigned j = 0; j < imageHeight; ++j) {
		for (unsigned i = 0; i < imageWidth; ++i) {
			// generate a float in the range [0:1]
			m_perlin[j * imageWidth + i] = eval_signed_periodic_smoothstep_hash(i * frequency, j * frequency);
		}
	}

	// output noise map to PPM
	std::ofstream ofs;
	ofs.open("noise.ppm", std::ios::out | std::ios::binary);
	ofs << "P6\n" << imageWidth << " " << imageHeight << "\n255\n";
	for (unsigned k = 0; k < imageWidth * imageHeight; ++k) {
		unsigned char n = (unsigned char)(m_perlin[k] * 255);
		ofs << n << n << n;
	}
	ofs.close();
}

void Perlin2D_V2::create_noise_fractal_sum(const int& layers) {
	unsigned imageWidth = 512, imageHeight = 512;
	float invImageWidth = 1.f / imageWidth;
	float invImageHeight = 1.f / imageHeight;
	float noiseFrequency = 2;

	if (m_perlin == nullptr)
		m_perlin = (float*)calloc(imageHeight * imageWidth, sizeof(float));
	
	make_rand_hash();
	
	float max_noise = 0;
	for (unsigned j = 0; j < imageHeight; ++j) {
		for (unsigned i = 0; i < imageWidth; ++i) {
			float x = i * invImageWidth * noiseFrequency;
			float y = j * invImageHeight * noiseFrequency;
			float amplitude = 1;
			for (int l = 0; l < layers; l++) {
				m_perlin[j * imageWidth + i] += eval_signed_periodic_smoothstep_hash(x, y);
				x *= 1.4; y*= 1.4;
				amplitude *= 0.9f;
			}
			if (m_perlin[j * imageWidth + i] > max_noise) max_noise = m_perlin[j * imageWidth + i];
		}
	}

	for (int i = 0; i < imageWidth * imageHeight; i++) {
		m_perlin[i] /= max_noise;
	}
	
	// output noise map to PPM
	std::ofstream ofs;
	ofs.open("noise.ppm", std::ios::out | std::ios::binary);
	ofs << "P6\n" << imageWidth << " " << imageHeight << "\n255\n";
	for (unsigned k = 0; k < imageWidth * imageHeight; ++k) {
		unsigned char n = (unsigned char)(m_perlin[k] * 255);
		ofs << n << n << n;
	}
	ofs.close();

}
void Perlin2D_V2:: make_rand() {
	for (int i = 0; i < m_max_vertices * m_max_vertices; i++)
		m_random[i] = rand() / (float)RAND_MAX;
}
void Perlin2D_V2::draw() {
	if (m_perlin == nullptr)
		return;

	float height_cell = 2 / (float)512;
	float width_cell = 2 / (float)512;

	for (int y = 0; y < 512; y++) {
		for (int x = 0; x < 512; x++) {
			glColor3f(m_perlin[y * 512 + x], m_perlin[y * 512 + x], m_perlin[y * 512 + x]);
			glVertex2f(width_cell * x - 1, height_cell * y - 1);
			glVertex2f(width_cell * (x + 1) - 1, height_cell * y - 1);
			glVertex2f(width_cell * (x + 1) - 1, height_cell * (y + 1) - 1);
			glVertex2f(width_cell * x - 1, height_cell * (y + 1) - 1);
		}
	}
}