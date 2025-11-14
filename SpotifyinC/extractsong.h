#ifndef extractsongs
#define extractsongs

#include "headerfile.h"

lib_node* gensong(lib_node* head);
void print_songs(lib_node* head);
void printf_song(int idx, lib_node* head);
void printf_onlysong(int idx, lib_node* head);
void free_library(lib_node* head);
int checksong(int song_idx, lib_node* head);

#endif