#include "stencil.h"

void ApplyStencil(unsigned char *img_in, unsigned char *img_out, int width, int height) {
  
	short val;
	unsigned char val_out;

	for (int i = 1; i < height-1; i++)
		for (int j = 1; j < width-1; j++) {
			val = img_in[(i  )*width + j];
			__m256i a = _mm256_load_size256((__m256i const *)&img_in[i *width + j]);
			__m256i b = _mm256_load_size256((__m256i const *)&img_in[(i-1)*width + j-1]);
			__m256i c = _mm256_load_size256((__m256i const *)&img_in[(i-1)*width + j]);
			__m256i d = _mm256_load_size256((__m256i const *)&img_in[(i-1)*width + j+1]);
			__m256i e = _mm256_load_size256((__m256i const *)&img_in[i*width + j-1]);
			__m256i f = _mm256_load_size256((__m256i const *)&img_in[i*width + j]);

			__m256i g = _mm256_load_size256((__m256i const *)&img_in[(i-1)*width + j]);
			__m256i h = _mm256_load_size256((__m256i const *)&img_in[(i-1)*width + j]);

			val +=	-img_in[(i-1)*width + j-1] -   img_in[(i-1)*width + j] - img_in[(i-1)*width + j+1] 
					-img_in[(i  )*width + j-1] + 7*img_in[(i  )*width + j] - img_in[(i  )*width + j+1] 
					-img_in[(i+1)*width + j-1] -   img_in[(i+1)*width + j] - img_in[(i+1)*width + j+1];

			__m256i z = _mm256_adds_epu8(a, a);
			__m256i res = z;

			__mm256_store_size256((__m256i const *)&img_out[i*width + j], res);
		}
}

void CopyImage(unsigned char *img_in, unsigned char *img_out, int width, int height) {

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			img_in[i*width + j] = img_out[i*width + j];
}
?¿*""