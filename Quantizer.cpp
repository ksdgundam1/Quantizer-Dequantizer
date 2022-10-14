#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

const int width = 512, height = 512;
//const int quantized_level = 32;

unsigned char original_rgb[1536][512];    //512 * 512 size image source
unsigned char quantized_rgb[1536][512];

int main(void)
{
    //����ȭ�� ���� �Է�
    FILE* original_image = fopen("Lenna_512x512_original.raw", "rb");
    FILE* quantized_image = fopen("Lenna_512x512_quantized.raw", "w+");
    
    //����ȭ�� ��Ʈ �� ����
    int bits = -1, sum = 1;
    printf("input quantize bits (1 ~ 7)\n>>");
    scanf("%d", &bits);

    for (int i = 0; i < bits; i++)
        sum *= 2;

    const int quantized_level = sum;
    printf("quantized level>>%3d\n", quantized_level);
    const int quantize_step = 512 / quantized_level;


    //rgb ���� �б�
    fread(original_rgb, sizeof(unsigned char), width * 3 * height, original_image);

    //����ȭ
    for (int i = 0; i < 3 * height; i++)
        for (int j = 0; j < width; j++)
            for (int k = 0; k < quantized_level; k++)
                if((original_rgb[i][j] >= (k * quantize_step)) && (quantized_rgb[i][j] < ((k + 1) * quantize_step)))
                    quantized_rgb[i][j] = k;

    fwrite(quantized_rgb, sizeof(unsigned char), width * 3 * height, quantized_image);
  
    fclose(original_image);
    fclose(quantized_image);

    return 0;
}