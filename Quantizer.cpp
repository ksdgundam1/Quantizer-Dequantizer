#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

const int width = 512, height = 512;

unsigned char original_red[512][512];    //512 * 512 size image source
unsigned char original_green[512][512];
unsigned char original_blue[512][512];

unsigned char quantized_red[512][512];
unsigned char quantized_green[512][512];
unsigned char quantized_blue[512][512];

int main(void)
{
    FILE* original_image = fopen("Lenna_512x512_original.raw", "rb");
    FILE* quantized_image = NULL;


    //rgb 정보 읽기
    fread(original_red, sizeof(unsigned char), width * height, original_image);
    fread(original_green, sizeof(unsigned char), width * height, original_image);
    fread(original_blue, sizeof(unsigned char), width * height, original_image);

    /*
    for (int i = 240; i < 260; i++)
    {
        printf("{");
        for (int j = 280; j < 300; j++)
        {
            printf("%5d", original_red[i][j]);
        }
        printf("\t]\n");
    }
    */

    //양자화
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            quantized_red[i][j] = original_red[i][j];
            //quantized_green[i][j] = original_green[i][j];
            //quantized_blue[i][j] = original_blue[i][j];
        }
    }

    /*
    for (int i = 0; i < height; i++)
        for (int j = 0; j < height; j++)
            for (int k = 0; k < 16; k++)
                if ((original_red[i][j] >= (k * 16)) && (original_red[i][j] < (k * 16 + 16)))
                    quantized_red[i][j] = k * 16 + 8;       //각 level의 중앙값으로 양자화
    */
    // 변환한 이미지 저장
    quantized_image = fopen("Lenna_512x512_quantized.raw", "w+");

    fwrite(quantized_red, sizeof(unsigned char), width * height, quantized_image);
    fclose(quantized_image);

    quantized_image = fopen("Lenna_512x512_quantized.raw", "a");
    fwrite(quantized_green, sizeof(unsigned char), width * height, quantized_image);
    fclose(quantized_image);

    quantized_image = fopen("Lenna_512x512_quantized.raw", "a");
    fwrite(quantized_blue, sizeof(unsigned char), width * height, quantized_image);
  
    fclose(original_image);
    fclose(quantized_image);

    return 0;
}