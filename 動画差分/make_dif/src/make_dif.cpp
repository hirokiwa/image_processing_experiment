/* �摜�Ԃ̍����摜�����߂�v���O���� make_dif.cpp */
#include<stdio.h>
#include<stdlib.h>
#include"mypgpm.h"

/* image1 �̉摜�f�[�^�� image2 �փR�s�[���� */
void copy_image1_to_image2( )
{
    int x, y;  /* ���[�v�ϐ� */

    x_size2 = x_size1;  y_size2 = y_size1;
    for ( y = 0; y < y_size1; y ++ )
        for ( x = 0; x < x_size1; x ++ )
            image2[y][x] = image1[y][x];
}

/* �摜�ԍ��������߂�*/
void make_difference_image()
{
    int x, y;        /* ���[�v�ϐ�   */
    int difference;  /* �����̐�Βl */

    printf("frame1 �� frame2 �̉�f���Ƃ̊K���l�̍�����\n");
    printf("��Βl�����߂� image2[y][x] �ɑ�����܂��D\n");
    for (y = 0; y < y_size2; y++) {
        for (x = 0; x < x_size2; x++) {
            //test---------------------
            //difference = abs( image1[y][x] - image2[y][x]);/*abs�͐�Βl������킷*/
            //--------------------------		

            //���W�P�A�Q------------------
            difference = abs(((image2[y][x] - image1[y][x]) / 2) + 128);
            //----------------------------


            image2[y][x] = (unsigned char)difference;
            //image2[y][x] = (unsigned char)(image1[y][x] + 2 * (difference - 128));
        }
    }
}

/*�@�����摜����Q�l�摜���쐬���� */
void make_mask_image( )
{
    int x, y;      /* ���[�v�ϐ� */
    int max_dif;   /* �Q�l����臒l */

    printf("�����摜����Q�l�摜�����܂��D\n");
    do {
        printf("�Q�l����臒l (1�`100) : ");
        scanf("%d", &max_dif);
		
     } while ( max_dif <1 || max_dif > 100);
		

    /* �Q�l���摜�̐��� */
    for ( y = 0; y < y_size2; y ++ )
        for ( x = 0; x < x_size2; x ++ )
//		 �Q�Q�Q�Q�Q�Q�Q�Q�Q
            if ( image2[y][x] > max_dif)
//		 �P�P�P�P�P�P�P�P�P
             image2[y][x] = MAX_BRIGHTNESS;
//		 �Q�Q�Q�Q�Q�Q�Q�Q�Q
            else  image2[y][x] = 0;
//		 �P�P�P�P�P�P�P�P�P
}

int main( )
{
    printf("*** frame No.1 �̃f�[�^��ǂݍ��݂܂��D\n");
    load_image_data( );        /* frame1 �f�[�^ --> image1  */
    copy_image1_to_image2( );  /* frame1 �f�[�^ --> image2  */
    printf("*** frame No.2 �̃f�[�^��ǂݍ��݂܂��D\n");
    load_image_data( );        /* frame2 �f�[�^ --> image1  */
    make_difference_image( );  /* ���������߂� image2 ��    */
    printf("*** �����摜�̃f�[�^��ۑ����܂��D\n");
    save_image_data( );        /* �����摜 --> �o��         */
    make_mask_image( );        /* �����}�X�N�摜 --> image2 */
    printf("*** �����摜���������}�X�N�摜��ۑ����܂��D\n");
    save_image_data( );        /* �}�X�N�摜 --> �o��       */
    return 0;
}
