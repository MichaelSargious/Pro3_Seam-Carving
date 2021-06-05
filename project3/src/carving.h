#ifndef CARVING_H
#define CARVING_H

#include <stdio.h>
#include "algorithmus.h"
#include "image.h"


void image_write_to_file(FILE* f , struct pixel* new_bild ,int w , int h) ;

struct pixel* before_ind (struct pixel* new_bild , struct pixel* pixels , int* pfad_ind , int w , int h );

struct pixel* after_ind (struct pixel* new_bild , struct pixel* pixels , int* pfad_ind , int w , int h ) ;





#endif
