/* �J���[�摜(RGB)���甒����(Y���o)�v���O���� rgb2y.cpp */
//#include<stdio.h>
//#include<stdlib.h>
#include"mypgpm.h"

void make_y_image( )
/* ���摜 image1_ppm ����Y���o���� image2 �ɑ������ */
{
    double Y, U, V;
    int x, y;    /* ����ϐ� */

    printf("�����摜���쐬���܂��D\n");
    x_size2 = x_size1;  /* ����f�� */
    y_size2 = y_size1;  /* �c��f�� */
    for ( y = 0; y < y_size2; y ++ ){
//	       �Q�Q�Q�Q�Q�Q�Q�Q�Q�Q			
        for (x = 0; x < x_size1; x++ ) {
//	      �P�P�P�P�P�P�P�P�P�P			
           // image2[y][x] = (unsigned char)	//�ϊ���
                //�ϊ��T
             //   0.299 * image1_ppm[y][x][0] + 0.587 * image1_ppm[y][x][1] + 0.114 * image1_ppm[y][x][2];

                //�ϊ��V �ۑ�(1)
                // (image1_ppm[y][x][0] + image1_ppm[y][x][1] + image1_ppm[y][x][2]) / 3;

                //�ϊ��U  �ۑ�(2)
                

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
    load_image_data_ppm(); /* �摜�f�[�^�� image1_ppm �ɓǂݍ��� */
	make_y_image();        /* image1_ppm ��Y�ϊ��� image2 �� */
    //save_image_data();     /* image2 ��ۑ����� */
    save_image_data_ppm();     /* image2.ppm ��ۑ����� */
    return 0;
}