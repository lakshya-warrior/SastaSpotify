#ifndef Albums
#define Albums

#include "headerfile.h"

extern int numberofalbums; 
void genalbumcnt();
int gen_album(char name[]);//
void albumname(int idx_to_find);
void albumadd(int index, int albumidx, lib_node* library);//
void albumdel(int index, int albumidx, lib_node* library);//
void list_songs_album(int albumidx, lib_node* library);//
void list_albums();//
song_list* return_songs_album(int albumidx, lib_node* library, song_list* head);

#endif
