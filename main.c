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

int validarArchivosInvertidos(const char *nombreArch1,const char *nombreArch2){
    
    FILE *in = fopen(nombreArch1,"r");; 
    FILE *out = fopen(nombreArch2,"w");

  	//Arreglo de punteros a caracteres
  	char **lines = NULL;

  	//Contador para el numero de lineas
  	int lineCount = 0;

  	// puntero 'line' para almacenar dinámicamente cada línea leída
	// 'len' para rastrear la longitud de la línea actual.
  	char *line = NULL;
  	size_t len = 0;

  	while (getline(&line, &len, in ) != -1){

  		lineCount++;
		
		// Redimensionar dinámicamente el arreglo 'lines' para acomodar la nueva línea.
		lines = realloc(lines, lineCount * sizeof(char *));

		// Verificar si la asignación de memoria fue exitosa.
		if (lines == NULL) {
        fprintf(stderr, "reverse: error allocating memory\n");
        exit(ERROR);
    	}

    	// Duplicar la línea recién leída y almacenar su dirección en el arreglo 'lines'.
		lines[lineCount - 1] = strdup(line);

		// Verificar si la duplicación de la línea fue exitosa.
		if (lines[lineCount - 1] == NULL) {
        fprintf(stderr, "reverse: error duplicating line\n");
        exit(ERROR);
    	}
  	}

  	free(line);

  	//imprimir arreglo desde su ultima posicion a la inicial
  	for (int i = lineCount - 1; i >= 0; i--) {
  		fprintf(out,"%s",lines[i]);
  		free(lines[i]);
  	}
    
  	free(lines);

  	//Cerrar archivos
  	fclose(in);
  	fclose(out);

    return 0;
}
