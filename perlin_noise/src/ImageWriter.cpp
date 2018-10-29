#define _CRT_SECURE_NO_WARNINGS
#include "ImageWriter.h"

void ImageWriter::write_bmp(const int width, const int height, char* path, float* data) {

	int w = 100, h = 100;
	FILE *f;
	unsigned char *img = NULL;
	int filesize = 54 + 3 * w*h;  //w is your image width, h is image height, both int

	img = (unsigned char *)malloc(3 * w*h);
	memset(img, 0, 3 * w*h);
	float min = 1, max = 0;
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			if (min > *(data + i * width + j))
				min = *(data + i * width + j);
			if (max < *(data + i * width + j))
				max = *(data + i * width + j);
			int x = i; int y = (h - 1) - j;
			int r = *(data + i * width + j) * 255;
			int g = *(data + i * width + j) * 255;
			int b = *(data + i * width + j) * 255;
			if (r > 255) r = 255;
			if (g > 255) g = 255;
			if (b > 255) b = 255;
			img[(x + y * w) * 3 + 2] = (unsigned char)(r);
			img[(x + y * w) * 3 + 1] = (unsigned char)(g);
			img[(x + y * w) * 3 + 0] = (unsigned char)(b);
		}
	}

	std::cout << "min : " << min << " - max : " << max << std::endl;

	unsigned char bmpfileheader[14] = { 'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0 };
	unsigned char bmpinfoheader[40] = { 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0 };
	unsigned char bmppad[3] = { 0,0,0 };

	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize >> 8);
	bmpfileheader[4] = (unsigned char)(filesize >> 16);
	bmpfileheader[5] = (unsigned char)(filesize >> 24);

	bmpinfoheader[4] = (unsigned char)(w);
	bmpinfoheader[5] = (unsigned char)(w >> 8);
	bmpinfoheader[6] = (unsigned char)(w >> 16);
	bmpinfoheader[7] = (unsigned char)(w >> 24);
	bmpinfoheader[8] = (unsigned char)(h);
	bmpinfoheader[9] = (unsigned char)(h >> 8);
	bmpinfoheader[10] = (unsigned char)(h >> 16);
	bmpinfoheader[11] = (unsigned char)(h >> 24);

	f = fopen(path, "wb");
	fwrite(bmpfileheader, 1, 14, f);
	fwrite(bmpinfoheader, 1, 40, f);
	for (int i = 0; i < h; i++)
	{
		fwrite(img + (w*(h - i - 1) * 3), 3, w, f);
		fwrite(bmppad, 1, (4 - (w * 3) % 4) % 4, f);
	}

	free(img);
	fclose(f);
}