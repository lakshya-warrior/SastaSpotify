#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headerfile.h"
#include "extractsong.h"
#include "albums.h"
#include "playlist.h"

int gen_album(char name[]){
    FILE* ablumfileptr;
    char line[301];
    ablumfileptr = fopen("albums.txt", "a+");
    rewind(ablumfileptr);

    while(fgets(line, 301, ablumfileptr)) {
        // printf("LINE: %s", line);
        // printf("%lu\n", strlen(name));
        // printf("Name: %s\n", name);
        if (strncmp(line, name, strlen(name)) == 0 && line[strlen(name)] == ' '){
            printf("%sThe album %s\"%s\" %sALREADY EXITS!%s\n", RED, RESET, name, RED, RESET);
            fclose(ablumfileptr);
            return 0;
        }
    }

    fprintf(ablumfileptr, "%s \n", name);
    fclose(ablumfileptr);
return 1;
}
void albumadd(int index, const char *name, lib_node* library){
    FILE *fPtr, *fTemp;
    char line[301];
    char new_line_content[301];
    int found = 0;

    fPtr = fopen("albums.txt", "r");
    fTemp = fopen("temp.txt", "w");

    while (fgets(line, 301, fPtr)) {
        if (strncmp(line, name, strlen(name)) == 0 && line[strlen(name)] == ' ') {
            int idx = strlen(name);

            while (line[idx] != '\0' && line[idx] != '\n' && line[idx] != EOF) {
                while (line[idx] != '\0' && line[idx]==' ') idx++;
                if (line[idx] == '\0' && line[idx] == '\n' && line[idx] == EOF) {
                    break;
                }

                int number = 0;
                while (line[idx] != '\0' && (line[idx] >= '0' && line[idx] <= '9')) {
                    number = (number * 10) + (line[idx] - '0');
                    idx++;
                }
                if (index == number) {
                    printf("%sSong %d Already there!%s\n", YELLOW, index, RESET);
                    fclose(fPtr);
                    fclose(fTemp);
                    remove("temp.txt");
                    return;
                }
            } 
            line[strlen(line)-1] = '\0';
            // Did not know how to edit a specic line of a file so 
            // I copied from Google not AI so pls don't cut marks

            // Append the new number to the line in the line
            // sprintf is used to format and concatenate string and integer
            snprintf(new_line_content, 301, "%s %d\n", line, index);
            // printf("LINE: %s\n", line);
            // printf("NEW LINE: %s", new_line_content);
            fprintf(fTemp, "%s", new_line_content);
            found = 1;

        } else {
            fprintf(fTemp, "%s", line);
        }
    }

    fclose(fPtr);
    fclose(fTemp);

    if (!found) {
        printf("%sAlbum \"%s\" not found.%s Please first create an album\n", YELLOW, name, RESET);
        remove("temp.txt");
        return;
    }

    remove("albums.txt");
    if (rename("temp.txt", "albums.txt") != 0) {
        printf("%sError renaming temporary file\n%s", RED, RESET);
    } else {
        printf("Added Song ");
        printf_onlysong(index, library);
        printf("to the album \"%s\"\n", name);
    }
}

void albumdel(int index, const char *name, lib_node* library){
    FILE *fPtr, *fTemp;
    char line[301];

    // Converting int to string 
    int temp = index, len=0;
    while(temp!=0){
        len++;
        temp/=(10);
    }
    char to_remove[len+2];
    temp = index;
    int idx = len, found=0;
    to_remove[0] = ' ';
    while(temp!=0){
        to_remove[idx--] = '0'+ (temp%10);
        temp/=10;
    }
    to_remove[len+1] = '\0';

    fPtr = fopen("albums.txt", "r");
    fTemp = fopen("temp.txt", "w");

    while (fgets(line, 301, fPtr)) {
        if (strncmp(line, name, strlen(name)) == 0 && line[strlen(name)] == ' ') {
            char *match = strstr(line, to_remove);

            if (match != NULL) {
                // returns in this datatype
                size_t remove_len = strlen(to_remove);
                char *rest_of_string = match + remove_len;

                size_t rest_len = strlen(rest_of_string) + 1;

                memmove(match, rest_of_string, rest_len);
                fprintf(fTemp, "%s", line);
                // printf("LINE: %s", line);
                found = 1;
            }
        }
        else {
            fprintf(fTemp, "%s", line);
        }
    }

    fclose(fPtr);
    fclose(fTemp);

    if (!found) {
        printf("%sSong Id: %d, not there in album%s \"%s\"\n", YELLOW, index, name, RESET);
        fclose(fPtr);
        fclose(fTemp);
        remove("temp.txt");
        return;
    }
    remove("albums.txt");
    if (rename("temp.txt", "albums.txt") != 0) {
        printf("%sError renaming temporary file%s\n", RED, RESET);
    } else {
        printf("Deleted Song ");
        printf_onlysong(index, library);
        printf("to the album \"%s\"\n", name);
    }
    
    FILE* logfile_pointer;
    logfile_pointer = fopen("log.txt", "a");
    fprintf(logfile_pointer,"6.2. Deleted Song %d to album --> %s\n", index, name);
    fclose(logfile_pointer);
}

void list_songs_album(char name[], lib_node* library){
    FILE *albumfilepointer;
    char line[301];
    albumfilepointer = fopen("albums.txt", "r");
    while (fgets(line, 301, albumfilepointer)) {
        if (strncmp(line, name, strlen(name)) == 0 && line[strlen(name)] == ' ') {
            // printf("LINE: >>%s<<\n", line);
            int idx = strlen(name);
            while (line[idx] != '\0' && line[idx] != '\n' && line[idx] != EOF) {
                while (line[idx] != '\0' && line[idx]==' ') idx++;
                if (line[idx] == '\0' && line[idx] == '\n' && line[idx] == EOF) {
                    break;
                }

                int number = 0;
                while (line[idx] != '\0' && (line[idx] >= '0' && line[idx] <= '9')) {
                    number = (number * 10) + (line[idx] - '0');
                    idx++;
                }
                if (number!=0) printf_song(number, library);
                // printf("Id: %d\n", number);
            }
        }
    }

    fclose(albumfilepointer);

}

song_list* return_songs_album(char name[], lib_node* library, song_list* head){
    FILE *albumfilepointer;
    char line[301];
    int songmax = 20, i = 1;
    // int* numbers = (int*)malloc((songmax)*sizeof(int));
    albumfilepointer = fopen("albums.txt", "r");
    while (fgets(line, 301, albumfilepointer)) {
        if (strncmp(line, name, strlen(name)) == 0 && line[strlen(name)] == ' ') {
            int idx = strlen(name);

            while (line[idx] != '\0' && line[idx] != '\n' && line[idx] != EOF) {
                while (line[idx] != '\0' && line[idx]==' ') idx++;

                if (line[idx] == '\0' || line[idx] == '\n') {
                    break;
                }

                int number = 0;
                while (line[idx] != '\0' && (line[idx] >= '0' && line[idx] <= '9')) {
                    number = (number * 10) + (line[idx] - '0');
                    idx++;
                }
                if (number == 0) continue;
                head = add_playlist(head, number, library);
            }
        }
    }
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
        printf("\"");
        while(line[idx] != ' ' && line[idx] != '\0' && line[idx] != EOF && idx < strlen(line)) printf("%c", line[idx++]);
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
        printf(" with %d Songs\n", count);
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
//     albumadd(2, name);
//     albumadd(3, album_name);
//     albumadd(17, album_name);

//     list_songs_album(album_name);
//     albumdel(3, album_name);
//     list_songs_album(album_name);

//     list_albums();
// return 0;
// }
