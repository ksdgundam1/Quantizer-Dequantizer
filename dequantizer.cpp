#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

const int width = 512, height = 512;

unsigned char quantized_rgb[1536][512];
unsigned char dequantized_rgb[1536][512];
unsigned char original_rgb[1536][512];

int main()
{
	FILE* quantized_image = fopen("Lenna_512X512_quantized.raw", "rb");
	FILE* dequantized_image = fopen("Lenna_512X512_dequantized.raw", "w+");

	int bits = -1, sum = 1;
	printf("input quantized bits (0 ~ 7)\n>>");
	scanf("%d", &bits);

	for (int i = 0; i < bits; i++)
		sum *= 2;

	const int quantized_level = sum;
	const int quantize_step = 512 / quantized_level;

	fread(quantized_rgb, sizeof(unsigned char), width * 3 * height, quantized_image);

	for (int i = 0; i < 3 * height; i++)
		for (int j = 0; j < width; j++)
			dequantized_rgb[i][j] = (quantized_rgb[i][j] * quantize_step) + (quantize_step / 2);

	fwrite(dequantized_rgb, sizeof(unsigned char), width * 3 * height, dequantized_image);

	//MSE 측정용 테스트
	FILE* original_image = fopen("Lenna_512x512_original.raw", "rb");
	fread(original_rgb, sizeof(unsigned char), width * 3 * height, original_image);

	long long MSE = 0;
	for (int i = 0; i < 3 * height; i++)
		for (int j = 0; j < width; j++)
		{
			MSE += (((long long)original_rgb[i][j] - (long long)dequantized_rgb[i][j]) * ((long long)original_rgb[i][j] - (long long)dequantized_rgb[i][j]));
			//printf("%ld\n", MSE);
		}
	MSE /= (3 * height * width);
	printf("MSE>> %ld", MSE);

	fclose(original_image);

	fclose(quantized_image);
	fclose(dequantized_image);

	return 0;
}
