/* ƒJƒ‰[‰æ‘œ(RGB)‚©‚ç”’•‰»(Y’Šo)ƒvƒƒOƒ‰ƒ€ rgb2y.cpp */
//#include<stdio.h>
//#include<stdlib.h>
#include"mypgpm.h"

void make_y_image( )
/* Œ´‰æ‘œ image1_ppm ‚©‚çY’Šo‚µ‚Ä image2 ‚É‘ã“ü‚·‚é */
{
    double Y, U, V;
    int x, y;    /* §Œä•Ï” */

    printf("”’•‰æ‘œ‚ğì¬‚µ‚Ü‚·D\n");
    x_size2 = x_size1;  /* ‰¡‰æ‘f” */
    y_size2 = y_size1;  /* c‰æ‘f” */
    for ( y = 0; y < y_size2; y ++ ){
//	       QQQQQQQQQQ			
        for (x = 0; x < x_size1; x++ ) {
//	      PPPPPPPPPP			
           // image2[y][x] = (unsigned char)	//•ÏŠ·®
                //•ÏŠ·‡T
             //   0.299 * image1_ppm[y][x][0] + 0.587 * image1_ppm[y][x][1] + 0.114 * image1_ppm[y][x][2];

                //•ÏŠ·‡V ‰Û‘è(1)
                // (image1_ppm[y][x][0] + image1_ppm[y][x][1] + image1_ppm[y][x][2]) / 3;

                //•ÏŠ·‡U  ‰Û‘è(2)
                

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
    load_image_data_ppm(); /* ‰æ‘œƒf[ƒ^‚ğ image1_ppm ‚É“Ç‚İ‚Ş */
	make_y_image();        /* image1_ppm ‚ğY•ÏŠ·‚µ image2 ‚Ö */
    //save_image_data();     /* image2 ‚ğ•Û‘¶‚·‚é */
    save_image_data_ppm();     /* image2.ppm ‚ğ•Û‘¶‚·‚é */
    return 0;
}