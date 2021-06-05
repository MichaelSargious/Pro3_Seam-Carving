#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "algorithmus.h"

int* lokale_energie (struct pixel* pixels ,int* total_lokal_e,int* o_l_e,int* l_l_e, int pixel_number ,int w , int h){
    int x = w-1 ;
    int y = h-1 ;
    int b ;
    int a ;

    a = 1 ;
    b = 0 ;
    for( int c = 1 ; c < pixel_number ; c++ ){
        if( a > 0 && a <= x && b >= 0 && b <= y ){
            l_l_e[c] = ((pixels[(b*w)+a].red - pixels[(b*w)+(a-1)].red)*(pixels[(b*w)+a].red - pixels[(b*w)+(a-1)].red))+
                       ((pixels[(b*w)+a].green - pixels[(b*w)+(a-1)].green)*(pixels[(b*w)+a].green - pixels[(b*w)+(a-1)].green))+
                       ((pixels[(b*w)+a].blue - pixels[(b*w)+(a-1)].blue)*(pixels[(b*w)+a].blue - pixels[(b*w)+(a-1)].blue)) ;
            a++ ;
        }else{
            a = 1 ;
            b++ ;
        }
    }

    a = 0 ;
    b = 1 ;
    for(int d = w ; d < pixel_number ; d++){
        if( a >= 0 && a <= x && b > 0 && b <= y ){
            o_l_e[d] = ((pixels[(b*w)+a].red - pixels[((b-1)*w)+a].red)*(pixels[(b*w)+a].red - pixels[((b-1)*w)+a].red))+
                       ((pixels[(b*w)+a].green - pixels[((b-1)*w)+a].green)*(pixels[(b*w)+a].green - pixels[((b-1)*w)+a].green))+
                       ((pixels[(b*w)+a].blue - pixels[((b-1)*w)+a].blue)*(pixels[(b*w)+a].blue - pixels[((b-1)*w)+a].blue)) ;
            a++ ;
        }else{
            a = 0 ;
            b++ ;
            if(a >= 0 && a <= x && b > 0 && b <= y){
                o_l_e[d] = ((pixels[(b*w)+a].red - pixels[((b-1)*w)+a].red)*(pixels[(b*w)+a].red - pixels[((b-1)*w)+a].red))+
                           ((pixels[(b*w)+a].green - pixels[((b-1)*w)+a].green)*(pixels[(b*w)+a].green - pixels[((b-1)*w)+a].green))+
                           ((pixels[(b*w)+a].blue - pixels[((b-1)*w)+a].blue)*(pixels[(b*w)+a].blue - pixels[((b-1)*w)+a].blue)) ;
                a++ ;
            }
        }
    }



    for(int e = 0 ; e < pixel_number ; e++){
        total_lokal_e[e] = o_l_e[e] + l_l_e[e] ;
    }

    return total_lokal_e ;

}

int* minimum_there (int* a , int* b , int* c){
    int x = *a ;
    int y = *b ;
    int z = *c ;
    int* m ;

    if (y <= x){
        if (y <= z){
            m = &y ;
        }else{
            m = &z ;
        }
    }else{
        if (x <= z){
            m = &x ;
        }else{
            m = &z ;
        }
    }

    return m ;
}

int* minimum_two (int* a , int* b ){
    int x = *a ;
    int y = *b ;
    int* m ;

    if (x < y ) m = &x ;
    else  m = &y ;

    return m ;
}



