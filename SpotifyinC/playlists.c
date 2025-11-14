#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headerfile.h"
#include "extractsong.h"
#include "albums.h"
#include "playlist.h"

int songs_in_pl = 0;

// typedef struct song_list
// {   
//     int index;
//     int song_index;
//     struct song_list* next;
//     struct song_list* prev;
// }song_list;

song_list* add_playlist(song_list* head, int index, lib_node* library){
    song_list* temp = head;
    if (temp!= NULL) {
        if (temp->song_index == index) {
            printf("%sSong Id: %d is already there in playlist!%s\n", YELLOW, index, RESET);
            return head;
        }
        temp = temp->next;
        while (temp != head) {
            if (temp->song_index == index) {
                printf("%sSong Id: %d is already there in playlist!%s\n", YELLOW, index, RESET);
                return head;
            }   
            temp = temp->next;
        }
    }
    temp = head;

    song_list* newsong = malloc(sizeof(song_list));
    newsong->song_index = index;
    newsong->index = ++songs_in_pl;
    newsong->next = NULL;
    newsong->prev = NULL;

    if (head == NULL) {
        head = newsong;
        head->next = head;
        head->prev = head;
        printf("Added Song ");
        printf_onlysong(index, library);
        printf("to the playlist\n");
        FILE* logfile_pointer = fopen("log.txt", "a");
        fprintf(logfile_pointer,"7.1. Added Song %d to playlist\n", index);
        fclose(logfile_pointer);
        return head;
    }

    song_list* last = head->prev;

    newsong->next = head;
    newsong->prev = last;

    last->next = newsong;
    head->prev = newsong;
printf("Added Song ");
printf_onlysong(index, library);
printf("to the playlist\n");
FILE* logfile_pointer = fopen("log.txt", "a");
fprintf(logfile_pointer,"7.1. Added Song %d to playlist\n", index);
fclose(logfile_pointer);
return head;
}

song_list* add_album_playlist(song_list* head, char name[], lib_node* library){
    
    int* numbers = return_songs_album(name);
    if (numbers == NULL) {
        printf("%sError%s: Could not get songs from album \"%s\"\n", RED, name, RESET);
        return head;
    }

    for (int i = 1; i < numbers[0]+1; i++)
    {
        head = add_playlist(head, numbers[i], library);
    }
    printf("Added album \"%s\" to playlist\n", name);
    
    free(numbers);
    numbers = NULL;

return head;
}

song_list* del_playlist(song_list* head, int index, lib_node* library){
    song_list* temp = head;

    if (head == NULL) {
        printf("%sNo songs in PLaylist%s\n", YELLOW, RESET);
        return head;
    }
    if (head->next == head && head->song_index == index){
        free(head);
        songs_in_pl--;
        printf("Deleted Song Id: %d ", index);
        printf_onlysong(index, library);
        printf("from the playlist\n");
        FILE* logfile_pointer = fopen("log.txt", "a");
        fprintf(logfile_pointer,"7.2. Deleted Song %d from playlist\n", index);
        fclose(logfile_pointer);
        return NULL;
    }

    if (head->song_index == index){
        song_list* node_to_del = head;
        head->prev->next = head->next;
        head->next->prev = head->prev;
        head = head->next;
        free(node_to_del);
        songs_in_pl--;
        printf("Deleted Song Id: %d ", index);
        printf_onlysong(index, library);
        printf("from the playlist\n");        
        FILE* logfile_pointer = fopen("log.txt", "a");
        fprintf(logfile_pointer,"7.2. Deleted Song %d from playlist\n", index);
        fclose(logfile_pointer);
        return head; // Return the new head
    }

    temp = head->next;
    while(temp != head){
        if (temp->song_index == index){
            song_list* node_to_del = temp;
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            free(node_to_del);
            songs_in_pl--;
            printf("Deleted Song Id: %d ", index);
            printf_onlysong(index, library);
            printf("from the playlist\n");            
            FILE* logfile_pointer = fopen("log.txt", "a");
            fprintf(logfile_pointer,"7.2. Deleted Song %d from playlist\n", index);
            fclose(logfile_pointer);
            return head;
        }
        temp = temp->next;
    }
printf("%sSong Id: %d ", YELLOW, index);
printf_onlysong(index, library);
printf("not in playlist%s\n", RESET);
return head;
}

void showpl(song_list* head, lib_node* library) {
    if (head == NULL) {
        printf("No playlist\n");
        return;
    }
    printf("PLaylist Contains (%d) Songs: \n", songs_in_pl);
    song_list* temp = head;
    int x;
    x = temp->song_index;
    // printf("Id: %d\n", x);
    printf("--> ");
    printf_song(x, library);
    temp = temp->next;
    while (temp != head){
        x = temp->song_index;
        // printf("Id: %d\n", x);
        printf_song(x, library);   
        temp = temp->next;
    }
}

song_list* playnext(song_list* head, lib_node* library){
    if (head == NULL){
        printf("%sEmpty Playlist!%s\n", PINK, RESET);
        return head;
    }
    head = head->next;
    // printf("NOW PLAYING Id: %d\n", head->song_index);
    int x = head->song_index;
    printf("%sNOW PLAYING %s", WHITE, RESET);
    printf_onlysong(x, library);
    printf("\n");

return head;
}
song_list* playprev(song_list* head, lib_node* library){
    if (head == NULL){
        printf("%sEmpty Playlist!%s\n", PINK, RESET);
        return head;
    }
    head = head->prev;
    //printf("NOW PLAYING Id: %d\n", head->song_index);
    printf("%sNOW PLAYING %s", WHITE, RESET);
    printf_onlysong(head->song_index, library);
    printf("\n");
    // printf_song(head->song_index);

return head;
}

song_list* play(song_list* head, lib_node* library){
    if (head == NULL){
        printf("%sEmpty Playlist!%s\n", PINK, RESET);
        return head;
    }

    int x = head->song_index;
    printf("%sNOW PLAYING %s", WHITE, RESET);
    printf_onlysong(x, library);
    printf("\n");

return head;
}
void free_playlist(song_list* head) {
    if (head == NULL) {
        return;
    }

    song_list* temp = head;
    song_list* next_node;
    
    do {
        next_node = temp->next;
        free(temp);
        temp = next_node;
    } while (temp != head);
}

// int main() {
//     song_list* playlist = NULL;
//     playlist = add_playlist(playlist, 1);
//     playlist = add_playlist(playlist, 4);
//     playlist = add_playlist(playlist, 9);

//     showpl(playlist);

//     playlist = playnext(playlist);
//     playlist = playprev(playlist);
//     playlist = playprev(playlist);

//     free_playlist(playlist);
    
// return 0;
// }
