#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headerfile.h"
#include "extractsong.h"
#include "albums.h"
#include "playlist.h"

int numberofalbums = 1;

void genalbumcnt() {
    
    char line[301];
    int max_id = 0;
    FILE *albumfileptr;
    albumfileptr = fopen("albums.txt", "r");
    if (albumfileptr == NULL) {
        numberofalbums = 1;
        return;
    }

    while (fgets(line, 301, albumfileptr)) {
        numberofalbums++;
    }
fclose(albumfileptr);
printf("Loaded (%d) ablums", numberofalbums-1);
}

int gen_album(char name[]){
    FILE* ablumfileptr;
    char line[301];
    ablumfileptr = fopen("albums.txt", "a");

    // rewind(ablumfileptr);
    // while(fgets(line, 301, ablumfileptr)) {
    //     // printf("LINE: %s", line);
    //     // printf("%lu\n", strlen(name));
    //     // printf("Name: %s\n", name);
    //     if (strncmp(line, name, strlen(name)) == 0 && line[strlen(name)] == ' '){
    //         printf("%sThe album %s\"%s\" %sALREADY EXITS!%s\n", RED, RESET, name, RED, RESET);
    //         fclose(ablumfileptr);
    //         return 0;
    //     }
    // }

    fprintf(ablumfileptr, "%d$%s$ \n",numberofalbums, name);
    numberofalbums++;
    fclose(ablumfileptr);
return numberofalbums-1;
}

void albumname(int idx_to_find) {
    FILE *albumfileptr;
    char line[301];
    int found = 0;

    // Converting int to string 
    int temp = idx_to_find, len=0;
    while(temp!=0){
        len++;
        temp/=(10);
    }
    char string[len+2];
    temp = idx_to_find;
    int i = len-1;
    while(temp!=0){
        string[i--] = '0' + (temp%10);
        temp/=10;
    }
    string[len] = '$';
    string[len+1] = '\0';
    //printf("HERE0 %s\n", string);

    albumfileptr = fopen("albums.txt", "r");
    while (fgets(line, 301, albumfileptr)) {
        if (strncmp(line, string, len) == 0) {
            found = 1;
            int idx = len+1;

            printf("\"");
            while (line[idx] != '\0' && line[idx] != '$') {
                printf("%c", line[idx]);
                idx++;
            }
            printf("\"");
            break;
        }
    }
    fclose(albumfileptr);

    if (!found) {
        printf("Album ID: %d Not Found", idx_to_find);
    }
}

void albumadd(int index, int albumidx, lib_node* library) {
    FILE *albumfileptr, *tempfileptr;
    char line[301];
    char newline[301];
    int found = 0;
    int duplicate_found = 0;

    // Converting int to string 
    int temp = albumidx, len=0;
    while(temp!=0){
        len++;
        temp/=(10);
    }
    char string[len+2];
    temp = albumidx;
    int i = len-1;
    while(temp!=0){
        string[i--] = '0' + (temp%10);
        temp/=10;
    }
    string[len] = '$';
    string[len+1] = '\0';

    albumfileptr = fopen("albums.txt", "r");
    tempfileptr = fopen("temp.txt", "w");

    while (fgets(line, 301, albumfileptr)) {
        if (!found && strncmp(line, string, len) == 0) {
            found = 1;
            int idx = len+1;

            while (line[idx] != '\0' && line[idx] != '$') {
                idx++;
            }
            if (line[idx] != '$') {
                fprintf(tempfileptr, "%s", line);
                continue; 
            }
            idx++; 

            int temp_idx = idx; 
            while (line[temp_idx] != '\0' && line[temp_idx] != '\n') {
                while (line[temp_idx] != '\0' && (line[temp_idx] < '0' || line[temp_idx] > '9')) temp_idx++;
                
                if (line[temp_idx] == '\0' || line[temp_idx] == '\n') break;
                
                int number = 0;
                while (line[temp_idx] >= '0' && line[temp_idx] <= '9') {
                    number = (number * 10) + (line[temp_idx] - '0');
                    temp_idx++;
                }
                if (number == index) {
                    printf("%sSong %d Already there!%s\n", YELLOW, index, RESET);
                    duplicate_found = 1;
                    break;
                }
            }

            if (duplicate_found) {
                fprintf(tempfileptr, "%s", line);
            } 
            else {
                line[strcspn(line, "\n")] = '\0';
                snprintf(newline, 301, "%s %d\n", line, index);
                
                // char indexstr[20];
                // sprintf(indexstr, "%d", index);
                // line[strcspn(line, "\n")] = '\0'; 
                // strcpy(newline, line);    
                // strcat(newline, " ");       
                // strcat(newline, indexstr);  
                // strcat(newline, "\n");
                fprintf(tempfileptr, "%s", newline);
            }
        } 
        else {
            fprintf(tempfileptr, "%s", line);
        }
    }

    fclose(albumfileptr);
    fclose(tempfileptr);

    if (!found) {
        printf("%sAlbum Id: %d not found%s Please first create an album\n", YELLOW, albumidx, RESET);
        remove("temp.txt");
        return;
    }

    remove("albums.txt");
    rename("temp.txt", "albums.txt"); 
    if (!duplicate_found) {
        printf("Added Song ");
        printf_onlysong(index, library);
        printf(" to the album ");
        albumname(albumidx);
        printf("\n");
    }
}