int* fuge_energie (int* fuge_e , int* total_lokal_e , int pixel_number ,int w , int h){
    int x = w-1 ;
    int y = h-1 ;
    int b ;
    int a ;
    int* min ;

    for (int j = 0; j < w; ++j) {
        fuge_e[j] = total_lokal_e[j] ;
    }

    a = 0 ;
    b = 1 ;
    for(int i = w ; i < pixel_number ; i++){
        switch(a){
            case 0 :
                if ( b>0 && b <= y ){
                    min = minimum_two ( &fuge_e[((b-1)*w)+a] , &fuge_e[((b-1)*w)+(a+1)] ) ;
                    fuge_e[(b*w)+a] = total_lokal_e[(b*w)+a] + *min ;
                    a++ ;
                }

            default :
                if( a>0 && a<x && b>0 && b<=y ){
                    min = minimum_there (&fuge_e[((b-1)*w)+(a-1)] , &fuge_e[((b-1)*w)+a] , &fuge_e[((b-1)*w)+(a+1)] ) ;
                    fuge_e[(b*w)+a] = total_lokal_e[(b*w)+a] + *min  ;
                    a++ ;
                }else{
                    if( a==x && b > 0 && b <= y ){
                        min = minimum_two ( &fuge_e[((b-1)*w)+a] , &fuge_e[((b-1)*w)+(a-1)] ) ;
                        fuge_e[(b*w)+a] = total_lokal_e[(b*w)+a] + *min  ;
                        a++ ;
                    }else{
                        a = 0 ;
      +                  b++ ;
                        if( a == 0  && b > 0 && b <= y ){
                            min = minimum_two ( &fuge_e[((b-1)*w)+a] , &fuge_e[((b-1)*w)+(a+1)] ) ;
                            fuge_e[(b*w)+a] = total_lokal_e[(b*w)+a] + *min  ;
                            a++ ;
                        }
                    }
                }
        }
    }

    return fuge_e ;

}

int* pfad_index (int* fuge_e , int* pfad_ind , int pixel_number , int w ,int h ){
    int x = w-1 ;
    int y = h-1 ;
    int min = 0;
    int start_ind = 0;
    int x_s = 0 ;


    min = fuge_e[pixel_number - w] ;
    start_ind = pixel_number - w ;
    for (int i = start_ind ; i < pixel_number ; i++){
        if(fuge_e[i] < min) {
            min = fuge_e[i];
            start_ind = i;
        }
    }
    x_s = start_ind ;
    while(x_s >= w){
        x_s -= w ;
    }
    pfad_ind[y] = x_s ;

    int b = y ;
    while(start_ind >= w){
        switch(x_s){
            case 0 :
                if (b > 0 && b <= y ){
                    if (fuge_e[start_ind - w] <= fuge_e[start_ind - w + 1]){
                        start_ind = start_ind - w ;
                        x_s = start_ind ;
                        while (x_s >= w ){
                            x_s -= w ;
                        }
                        pfad_ind[b-1] = x_s ;
                    }else{
                        start_ind = start_ind - w +1;
                        x_s = start_ind ;
                        while (x_s >= w ){
                            x_s -= w ;
                        }
                        pfad_ind[b-1] = x_s ;
                    }
                    b-- ;
                }
            default:
                if (x_s > 0 && x_s < x && b > 0 && b <= y){
                    if(fuge_e[start_ind - w] <= fuge_e[start_ind - w - 1] ){
                        if ( fuge_e[start_ind - w] <= fuge_e[start_ind - w + 1]) {
                            start_ind = start_ind - w ;
                            x_s = start_ind ;
                            while (x_s >= w ){
                                x_s -= w ;
                            }
                            pfad_ind[b-1] = x_s ;
                        }else{
                            start_ind = start_ind - w + 1 ;
                            x_s = start_ind ;
                            while (x_s >= w ){
                                x_s -= w ;
                            }
                            pfad_ind[b-1] = x_s ;
                        }
                    }else{
                        if (fuge_e[start_ind - w - 1] <= fuge_e[start_ind - w + 1] ){
                            start_ind = start_ind - w - 1 ;
                            x_s = start_ind ;
                            while (x_s >= w ){
                                x_s -= w ;
                            }
                            pfad_ind[b-1] = x_s ;
                        }else{
                            start_ind = start_ind - w + 1 ;
                            x_s = start_ind ;
                            while (x_s >= w ){
                                x_s -= w ;
                            }
                            pfad_ind[b-1] = x_s ;
                        }
                    }
                    b-- ;
                } else{
                    if( x_s == x && b > 0 && b <= y ){
                        if (fuge_e[start_ind - w] <= fuge_e[start_ind - w - 1]){
                            start_ind = start_ind - w ;
                            x_s = start_ind ;
                            while (x_s >= w ){
                                x_s -= w ;
                            }
                            pfad_ind[b-1] = x_s ;
                        }else{
                            start_ind = start_ind - w - 1;
                            x_s = start_ind ;
                            while (x_s >= w ){
                                x_s -= w ;
                            }
                            pfad_ind[b-1] = x_s ;
                        }
                        b-- ;
                    }
                }
        }
    }
return pfad_ind ;
}




