#ifndef Albums
#define Albums

#include "headerfile.h"

int gen_album(char name[]);//
void albumadd(int index, const char *name, lib_node* library);//
void albumdel(int index, const char *name, lib_node* library);//
void list_songs_album(char name[], lib_node* library);//
void list_albums();//
int* return_songs_album(char name[]);//

#endif