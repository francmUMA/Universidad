/*
 * FUSE: Filesystem in Userspace
 * DSO 2014
 * Ejemplo para montar un libro de poesía como sistema de ficheros
 * Cada capítulo del libro será un fichero diferente
 * 
 * Compilarlo con make
 *  
 * uso:  basicFUSE [opciones FUSE] fichero_inicial punto_de_montaje
 * 
 *  ./basicFUSE proverbiosycatares.txt punto_montaje
 * 
*/
#include <asm-generic/errno-base.h>
#define FUSE_USE_VERSION 26

#include "basicFUSE_lib.h"

#include <stdlib.h>
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

char *strdup(const char *str) {
    int n = strlen(str) + 1;
    char *dup = malloc(n);
    if(dup)
    {
        strcpy(dup, str);
    }
    return dup;
}


/*
 *  Para usar los datos pasados a FUSE usar en las funciones:
 * 
	struct structura_mis_datos *mis_datos= (struct structura_mis_datos *) fuse_get_context()->private_data;
 * 
 * */

/***********************************
 * */
static int mi_getattr(const char *path, struct stat *stbuf)
{
    struct structura_mis_datos *data = (struct structura_mis_datos *) fuse_get_context() -> private_data;
    int res = 0;
    int chapter = 0;
    memset(stbuf, 0, sizeof(struct stat));
    if (strcmp(path, "/") == 0){
        stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 2;
		stbuf->st_uid = data->st_uid;
		stbuf->st_gid = data->st_gid;
		
		stbuf->st_atime = data->st_atim;
		stbuf->st_mtime = data->st_mtim;
		stbuf->st_ctime = data->st_ctim;
		stbuf->st_size = 1024;
		stbuf->st_blocks = 2;
    } else if ((chapter = buscar_fichero(path, data)) >= 0){
        stbuf->st_mode = S_IFREG | 0444;
		stbuf->st_nlink = 1;
		
		stbuf->st_uid = data->st_uid;
		stbuf->st_gid = data->st_gid;
		
		stbuf->st_atime = data->st_atim;
		stbuf->st_mtime = data->st_mtim;
		stbuf->st_ctime = data->st_ctim;
		
		stbuf->st_size = strlen(data->contenido_ficheros[i]);
		stbuf->st_blocks = stbuf->st_size/512 + (stbuf->st_size%512)? 1 : 0; 
    } else {
        res = -ENOENT;
    }
    return res;
}

/***********************************
 * */

static int mi_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
			 off_t offset, struct fuse_file_info *fi)
{ 
    /* completar */
    struct structura_mis_datos *mis_datos= (struct structura_mis_datos *) fuse_get_context()->private_data;
		
	/* completar */
	int i;
	
	(void) offset;
	(void) fi;

	if (strcmp(path, "/") != 0)
		return -ENOENT;

	if(filler(buf, "." , NULL, 0)!=0) return -ENOMEM;
	if(filler(buf, "..", NULL, 0)!=0) return -ENOMEM;
	
	
	for (i=0; i< mis_datos->numero_ficheros; i++)
	{
		if (filler(buf,mis_datos->nombre_ficheros[i], NULL, 0) != 0)
            return -ENOMEM;
	}
	
	return 0;

}

/***********************************
 * */
static int mi_open(const char *path, struct fuse_file_info *fi)
{
	/* completar */
    
    struct structura_mis_datos *mis_datos= (struct structura_mis_datos *) fuse_get_context()->private_data;
    int res = 0;
    for (int i = 0; (i < mis_datos -> numero_ficheros) && (!res); i++){
        if (strcmp(path + 1, mis_datos -> nombre_ficheros) == 0){
           res = 1; 
        }     
    }
    if (!res) return -ENOENT;
    else if ((fi->flags & O_ACCMODE) != O_RDONLY) return -EACCES;

    return 0;
}


/***********************************
 * */
static int mi_read(const char *path, char *buf, size_t size, off_t offset,
		      struct fuse_file_info *fi)
{
	/* completar */
}


/***********************************
 * operaciones FUSE
 * */
static struct fuse_operations basic_oper = {
	.getattr	= mi_getattr,
	.readdir	= mi_readdir,
	.open		= mi_open,
	.read		= mi_read,
};


/***********************************
 * */
int main(int argc, char *argv[])
{
	struct structura_mis_datos *mis_datos;
	
	mis_datos=malloc(sizeof(struct structura_mis_datos));
	
	// análisis parámetros de entrada
	if ((argc < 3) || (argv[argc-2][0] == '-') || (argv[argc-1][0] == '-')) error_parametros();

	mis_datos->fichero_inicial = strdup(argv[argc-2]); // fichero donde están los capítulos
    argv[argc-2] = argv[argc-1];
    argv[argc-1] = NULL;
    argc--;
    
    leer_fichero(mis_datos);
    
/*    int i;
    for(i=0; i<mis_datos->numero_ficheros; i++)
    {
		printf("----->  %s\n", mis_datos->nombre_ficheros[i]);
		printf("%s",mis_datos->contenido_ficheros[i]);
	}
	exit(0);
*/
	
	return fuse_main(argc, argv, &basic_oper, mis_datos);
}
