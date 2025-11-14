#ifndef PLAYLIST
#define PLAYLIST

#include "headerfile.h"

song_list* add_playlist(song_list* head, int index, lib_node* library);//
song_list* del_playlist(song_list* head, int index, lib_node* library);
void showpl(song_list* head, lib_node* library);//
song_list* playnext(song_list* head, lib_node* library);
song_list* playprev(song_list* head, lib_node* library);
song_list* add_album_playlist(song_list* head, char name[], lib_node* library);//
song_list* play(song_list* head, lib_node* library);
void free_playlist(song_list* head);//

#endif