void albumdel(int index, int albumidx, lib_node* library) {
    FILE *albumfileptr, *tempfileptr;
    char line[301];
    int found_album = 0;
    int found_song_in_album = 0;

    // Converting int to string 
    int temp = index, remove_len=0;
    while(temp!=0){
        remove_len++;
        temp/=(10);
    }
    char to_remove[remove_len+2];
    temp = index;
    int i = remove_len;
    while(temp!=0){
        to_remove[i--] = '0' + (temp%10);
        temp/=10;
    }
    to_remove[0] = ' ';
    to_remove[remove_len+1] = '\0';
    remove_len++;

    // Converting int to string 
    temp = albumidx; 
    int len=0;
    while(temp!=0){
        len++;
        temp/=(10);
    }
    char string[len+2];
    temp = albumidx;
    i = len-1;
    while(temp!=0){
        string[i--] = '0' + (temp%10);
        temp/=10;
    }
    string[len] = '$';
    string[len+1] = '\0';

    albumfileptr = fopen("albums.txt", "r");
    tempfileptr = fopen("temp.txt", "w");

    while (fgets(line, 301, albumfileptr)) {
        if (!found_album && strncmp(line, string, len+1) == 0) {
            found_album = 1;
            int idx = len + 1; 

            while (line[idx] != '$' && line[idx] != '\n' && line[idx] != '\0'&& line[idx] != EOF) idx++;
            
            if (line[idx] == '$') idx++;
            while (strncmp((line + idx), to_remove, remove_len) != 0 || !(line[idx + remove_len] == ' ' || line[idx + remove_len] == '\n' || line[idx + remove_len] == '\0')) {
                
                if (line[idx] == '\0' || line[idx] == '\n') {
                    found_song_in_album = -1;
                    break;
                }
                idx++;
            }
            found_song_in_album++;

            if (found_song_in_album==1) {
                for (int i = 0; i < idx; i++) fprintf(tempfileptr, "%c", line[i]);
                fprintf(tempfileptr, "%s", line + idx + remove_len);
            } 

            else {
                fprintf(tempfileptr, "%s", line);
            }
        } 
        else {
            fprintf(tempfileptr, "%s", line);
        }
    }
    fclose(albumfileptr);
    fclose(tempfileptr);

    if (found_album == 0) {
        printf("%sAlbum Id: %d not found.%s\n", YELLOW, albumidx, RESET);
        remove("temp.txt");
        return;
    }

    if (found_song_in_album == 0) {
        printf("%sSong Id: %d not found in album Id: %d %s ", YELLOW, index, albumidx, RESET);
        albumname(albumidx);
        printf("\n");
        remove("temp.txt");
        return;
    }

    remove("albums.txt");
    rename("temp.txt", "albums.txt");
    printf("Deleted Song ");
    printf_onlysong(index, library);
    printf(" from the album Id: %d ", albumidx);
    albumname(albumidx);
    printf("\n");

    FILE* logfile_pointer;
    logfile_pointer = fopen("log.txt", "a");
    fprintf(logfile_pointer, "6.2. Deleted Song %d from album --> %d\n", index, albumidx);
    fclose(logfile_pointer);
}
void list_songs_album(int albumidx, lib_node* library) {
    FILE *albumfilepointer;
    char line[301];
    int album_found = 0;

    // Converting int to string 
    int temp = albumidx, len=0;
    while(temp!=0){
        len++;
        temp/=(10);
    }
    char string[len+2];
    temp = albumidx;
    int i = len-1;
    while(temp!=0){
        string[i--] = '0' + (temp%10);
        temp/=10;
    }
    string[len] = '$';
    string[len+1] = '\0';

    albumfilepointer = fopen("albums.txt", "r");
    
    while (fgets(line, 301, albumfilepointer)) {
        if (strncmp(line, string, len) == 0) {
            album_found = 1;
            int idx = len+1;
            while (line[idx] != '\0' && line[idx] != '$') {
                idx++;
            }
            if (line[idx] != '$') continue;
            idx++;
            
            int songs = 0;
            while (line[idx] != '\0' && line[idx] != '\n') {
                while (line[idx] != '\0' && (line[idx] < '0' || line[idx] > '9')) {
                    idx++;
                }
                if (line[idx] == '\0' || line[idx] == '\n') break;
                
                int number = 0;
                while (line[idx] >= '0' && line[idx] <= '9') {
                    number = (number * 10) + (line[idx] - '0');
                    idx++;
                }
                if (number != 0) {
                    printf_song(number, library);
                    songs++;
                }
            }
            
            if (songs == 0) {
                 printf("Album ");
                 albumname(albumidx);
                 printf(" is empty\n");
            }  
            break;
        }
    }
    if (album_found == 0) {
        printf("%sError: Album with ID %d not found%s\n", RED, albumidx, RESET);
    }
    fclose(albumfilepointer);
}

