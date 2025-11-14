// Code to extract data from a song.txt file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headerfile.h"
#include "extractsong.h"
#include "albums.h"
#include "playlist.h"
// For faster Reading of songs i will store in linked list

lib_node* gensong(lib_node* head){
    lib_node* temp = head;
    char line[301];
    FILE* songsfilepointer;
    songsfilepointer = fopen("songs.txt", "r");

    if (songsfilepointer == NULL) {
        printf("%sERROR:%s Could not open %ssongs.txt\n", RED, YELLOW, RESET);
        exit(1);
    }

    while (fgets(line, 301, songsfilepointer)) {
        lib_node* newnode = (lib_node*)malloc(sizeof(lib_node));
        sscanf(line, "%d$%99[^$]$%99[^$]$%d", &newnode->index, newnode->songname, newnode->singer, &newnode->time);
        newnode->next = NULL;
        if (temp == NULL) {
            head = newnode;
            temp = head;
        }
        else {
            temp->next = newnode;
            temp = temp->next;
        }
    }
    fclose(songsfilepointer);
    // LOOPING
    temp->next = head;
    return head;
    
    
    // if (head == NULL) {
    //     printf("Empty.\n");
    //     return;
    // }
    // song_list* temp = head;

    // do {
    //     printf("Id: %d Name: %s\n",temp->index, temp->ptr_to_song->songname);
    //     //printf("Id: %d Name: %s Singer: %s Duration: %d sec\n",temp->index, temp->ptr_to_song->songname, temp->ptr_to_song->atristname, temp->ptr_to_song->time);
    //     temp = temp->next;
    // } while(temp!=head);
}

void print_songs(lib_node* head){
    
    if (head == NULL) {
        printf("Empty.\n");
        return;
    }
    lib_node* temp = head;

    do {
        printf("Id: %d Song Name: \"%s\" by %s of time: %d sec\n",temp->index, temp->songname, temp->singer, temp->time);
        temp = temp->next;
    } while(temp!=head);
    // FILE * songsfilepointer;
    // songsfilepointer = fopen("songs.txt", "r");

    // char line[301];
    // while (fgets(line, 301, songsfilepointer)) {
    //     printf("Id: %s", line);
    // }

    // printf("\n");
    // fclose(songsfilepointer);
}

void printf_song(int idx, lib_node* head){
    if (head == NULL) {
        printf("Empty.\n");
        return;
    }
    lib_node* temp = head;

    do {
        if (idx == temp->index) {printf("Id: %d Song Name: \"%s\" by Singer: %s of Duration: %d sec\n",temp->index, temp->songname, temp->singer, temp->time); return;}
        temp = temp->next;
    } while(temp!=head);

    printf("%sSong with Id: %d is not there in library!\n%s", YELLOW, idx, RESET);

    // Converting int to string 
//     int temp = idx, len=0;
//     while(temp!=0){
//         len++;
//         temp/=(10);
//     }
//     char string[len+1];
//     temp = idx;
//     int i = len-1;
//     while(temp!=0){
//         string[i--] = '0'+ (temp%10);
//         temp/=10;
//     }
//     char line[301];
//     string[len] = ' ';
//     FILE * songsfilepointer;
//     songsfilepointer = fopen("songs.txt", "r");
//     while (fgets(line, 301, songsfilepointer)) {
//         // printf("%s", line);
//         // printf(">>%d\n", strncmp(line, string, strlen(string)));
//         if (strncmp(line, string, len+1) == 0) {
//             printf("Id: %s", line);
//             fclose(songsfilepointer);
//             return;
//         }
//     }
// fclose(songsfilepointer);
}

int checksong(int idx, lib_node* head){
    if (head == NULL) {
        printf("Empty.\n");
        return 0;
    }
    lib_node* temp = head;

    do {
        if (idx == temp->index) return 1;
        temp = temp->next;
    } while(temp!=head);

    printf("%sSong with Id: %d is not there in library!%s\n", YELLOW, idx, RESET);
    return 0;
}


void printf_onlysong(int idx, lib_node* head){
    
    if (head == NULL) {
        printf("Empty.\n");
        return;
    }
    lib_node* temp = head;

    do {
        if (idx == temp->index) {printf("\"%s\" ",temp->songname); return;}
        temp = temp->next;
    } while(temp!=head);

    printf("%sSong with Id: %d is not there in library!%s\n", YELLOW, idx, RESET);
    
    // // Converting int to string 
    // int temp = idx, len=0;
    // while(temp!=0){
    //     len++;
    //     temp/=(10);
    // }
    // char string[len+2];
    // temp = idx;
    // int i = len-1;
    // while(temp!=0){
    //     string[i--] = '0' + (temp%10);
    //     temp/=10;
    // }
    // char line[301];
    // string[len] = ' ';
    // string[len+1] = '\0';
    // int index = 2;

    // FILE* songsfilepointer;
    // songsfilepointer = fopen("songs.txt", "r");
    // while (fgets(line, 301, songsfilepointer)) {
    //     if (strncmp (line, string, len+1) == 0) {
    //         while (strncmp(line + index, "Song: ", 6) != 0) index++;
    //         index+=6;
    //         while (strncmp(line + index, "Singer: ", 8) != 0) {printf("%c", line[index]); index++;}
    //         fclose(songsfilepointer);
    //         return;
    //     }
    // }

    // fclose(songsfilepointer);
}
void free_library(lib_node* head) {
    if (head == NULL) {
        return;
    }

    lib_node* temp = head;
    lib_node* next_node;
    
    do {
        next_node = temp->next;
        free(temp);
        temp = next_node;
    } while (temp != head);
}

// int main() {

//     library = NULL;
//     library = gensong(library);

//     print_songs(library);
//     printf_song(2,library);
//     printf_onlysong(2,library);


//     // char album_name[] = "album1";
//     // gen_album(album_name);

//     // albumadd(1, album_name);
//     // albumadd(5, album_name);
//     // albumadd(7, album_name);

// return 0;
// }