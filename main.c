#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h> 

#define MAX_ARG 3
#define DEBUG 0
#define ERROR 1

// Función para comprobar si un archivo existe
bool fileTrue(const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    bool existe = (archivo != NULL);  // Asignamos el resultado de la comprobación
    if (archivo) {
        fclose(archivo);  // Cerramos el archivo si fue abierto
    }
    return existe;
}

// Función para comprobar si los archivos de entrada y salida son diferentes
void fileNameDiff(const char *nombreArch1, const char *nombreArch2) {
    strcmp(nombreArch1, nombreArch2) == 0 
        ? (fprintf(stderr, "reverse: los archivos deben ser diferentes\n"), exit(ERROR))
        : (void)0;  // Si son diferentes, no hacer nada
}

// Función para validar que los archivos de entrada y salida no sean el mismo archivo
void validatorContDiff(const char *nombreArch1, const char *nombreArch2) {
    FILE *in = fopen(nombreArch1, "r");
    FILE *out = fopen(nombreArch2, "r");

    // Verificar que los archivos se abrieron correctamente
    if (!in || !out) {
        fprintf(stderr, "reverse: No se puede abrir el archivo\n");
        exit(ERROR);
    }

    struct stat sb1, sb2;

    // Verificar el estado de los archivos
    fstat(fileno(in), &sb1);
    fstat(fileno(out), &sb2);

    fclose(in);
    fclose(out);

    // Comparar los inodos de los archivos para verificar si son el mismo archivo
    if (sb1.st_ino == sb2.st_ino) {
        fprintf(stderr, "reverse: Los archivos deben ser diferentes\n");
        exit(ERROR);
    }
}

