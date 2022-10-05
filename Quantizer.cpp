#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

const int width = 512, height = 512;

char original_red[512][512];    //512 * 512 size image source
char original_green[512][512];
char original_blue[512][512];

char quantized_red[512][512];
char quantized_green[512][512];
char quantized_blue[512][512];

int main(void)
{
    FILE* original_image = NULL, * quantized_image = NULL;

    // raw 파일 읽어오기
    original_image = fopen("Lenna_512x512_original.raw", "rb");
    if (original_image == NULL)
    {
        printf("File not found!!\n");
        //return;
    }
    
    //rgb 정보 읽기
    fread(original_red, sizeof(char), width * height, original_image);
    fread(original_green, sizeof(char), width * height, original_image);
    fread(original_blue, sizeof(char), width * height, original_image);

    for (int i = 240; i < 260; i++)
    {
        printf("{");
        for (int j = 280; j < 300; j++)
        {
            printf("%5d", original_red[i][j]);
        }
        printf("\t]\n");
    }

    //양자화
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            //quantized_red[i][j] = original_red[i][j];
            quantized_green[i][j] = original_green[i][j];
            //quantized_blue[i][j] = original_blue[i][j];
        }
    }
    // 변환한 이미지 저장
    quantized_image = fopen("Lenna_512x512_quantized.raw", "w+");
    fwrite(quantized_red, sizeof(char), width * height, quantized_image);
    fwrite(quantized_green, sizeof(char), width * height, quantized_image);
    fwrite(quantized_blue, sizeof(char), width * height, quantized_image);

    fclose(original_image);
    fclose(quantized_image);

    return 0;
}