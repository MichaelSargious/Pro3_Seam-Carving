#ifndef ALGORITHMUS_H
#define ALGORITHMUS_H


#include "image.h"
#include "carving.h"

#include <stdio.h>

struct pixel {
	int red , green , blue ;
};


int* lokale_energie (struct pixel* pixels ,int* total_lokal_e,int* o_l_e,int* l_l_e, int pixel_number ,int w , int h) ;

int* minimum_there (int* a , int* b , int* c) ;

int* minimum_two (int* a , int* b );

int* fuge_energie (int* fuge_e , int* total_lokal_e , int pixel_number ,int w , int h) ;

int* pfad_index (int* fuge_e , int* pfad_ind  , int pixel_number ,int w , int h);

#endif