song_list* return_songs_album(int albumidx, lib_node* library, song_list* head) { // for add_album_playlist
    FILE *albumfilepointer;
    char line[301];

    // Converting int to string 
    int temp = albumidx, len=0, found=0;
    while(temp!=0){
        len++;
        temp/=(10);
    }
    char string[len+2];
    temp = albumidx;
    int i = len-1;
    while(temp!=0){
        string[i--] = '0' + (temp%10);
        temp/=10;
    }
    string[len] = '$';
    string[len+1] = '\0';

    albumfilepointer = fopen("albums.txt", "r");
    while (fgets(line, 301, albumfilepointer)) {
        if (strncmp(line, string, len) == 0) {
            int idx = len;
            found = 1;
            while (line[idx] != '\0' && line[idx] != '$') idx++;
            if (line[idx] != '$') continue;
            idx++;
            
            int songs = 0;
            while (line[idx] != '\0' && line[idx] != '\n') {
                while (line[idx] != '\0' && (line[idx] < '0' || line[idx] > '9')) {
                    idx++;
                }
                if (line[idx] == '\0' || line[idx] == '\n') break;
                
                int number = 0;
                while (line[idx] >= '0' && line[idx] <= '9') {
                    number = (number * 10) + (line[idx] - '0');
                    idx++;
                }
                if (number != 0) {
                    head = add_playlist(head, number, library);
                    songs++;
                }
            }

            if (songs == 0) { printf("Album ");
                 albumname(albumidx);
                 printf(" is empty\n");
            }  
            break;
        }
    }

    if (found == 0) printf("%sError: Album with ID %d not found%s\n", RED, albumidx, RESET);
    
    fclose(albumfilepointer);
    return head;
}

void list_albums(){
    FILE *albumfilepointer;
    char line[301];
    int count =0;

    albumfilepointer = fopen("albums.txt", "r");

    while (fgets(line, 301, albumfilepointer)) {
        // fscanf(albumfilepointer, "%s ", name);
        int idx=0;

        printf("Id: ");
        while (line[idx] != '$') printf("%c", line[idx++]);
        idx++;
        printf(" Album Name: \"");
        while(line[idx] != '\0' && line[idx] != EOF && idx < strlen(line) && line[idx]!='\n'  && line[idx]!='$') printf("%c", line[idx++]);
        printf("\"");
        // To see how manys songs are ther in album
        while (line[idx] != '\0' && line[idx] != '\n') {
            while (line[idx] != '\0' && (line[idx] < '0' || line[idx] > '9')) {
                idx++;
            }
            if (line[idx] >= '0' && line[idx] <= '9') {
                count++;
                while (line[idx] >= '0' && line[idx] <= '9') {
                    idx++;
                }
            }
        }
        printf(" with (%d) Songs\n", count);
        count = 0;
    }
fclose(albumfilepointer);
}

// void albumcount(char* line, int idx){
//     int count=0;
//     while (line[idx] != '\0' && line[idx] != '\n') {
//             while (line[idx] != '\0' && (line[idx] < '0' || line[idx] > '9')) {
//                 idx++;
//             }
//             if (line[idx] >= '0' && line[idx] <= '9') {
//                 count++;
//                 while (line[idx] >= '0' && line[idx] <= '9') {
//                     idx++;
//                 }
//             }
//         }
//         printf(" with %d Songs\n", count);
//         count = 0;
// }

// int main(){
//     char album_name[] = "album4";
//     gen_album(album_name);
//     char name[] = "album4";
//     albumadd(2, 1, lib_nod);
//     albumadd(3, album_name);
//     albumadd(17, album_name);

//     list_songs_album(album_name);
//     albumdel(3, album_name);
//     list_songs_album(album_name);

//     list_albums();
// return 0;
// }
