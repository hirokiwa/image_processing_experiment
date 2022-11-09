/* Sobel �������������t�B���^ sobel.cpp */
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include"mypgpm.h"

double data[MAX_IMAGESIZE][MAX_IMAGESIZE];

void spacial_filtering( )
/* �摜�̋�ԃt�B���^�����O���s���D                     */
/* Sobel�t�B���^�i�������������j                        */
/* ���摜 image1[y][x] ===> �ϊ���̉摜 image2[y][x]   */
{
    /* �K�p����t�B���^�̒�`�iSobel������������) */
    //test----------------------------
    //int weight[3][3] = {
    //    { -1,  0,  1 },
    //    { -2,  0,  2 },
    //    { -1,  0,  1 }  };
    //---------------------------------
    // �ۑ�P----------------------------
    int weight[3][3] = {
        { -2,  0,  2 },
        { -4,  0,  4 },
        { -2,  0,  2 } };
    //---------------------------------
    //�ۑ�Q---------------------------
    //int weight[3][3] = {
    //  { -1,  -2,  -1 },
    //    { 0,  0,  0 },
    //    { 1,  2,  1 } };
    //---------------------------------
    //���W�ۑ�P---------------------------
    //int weight[3] = {-1,0,1 };
    //---------------------------------
    //���W�ۑ�Q---------------------------
    //int weight[3][3] = {
    //    { -1,  0,  1 },
    //    { -1,  0,  1 },
    //    { -1,  0,  1 } };
    //---------------------------------
    //���W�ۑ�R---------------------------
    //int weight[3][3] = {
    //   { -1,  0,  1 },
    //   { -2,  0,  2 },
    //    { -1,  0,  1 } };
    //---------------------------------
    double div_const = 1.0; /* <== �Ō�Ɋ���l */
    double pixel_value; /* �v�Z�l */
    double min, max; /* �v�Z�l�̍ŏ��l�C�ő�l */
    int x, y, i, j;  /* ���[�v�ϐ� */

    /* �t�B���^�����O��̊K���l�̍ŏ��l�C�ő�l�����߂� */
    printf("���摜�̃t�B���^�����O�����Ă��܂��D\n");
    min = (double)INT_MAX;
    max = (double)INT_MIN;
    for ( y = 1; y < y_size1 - 1; y ++ ){
        for ( x = 1; x < x_size1 - 1; x ++ ){
            pixel_value = 0.0;

            //���W1�ȊO------------------
            for ( i = -1; i < 2; i++){	
                for (j = -1; j < 2; j++) {
                    pixel_value = pixel_value +	
                    weight[i + 1][j + 1] * image1[y + i][x + j];	
                }
            }
            //------------------------
            //���W1--------------------
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
    /* image2[y][x] �̏�����(�O�s�̉�f�̂��߁j*/
    x_size2 = x_size1;  y_size2 = y_size1;
    for ( y = 0; y < y_size2; y ++ )
        for ( x = 0; x < x_size2; x ++ )
            image2[y][x] = 0;
    /* ������̒l����`�ϊ����Ă��� image2 �ɑ�� */

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
//	 �Q�Q�Q�Q�Q�Q�Q�Q�Q						
	/*	 c	 */	   /* �摜��ǂݍ���� image1 �� */ 
    load_image_data();
//	�P�P�P�P�P�P�P�P�P						
//	 �Q�Q�Q�Q�Q�Q�Q�Q�Q						
	/*	 d	 */	   /* ��ԃt�B���^�����O���� image2 �� */
    spacial_filtering();
//	�P�P�P�P�P�P�P�P�P						
//	 �Q�Q�Q�Q�Q�Q�Q�Q�Q						
	/*	 e	 */	   /* image2 ��ۑ����� */
    save_image_data();
//	�P�P�P�P�P�P�P�P�P						
    return 0;
}
