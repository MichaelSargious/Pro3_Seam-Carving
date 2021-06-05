#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "image.h"


int pixel_read_from_file (FILE* f , struct pixel* pix ) {

    if ((fscanf( f , "%d %d %d", &pix->red, &pix->green, &pix->blue)) == 3)
            return 1;
            else
                return 0;
}

int statistiken (FILE* f , int num , int w , int h  ){
    int mag_counter = 0 ;
    int w_s , h_s ;
    unsigned int ww = w ;
    unsigned int hh = h ;
    int r = 0 ;
    int g = 0 ;
    int b = 0 ;
    double total = 0.0 ;

    if(fscanf(f , "P3\n%d %d\n255\n" , &w_s , &h_s) !=2 ) return EXIT_FAILURE ;
    if(w_s <= 0 || h_s <= 0 ) return EXIT_FAILURE ;
    double mag[num];

    while(!feof(f)){
        if ((fscanf ( f , "%d %d %d" , &r , &g , &b ))==3){
            if (r<=255 && r>=0 && g>=0 && g<=255 && b<=255 && b>=0 ){
                mag[mag_counter] = (r + g + b )/3 ;
                total += mag[mag_counter];
                mag_counter++ ;
            }else{
            	return EXIT_FAILURE ;
            }
        }
    }

    if(num != mag_counter) return EXIT_FAILURE ;

    unsigned int bright = (total / num) ;
    printf("width: %u\n", ww);
    printf("height: %u\n", hh);
    printf("brightness: %u\n", bright) ;
    return EXIT_SUCCESS;
}


