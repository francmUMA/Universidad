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
        printf("No hay suficiente espacio en memoria");
        exit(-1);
    }
    ptr_aux = list -> head_;
    if (ptr_aux == NULL){
        usuario -> nextUser_ = list -> head_;
        list -> head_ = usuario;
        list -> numberOfUsers_++;
        return 1;
    } else {
        int isUserName = 0;
        int isUid = 0;
        while (ptr_aux -> nextUser_ != NULL && !isUserName && !isUserName){
            isUserName = strcmp(ptr_aux -> userName_, usuario -> userName_);
            if (isUserName < 0 || isUserName > 0) {
                isUserName = 1;
            } 
            isUid = ptr_aux -> uid_ == usuario -> uid_;
            ptr_aux = ptr_aux -> nextUser_;
        }
        if (isUserName || isUid){
            printf("No se ha podido añadir el usuario. \n");
            return 0;
        } else {
            usuario -> nextUser_ = list -> head_;
            list -> head_ -> previousUser_ = usuario;
            list -> head_ = usuario;
            list -> numberOfUsers_++;
            return 1;
        }
    }
    
}

int getUid(T_userList list, char *userName){
    ;
}

int deleteUser(T_userList *list, char *userName){
    ;
}

void printUserList(T_userList list, int reverse){
    if (reverse){
        ;
    } else {
        T_user *ptr_aux = malloc(sizeof(struct user));
        if (&ptr_aux == NULL){
            printf("No hay suficiente espacio en memoria");
            exit(-1);
        }
        ptr_aux = (&list) -> head_;
        while (ptr_aux != NULL){
            printf ("Nombre: %s UID: %i Home Directory: %s \n", ptr_aux -> userName_, ptr_aux -> uid_, ptr_aux -> homeDirectory_);
            ptr_aux = ptr_aux -> nextUser_;
        }
    }
}
