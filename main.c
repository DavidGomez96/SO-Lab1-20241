#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h> 

#define MAX_ARG 3
#define DEBUG 0
#define ERROR 1

bool archivoExiste(const char *nombreArchivo) {

    FILE *archivo = fopen(nombreArchivo, "r");

    if (archivo != NULL) {
        fclose(archivo);
        return true;
    } else {
        return false;
    }
}

void archivosNombreDiffArchivos(const char *nombreArch1,const char *nombreArch2){

    if ( strcmp(nombreArch1,nombreArch2)==0){
        fprintf(stderr,"reverse: input and output file must differ\n");
        exit(ERROR);
    }

}

void validarContenidoDiffArchivo(const char *nombreArch1,const char *nombreArch2){
    
    FILE *in = fopen(nombreArch1,"r");
    FILE *out = fopen(nombreArch2,"r");

    struct stat sb1, sb2;

    fstat(fileno(in), &sb1);
    fstat(fileno(out), &sb2);

    if (sb1.st_ino == sb2.st_ino){
        fprintf(stderr,"reverse: input and output file must differ\n");
        exit(ERROR);
    }

} 
