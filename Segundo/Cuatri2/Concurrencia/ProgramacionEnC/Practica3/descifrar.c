#include <stdio.h>

void decrypt(unsigned * v, unsigned * k){
    const unsigned delta = 0x9e3779b9;
    unsigned sum = 0xC6EF3720;
    for (int i = 0; i < 32; i++){
        v[1] -= (((v[0] << 4) + k[2]) ^ (v[0] + sum) ^ ((v[0] >> 5) + k[3]));
        v[0] -= (((v[1] << 4) + k[0]) ^ (v[1] + sum) ^ ((v[1] >> 5) + k[1]));
        sum = sum - delta; 
    }
}
int main(int argc, char const *argv[])
{
    unsigned k[4]={128, 129, 130, 131}; 
    FILE *ptr_entrada;
    FILE *ptr_salida;
    if(argc!=3){
        printf("Se esperaban 2 argumentos, el fichero de entrada y el de salida");
        exit(-1);
    }
    ptr_entrada = fopen(argv[1],"rb");
    if (ptr_entrada == NULL){
        perror("No se puede leer el fichero de entrada");
        exit(-1);
    }
    ptr_salida = fopen(argv[2],"wb");
    if (ptr_salida == NULL){
        perror("No se puede leer el fichero de salida");
        exit(-1);
    }
    unsigned tam_fichero, tam_fichero_adaptado;
    int leidos = fread(&tam_fichero, sizeof(unsigned), 1, ptr_entrada);
    if(leidos == 1){
        tam_fichero_adaptado = tam_fichero;
        if (tam_fichero % 8 != 0) tam_fichero_adaptado += 8 - tam_fichero % 8;
        unsigned *ptr_aux = malloc(tam_fichero_adaptado);
        if (ptr_aux == NULL){
            perror("No hay suficiente espacio");
            exit(-1);
        }
        fread(ptr_aux, tam_fichero, 1, ptr_entrada);
        for (size_t i = 0; i < tam_fichero_adaptado / sizeof(unsigned); i+=2){
            decrypt(&ptr_aux[i],k);
        }
        fwrite(ptr_aux, 1, tam_fichero_adaptado, ptr_salida);
        free(ptr_aux);
        fclose(ptr_entrada);
        fclose(ptr_salida);
    } else {
        perror("el formato del fichero no es correcto");
        exit(-1);
    }
    return 0;
}
