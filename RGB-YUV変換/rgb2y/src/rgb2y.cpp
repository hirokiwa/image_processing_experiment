/* カラー画像(RGB)から白黒化(Y抽出)プログラム rgb2y.cpp */
//#include<stdio.h>
//#include<stdlib.h>
#include"mypgpm.h"

void make_y_image( )
/* 原画像 image1_ppm からY抽出して image2 に代入する */
{
    double Y, U, V;
    int x, y;    /* 制御変数 */

    printf("白黒画像を作成します．\n");
    x_size2 = x_size1;  /* 横画素数 */
    y_size2 = y_size1;  /* 縦画素数 */
    for ( y = 0; y < y_size2; y ++ ){
//	       ＿＿＿＿＿＿＿＿＿＿			
        for (x = 0; x < x_size1; x++ ) {
//	      ￣￣￣￣￣￣￣￣￣￣			
           // image2[y][x] = (unsigned char)	//変換式
                //変換?T
             //   0.299 * image1_ppm[y][x][0] + 0.587 * image1_ppm[y][x][1] + 0.114 * image1_ppm[y][x][2];

                //変換?V 課題(1)
                // (image1_ppm[y][x][0] + image1_ppm[y][x][1] + image1_ppm[y][x][2]) / 3;

                //変換?U  課題(2)
                

                Y = 0.299 * image1_ppm[y][x][0] + 0.587 * image1_ppm[y][x][1] + 0.114 * image1_ppm[y][x][2];;
                U = -0.169 * image1_ppm[y][x][0] - 0.332 * image1_ppm[y][x][1] + 0.500 * image1_ppm[y][x][2];
                V = 0.500 * image1_ppm[y][x][0] - 0.419 * image1_ppm[y][x][1] - 0.081 * image1_ppm[y][x][2];
                 
                image2_ppm[y][x][0] = (unsigned char)( Y + 1.402 * V);
                image2_ppm[y][x][1] = (unsigned char)( Y - 0.344 * U - 0.714 * V);
                image2_ppm[y][x][2] = (unsigned char) (Y + 1.772 * U);
        }
    }
}

int main( )
{
    load_image_data_ppm(); /* 画像データを image1_ppm に読み込む */
	make_y_image();        /* image1_ppm をY変換し image2 へ */
    //save_image_data();     /* image2 を保存する */
    save_image_data_ppm();     /* image2.ppm を保存する */
    return 0;
}