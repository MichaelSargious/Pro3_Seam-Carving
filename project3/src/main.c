#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "image.h"
#include "algorithmus.h"
#include "carving.h"


int main(int const argc, char** const argv){

	int n ;
	int sflag = 0 ;
	int pflag = 0 ;
	int nflag = 0 ;
	int option;

	while((option = getopt(argc, argv, "spn:")) != -1) {
		switch(option) {
		case 's':
			sflag++;
			break ;
		case 'p':
			pflag++;
			break ;
		case 'n' :
			nflag++;
		    n = atoi(optarg) ;
			break ;
		default:
			printf( "Usage: %s Error \n", argv[0]);
			return EXIT_FAILURE ;
		}
	}

	if(optind != (argc -1)){
		printf( "cannot open the foto \"%s\"\n", argv[optind]);
		return EXIT_FAILURE ;
	}
	FILE* f = fopen( argv[optind] ,"r");
	    if (f == NULL) {
	        printf( "cannot open the foto \n");
	        return EXIT_FAILURE ;
	    }

	    int w , h ;
	    if((fscanf(f , "P3\n%d %d\n255\n" , &w , &h)) !=2 ) return EXIT_FAILURE ;
	    if(w <= 0 || h <= 0 ) return EXIT_FAILURE ;
	    int num = w*h ;
	    struct pixel* pixels = calloc (num , sizeof(  *pixels ));
	    int q = 0 ;
	    while(!feof(f)) {
	        if(pixel_read_from_file ( f , &pixels[q] ) == 1)
	        q++ ;
	    }
	    rewind(f) ;

	    int* o_l_e =  calloc (num , sizeof(int)) ;
	    int* l_l_e =  calloc (num , sizeof(int)) ;
	    int* total_lokal_e = calloc (num , sizeof(int)) ;
	    int* fuge_e = calloc (num , sizeof(int)) ;
	    int* pfad_ind = calloc ( h , sizeof(int)) ;
	    struct pixel* new_bild = calloc (num , sizeof( *new_bild )) ;

	    if(sflag == 1) {
	        statistiken ( f , num , w , h  ) ;
	        rewind(f) ;

	    }

	    if(pflag == 1) {
	    	 int* after_t_l_e = lokale_energie ( pixels , total_lokal_e , o_l_e , l_l_e , num , w , h) ;
	    	 int* after_f_e = fuge_energie (fuge_e , after_t_l_e , num , w ,  h) ;
	    	 pfad_index ( after_f_e , pfad_ind , num ,  w , h );
	    	 for (int i = h-1 ; i >= 0 ; i--) {
	    		 printf("%d\n" , pfad_ind[i]) ;
	    	 }
	    }

	    if(nflag==1){


	    	if(n > w) {
	    	            return EXIT_FAILURE;

	    	}else if (n == 0) {
	    		FILE *fp = fopen("out.ppm", "w");
	    		if (f == NULL) {
	    			        printf( "cannot open the foto \n");
	    			        return EXIT_FAILURE ;
	    			    }
	    		image_write_to_file(fp, pixels, w, h);
	    		rewind (fp) ;

	    	}else if (n > 0) {

	    		struct pixel *new = pixels;
	    		    int j = 1;
	    		    while (j <= n) {
	    		    int *after_t_l_e = lokale_energie(new, total_lokal_e, o_l_e, l_l_e, num, w, h);
	    		    int *after_f_e = fuge_energie(fuge_e, after_t_l_e, num, w, h);
	    		    int *path = pfad_index(after_f_e, pfad_ind, num, w, h);
	    		    before_ind(new_bild, new, path, w, h);
	    		    after_ind(new_bild, new, pfad_ind, w, h);
	    		    new = new_bild;
	    		      j++ ;
	    		    }
	    	    FILE *fp = fopen("out.ppm", "w");
	    	    if (f == NULL) {
	    	    	        printf( "cannot open the foto \n");
	    	    	        return EXIT_FAILURE ;
	    	    	    }
	    	    image_write_to_file(fp, new_bild , w, h);

	    	}else {

	    		FILE *fp = fopen("out.ppm", "w");
	    		if (f == NULL) {
	    			        printf( "cannot open the foto \n");
	    			        return EXIT_FAILURE ;
	    			    }
	    		image_write_to_file( fp , new_bild , w, h);
	    	        }
}
	    free(pixels);
	    free(o_l_e);
	    free(l_l_e);
	    free(total_lokal_e);
	    free(fuge_e);
	    free(pfad_ind) ;
	    free(new_bild) ;
	    fclose(f) ;

	    return EXIT_SUCCESS;
}









