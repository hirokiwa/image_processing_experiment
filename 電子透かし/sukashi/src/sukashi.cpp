/*“dq“§‚©‚µ‚ÌƒvƒƒOƒ‰ƒ€ sukashi.cpp*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"mypgpm.h"
#include"FFT.h"

/*¬“ü‚³‚¹‚é‰æ‘œ‚ÉŠ|‚¯‚éŒW”(=ƒÃ)*/
//#define RATIO 0 ;
//#define RATIO 0.01 ;
//#define RATIO 0.1 ;
//#define RATIO 1 ;
//#define RATIO 10 ;
#define RATIO 100 ;

double data2[FFT_MAX][FFT_MAX];
double jdata2[FFT_MAX][FFT_MAX];

void make_data()/*image1[y][x]‚Ìƒf[ƒ^‚ğdata[y][x],jdata[y][x]‚É‘ã“ü‚·‚é*/
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

void make_output_image()/*ƒf[ƒ^data[y][x],jdata[y][x]‚ğimage2[y][x]‚É‚È‚¨‚·iˆ—Œãƒf[ƒ^‚ÌƒNƒŠƒbƒsƒ“ƒOj*/
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

void copy_image_data()/*image1[y][x]==>image2[y][x]‚Öƒf[ƒ^‚ğƒRƒs[iˆ—‘O‚Ìƒf[ƒ^ƒRƒs[j*/
{
  int i,j;
  
  for(i=0;i<y_size1;i++){
    for(j=0;j<x_size1;j++){
      image2[i][j]=image1[i][j];
    }
  }
  y_size2=y_size1; x_size2=x_size1;
}

void copy_FFT_data()/*data,jdata==>data2,jdata2‚Ìƒf[ƒ^‚ÌƒRƒs[iˆ—‘O‚Ì•¡‘f‰»‚µ‚½ƒf[ƒ^‚ÌƒRƒs[j*/
{
  int i,j;
  
  for(i=0;i<num_of_data;i++){
    for(j=0;j<num_of_data;j++){
      data2[j][i]=data[j][i];
      jdata2[j][i]=jdata[j][i];
    }
  }
}

void coding()/*Œ´‰æ‘œ‚Æ¬“ü‚·‚é‰æ‘œ‚ğw’è‚µ‚Ä“§‚©‚µ“ü‚è‚Ì‰æ‘œ‚ğ•Û‘¶‚·‚é*/
{
  int i,j;
  
  printf("\n¬“ü‚·‚é‰æ‘œ‚ğ“Ç‚İ‚İ‚Ü‚·\n");
  load_image_data();
  copy_image_data();
  printf("\nŒ´‰æ‘œ‚ğ“Ç‚İ‚İ‚Ü‚·\n");
  load_image_data();
  make_data();
  FFT2( 1 );
  for(i=0;i<y_size1;i++){
    for(j=0;j<x_size1;j++){
//	 	 QQQQQQQQQQQQQQQQQQQ					


        data[i][j] = data[i][j] + image2[i][j] * RATIO;

//		PPPPPPPPPPPPPPPPPPP        //
	}
  }
  FFT2( -1);/*2ŸŒ³@‹tFFT‚ÌÀs*/
  make_output_image();
  //”­“W‰Û‘è
 
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
  printf("SNRF%f\n", snr);

  printf("\n“dq“§‚©‚µ“ü‚è‚Ì‰æ‘œ‚ğ•Û‘¶‚µ‚Ü‚·\n");
  save_image_data();
}

void decoding()
/*“§‚©‚µ“ü‚è‚Ì‰æ‘œ‚ÆŒ´‰æ‘œ‚ğw’è‚µ‚Ä’Šo‚³‚ê‚½‰æ‘œ‚ğ•Û‘¶‚·‚é*/
{
  int i,j;
  double d;
  
  printf("\nŒ´‰æ‘œ‚ğ“Ç‚İ‚İ‚Ü‚·\n");
  load_image_data();
  make_data();
  FFT2(1);
  copy_FFT_data();
  printf("\n“§‚©‚µ“ü‚è‚Ì‰æ‘œ‚ğ“Ç‚İ‚İ‚Ü‚·\n");
  load_image_data();
  make_data();
  FFT2(1);
  x_size2=x_size1; y_size2=y_size1;
  for(i=0;i<y_size2;i++){
    for(j=0;j<x_size2;j++){
//	 	     QQQQQQQQQQQQQQQQQQQ						
        d = (data[i][j] - data2[i][j]) / RATIO;
//		    PPPPPPPPPPPPPPPPPPP        //	
      if(d<0.0) image2[i][j]=0;
      else if(d>MAX_BRIGHTNESS)
        image2[i][j]=MAX_BRIGHTNESS;
      else image2[i][j]=(unsigned char)d;
    }
  }
  printf("\n’Šo‚³‚ê‚½‰æ‘œ‚ğ•Û‘¶‚µ‚Ü‚·\n");
  save_image_data();
}

int main()
{
  int mode;
  
  printf("***“dq“§‚©‚µ‚ÌƒvƒƒOƒ‰ƒ€***\n");
  do{
    printf("“§‚©‚µ‚ğ“ü‚ê‚é(1)/“§‚©‚µ‚ğæ‚é(-1)");
    scanf("%d",&mode);
  }while(mode!=1&&mode!=-1);
  if(mode==1) coding();
  else decoding();

  return 0;
}
