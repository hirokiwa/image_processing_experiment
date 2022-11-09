/*�d�q�������̃v���O���� sukashi.cpp*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"mypgpm.h"
#include"FFT.h"

/*����������摜�Ɋ|����W��(=��)*/
//#define RATIO 0 ;
//#define RATIO 0.01 ;
//#define RATIO 0.1 ;
//#define RATIO 1 ;
//#define RATIO 10 ;
#define RATIO 100 ;

double data2[FFT_MAX][FFT_MAX];
double jdata2[FFT_MAX][FFT_MAX];

void make_data()/*image1[y][x]�̃f�[�^��data[y][x],jdata[y][x]�ɑ������*/
{
  int i,j;
  num_of_data=x_size1;
  for(i=0;i<num_of_data;i++){
    for(j=0;j<num_of_data;j++){
      data[i][j]=(double)image1[i][j];
      jdata[i][j]=0.0;
    }
  }
}

void make_output_image()/*�f�[�^data[y][x],jdata[y][x]��image2[y][x]�ɂȂ����i������f�[�^�̃N���b�s���O�j*/
{
  int x,y;
  
  x_size2=num_of_data; y_size2=num_of_data;
  for(x=0;x<x_size2;x++){
    for(y=0;y<y_size2;y++){
      if(data[y][x]<0.0) image2[y][x]=0;
      else if(data[y][x]>255) image2[y][x]=255;
      else image2[y][x]=(unsigned char)data[y][x];
    }
  }
}

void copy_image_data()/*image1[y][x]==>image2[y][x]�փf�[�^���R�s�[�i�����O�̃f�[�^�R�s�[�j*/
{
  int i,j;
  
  for(i=0;i<y_size1;i++){
    for(j=0;j<x_size1;j++){
      image2[i][j]=image1[i][j];
    }
  }
  y_size2=y_size1; x_size2=x_size1;
}

void copy_FFT_data()/*data,jdata==>data2,jdata2�̃f�[�^�̃R�s�[�i�����O�̕��f�������f�[�^�̃R�s�[�j*/
{
  int i,j;
  
  for(i=0;i<num_of_data;i++){
    for(j=0;j<num_of_data;j++){
      data2[j][i]=data[j][i];
      jdata2[j][i]=jdata[j][i];
    }
  }
}

void coding()/*���摜�ƍ�������摜���w�肵�ē���������̉摜��ۑ�����*/
{
  int i,j;
  
  printf("\n��������摜��ǂݍ��݂܂�\n");
  load_image_data();
  copy_image_data();
  printf("\n���摜��ǂݍ��݂܂�\n");
  load_image_data();
  make_data();
  FFT2( 1 );
  for(i=0;i<y_size1;i++){
    for(j=0;j<x_size1;j++){
//	 	 �Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q					


        data[i][j] = data[i][j] + image2[i][j] * RATIO;

//		�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P        //
	}
  }
  FFT2( -1);/*2�����@�tFFT�̎��s*/
  make_output_image();
  //���W�ۑ�
 
  double snr; 
  double A = 0;
  double B = 0;

  for (i = 0; i < x_size1; i++) {
      for (j = 0; j < y_size1; j++) {
          A = A + image1[j][i] * image1[j][i];
      }
  }

  for (i = 0; i < x_size1; i++) {
      for (j = 0; j < y_size1; j++) {
         B = B + (image1[j][i] - image2[j][i]) * (image1[j][i] - image2[j][i]);
      }
  }

  snr = 10 * log10(A / B);
  printf("SNR�F%f\n", snr);

  printf("\n�d�q����������̉摜��ۑ����܂�\n");
  save_image_data();
}

void decoding()
/*����������̉摜�ƌ��摜���w�肵�Ē��o���ꂽ�摜��ۑ�����*/
{
  int i,j;
  double d;
  
  printf("\n���摜��ǂݍ��݂܂�\n");
  load_image_data();
  make_data();
  FFT2(1);
  copy_FFT_data();
  printf("\n����������̉摜��ǂݍ��݂܂�\n");
  load_image_data();
  make_data();
  FFT2(1);
  x_size2=x_size1; y_size2=y_size1;
  for(i=0;i<y_size2;i++){
    for(j=0;j<x_size2;j++){
//	 	     �Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q						
        d = (data[i][j] - data2[i][j]) / RATIO;
//		    �P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P        //	
      if(d<0.0) image2[i][j]=0;
      else if(d>MAX_BRIGHTNESS)
        image2[i][j]=MAX_BRIGHTNESS;
      else image2[i][j]=(unsigned char)d;
    }
  }
  printf("\n���o���ꂽ�摜��ۑ����܂�\n");
  save_image_data();
}

int main()
{
  int mode;
  
  printf("***�d�q�������̃v���O����***\n");
  do{
    printf("������������(1)/�����������(-1)");
    scanf("%d",&mode);
  }while(mode!=1&&mode!=-1);
  if(mode==1) coding();
  else decoding();

  return 0;
}
