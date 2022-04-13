#include "userList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

T_user *createUser(char *name, int uid, char *dir){
    T_user *newUser = malloc (sizeof(struct user));
    if (&newUser == NULL){
        printf("No hay suficiente espacio en memoria");
        exit(-1);
    }
    newUser -> uid_ = uid;
    newUser -> userName_ = malloc (sizeof(strlen(name)));
    newUser -> homeDirectory_ = malloc (sizeof(strlen(dir)));
    strcpy(newUser -> userName_, name);
    strcpy(newUser -> homeDirectory_, dir);
    newUser -> previousUser_ = NULL;
    newUser -> nextUser_ = NULL;
    return newUser;
}

T_userList createUserList(){
    T_userList *newList = malloc(sizeof(struct userList));
    if (&newList == NULL){
        printf("No hay suficiente espacio en memoria");
        exit(-1);
    }
    newList -> head_ = NULL;
    newList -> tail_ = NULL;
    newList -> numberOfUsers_ = 0;
    return *newList;
}
 
int addUser(T_userList *list, T_user *usuario){
    T_user *ptr_aux = malloc(sizeof(struct user));
    if (&ptr_aux == NULL){
        printf("No hay memoria suficiente");
        exit(-1);
    }
    ptr_aux = list -> head_;
    if (ptr_aux == NULL){
        //Solo hay un elemento
        list -> head_ = usuario;
        list -> numberOfUsers_++;
        return 0;
    } else {
        /* Hay más de un elemento, por lo que hay que comprobar que el elemento que se va a 
        añadir no esté en la lista */
        int isUid = 0;
        int isUserName = 0;
        while (ptr_aux -> nextUser_ != NULL && !isUid && !isUserName){
            if (ptr_aux -> uid_ == usuario -> uid_){
                isUid = 1;
            }
            if (strcmp(usuario -> userName_, ptr_aux -> userName_) == 0){
                isUserName = 1;
            }
            ptr_aux = ptr_aux -> nextUser_; 
        }
        if (isUid || isUserName){
            printf("No se ha podido añadir al usuario %s \n", usuario -> userName_);
            return 0;
        } else {
            list -> head_ -> previousUser_ = usuario;
            list -> tail_ = list -> head_;
            usuario -> nextUser_ = list -> tail_;
            list -> head_ = usuario;
            list -> numberOfUsers_++;
            return 1;
        }
    }
}

int getUid(T_userList list, char *userName){
    T_user *ptr_aux = malloc(sizeof(struct user));
    if (&ptr_aux == NULL){
        printf("No hay memoria suficiente");
        exit(-1);
    }
    ptr_aux = (&list) -> head_;
    while(ptr_aux != NULL){
        if (strcmp(ptr_aux -> userName_, userName) == 0){
            return ptr_aux -> uid_;
        }
        ptr_aux = ptr_aux -> nextUser_;
    }
    return -1;
}

int deleteUser(T_userList *list, char *userName){
    T_user *ptr_aux = malloc(sizeof(struct user));
    if (&ptr_aux == NULL){
        printf("No hay memoria suficiente");
        exit(-1);
    }
    ptr_aux = list -> head_;
    while(ptr_aux != NULL){
        if (strcmp(ptr_aux -> userName_, userName) == 0){
            //Hay que modificar head
            if (ptr_aux == list -> head_){
                list -> head_ = list -> tail_;
                if (list -> tail_ != NULL){
                    list -> tail_ = list -> tail_ -> nextUser_;
                    list -> head_ -> previousUser_ = NULL;
                }
            } else {
                ptr_aux -> previousUser_ = ptr_aux -> nextUser_;
            }
            free(ptr_aux);
            return 0;
        }
        ptr_aux = ptr_aux -> nextUser_;
    }
    return -1;
}

void printUserList(T_userList list, int reverse){
    T_user *ptr_aux = malloc(sizeof(struct user));
    if (&ptr_aux == NULL){
        printf("No hay suficiente espacio en memoria");
        exit(-1);
    }
    ptr_aux = (&list) -> head_;
    if (reverse){
        while (ptr_aux != NULL && ptr_aux -> nextUser_ != NULL){
            ptr_aux = ptr_aux -> nextUser_;
        }
        while (ptr_aux != NULL){
            printf ("Nombre: %s UID: %i Home Directory: %s \n", ptr_aux -> userName_, ptr_aux -> uid_, ptr_aux -> homeDirectory_);
            ptr_aux = ptr_aux -> previousUser_;
        }
    } else {
        while (ptr_aux != NULL){
            printf ("Nombre: %s UID: %i Home Directory: %s \n", ptr_aux -> userName_, ptr_aux -> uid_, ptr_aux -> homeDirectory_);
            ptr_aux = ptr_aux -> nextUser_;
        }
    }
}
