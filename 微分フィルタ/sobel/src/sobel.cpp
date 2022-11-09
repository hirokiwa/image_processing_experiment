/* Sobel …•½•ûŒü”÷•ªƒtƒBƒ‹ƒ^ sobel.cpp */
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include"mypgpm.h"

double data[MAX_IMAGESIZE][MAX_IMAGESIZE];

void spacial_filtering( )
/* ‰æ‘œ‚Ì‹óŠÔƒtƒBƒ‹ƒ^ƒŠƒ“ƒO‚ğs‚¤D                     */
/* SobelƒtƒBƒ‹ƒ^i…•½•ûŒü”÷•ªj                        */
/* Œ´‰æ‘œ image1[y][x] ===> •ÏŠ·Œã‚Ì‰æ‘œ image2[y][x]   */
{
    /* “K—p‚·‚éƒtƒBƒ‹ƒ^‚Ì’è‹`iSobel…•½•ûŒü”÷•ª) */
    //test----------------------------
    //int weight[3][3] = {
    //    { -1,  0,  1 },
    //    { -2,  0,  2 },
    //    { -1,  0,  1 }  };
    //---------------------------------
    // ‰Û‘è‚P----------------------------
    int weight[3][3] = {
        { -2,  0,  2 },
        { -4,  0,  4 },
        { -2,  0,  2 } };
    //---------------------------------
    //‰Û‘è‚Q---------------------------
    //int weight[3][3] = {
    //  { -1,  -2,  -1 },
    //    { 0,  0,  0 },
    //    { 1,  2,  1 } };
    //---------------------------------
    //”­“W‰Û‘è‚P---------------------------
    //int weight[3] = {-1,0,1 };
    //---------------------------------
    //”­“W‰Û‘è‚Q---------------------------
    //int weight[3][3] = {
    //    { -1,  0,  1 },
    //    { -1,  0,  1 },
    //    { -1,  0,  1 } };
    //---------------------------------
    //”­“W‰Û‘è‚R---------------------------
    //int weight[3][3] = {
    //   { -1,  0,  1 },
    //   { -2,  0,  2 },
    //    { -1,  0,  1 } };
    //---------------------------------
    double div_const = 1.0; /* <== ÅŒã‚ÉŠ„‚é’l */
    double pixel_value; /* ŒvZ’l */
    double min, max; /* ŒvZ’l‚ÌÅ¬’lCÅ‘å’l */
    int x, y, i, j;  /* ƒ‹[ƒv•Ï” */

    /* ƒtƒBƒ‹ƒ^ƒŠƒ“ƒOŒã‚ÌŠK’²’l‚ÌÅ¬’lCÅ‘å’l‚ğ‹‚ß‚é */
    printf("Œ´‰æ‘œ‚ÌƒtƒBƒ‹ƒ^ƒŠƒ“ƒO‚ğ‚µ‚Ä‚¢‚Ü‚·D\n");
    min = (double)INT_MAX;
    max = (double)INT_MIN;
    for ( y = 1; y < y_size1 - 1; y ++ ){
        for ( x = 1; x < x_size1 - 1; x ++ ){
            pixel_value = 0.0;

            //”­“W1ˆÈŠO------------------
            for ( i = -1; i < 2; i++){	
                for (j = -1; j < 2; j++) {
                    pixel_value = pixel_value +	
                    weight[i + 1][j + 1] * image1[y + i][x + j];	
                }
            }
            //------------------------
            //”­“W1--------------------
            //for (j = -1; j < 2; j++) {
            //    pixel_value = pixel_value +
            //        weight[j + 1] * image1[y][x + j];
            //}
            //-----------------------

			pixel_value = pixel_value / div_const;
	 		data[y][x] = pixel_value;
            if ( pixel_value < min ) min = pixel_value;
            if ( pixel_value > max ) max = pixel_value;
        }
    }
    if ( (int)(max - min) == 0 ) exit(1);
    /* image2[y][x] ‚Ì‰Šú‰»(ŠOŠs‚Ì‰æ‘f‚Ì‚½‚ßj*/
    x_size2 = x_size1;  y_size2 = y_size1;
    for ( y = 0; y < y_size2; y ++ )
        for ( x = 0; x < x_size2; x ++ )
            image2[y][x] = 0;
    /* ˆ—Œã‚Ì’l‚ğüŒ`•ÏŠ·‚µ‚Ä‚©‚ç image2 ‚É‘ã“ü */

	for ( y = 1; y < y_size1 - 1; y ++ ){
        	for ( x = 1; x < x_size1 - 1; x ++ ){
			pixel_value = data[y][x];
			if(pixel_value > 0)
				pixel_value = 128  *  pixel_value / max + 127;
			if(pixel_value < 0)
				pixel_value = 127  *  (min - pixel_value) / min;
			if(pixel_value == 0)
				pixel_value = 127;

            image2[y][x] = (unsigned char)pixel_value;
        }
    }
}

int main( )
{
//	 QQQQQQQQQ						
	/*	 c	 */	   /* ‰æ‘œ‚ğ“Ç‚İ‚ñ‚Å image1 ‚Ö */ 
    load_image_data();
//	PPPPPPPPP						
//	 QQQQQQQQQ						
	/*	 d	 */	   /* ‹óŠÔƒtƒBƒ‹ƒ^ƒŠƒ“ƒO‚µ‚Ä image2 ‚Ö */
    spacial_filtering();
//	PPPPPPPPP						
//	 QQQQQQQQQ						
	/*	 e	 */	   /* image2 ‚ğ•Û‘¶‚·‚é */
    save_image_data();
//	PPPPPPPPP						
    return 0;
}
