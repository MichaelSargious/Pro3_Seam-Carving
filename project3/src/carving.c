#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "carving.h"

void image_write_to_file(FILE* f , struct pixel* new_bild , int w , int h){
    fprintf(f,"P3\n");
    fprintf(f,"%d %d\n", w , h);
    int y = 255 ;
    fprintf(f, "%d\n", y );
    int i = 0;
    for (int p = 0 ; p < h ; p++){
        for (int q = 0 ; q < w ; q++){
            fprintf ( f , "%d %d %d " , new_bild[i].red , new_bild[i].green , new_bild[i].blue ) ;
            i++;
        }
        fprintf(f,"\n");
    }
}

struct pixel* before_ind (struct pixel* new_bild , struct pixel* pixels , int* pfad_ind , int w , int h ) {
    for (int b = 0; b < h; b++){
        for (int a = 0; a < pfad_ind[b]; a++) {
            new_bild[(b * w) + a].red = pixels[(b * w) + a].red;
            new_bild[(b * w) + a].green = pixels[(b * w) + a].green;
            new_bild[(b * w) + a].blue = pixels[(b * w) + a].blue;
        }
    }

    return new_bild ;
}

struct pixel* after_ind (struct pixel* new_bild , struct pixel* pixels , int* pfad_ind , int w , int h ){
    for(int b = 0 ; b < h ; b++){
        for(int a = pfad_ind [b] ; a < (w-1) ; a++){
                new_bild[(b*w)+a].red = pixels[(b*w)+(a+1)].red ;
                new_bild[(b*w)+a].green = pixels[(b*w)+(a+1)].green ;
                new_bild[(b*w)+a].blue = pixels[(b*w)+(a+1)].blue ;
        }
    }
    return new_bild ;
}
