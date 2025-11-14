#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headerfile.h"
#include "extractsong.h"
#include "albums.h"
#include "playlist.h"

//void printcommands(){
//     printf("\nCOMMANDS (Type the blue part to execute)\n");
//     printf("0. help -- To show all the commands\n");
//     printf("1. songs -- To show all/specifc songs\n");
//     printf("2. log -- To show the commands you typed\n");
//     printf("3. clear -- To clear the log file\n");
//     printf("4. new-ablum -- Create a new empty album\n");
//     printf("5. albums -- List all your created albums\n");
//     printf("6. specific-album -- View/Add/Delete from a specific album\n");
//     printf("7. playlist -- Add/Delete/View from playlist\n");
//     printf("8. album-to-pl -- Adds a album to playlist\n");
//     printf("9. exit (q) -- To exit from program\n");
//     printf(">. next -- for next in pl\n");
//     printf("<. prev -- for previos song in pl\n");
//     printf("p. play -- for previos song in pl\n");
// }
void printcommands(){
    printf("\n%sCOMMANDS%s (Type the blue part to execute (number/word/>/<))\n", GREEN, RESET);
    printf("%s0%s. %shelp%s -- To show all the commands\n", BLUE, RESET, BLUE, RESET);
    printf("%s1%s. %ssongs%s -- To show all/specifc songs\n", BLUE, RESET , BLUE, RESET);
    printf("%s2%s. %slog%s -- To show the commands you typed\n", BLUE, RESET, BLUE, RESET);
    printf("%s3%s. %sclear%s -- To clear the log file\n", BLUE, RESET, BLUE, RESET);
    printf("%s4%s. %snew-ablum%s -- Create a new empty album\n", BLUE, RESET, BLUE, RESET);
    printf("%s5%s. %salbums%s -- List all your created albums\n", BLUE, RESET, BLUE, RESET);
    printf("%s6%s. %sspecific-album%s -- View/Add/Delete from a specific album\n", BLUE, RESET, BLUE, RESET);
    printf("%s7%s. %splaylist%s -- Add/Delete/View from playlist\n", BLUE, RESET, BLUE, RESET);
    printf("%s8%s. %salbum-to-pl%s -- Adds a album to playlist\n", BLUE, RESET, BLUE, RESET);
    printf("%s9%s. %sexit%s (%sq%s) -- To exit from program\n", BLUE, RESET, BLUE, RESET, BLUE, RESET);
    printf("%s>%s. %snext%s -- for next in pl\n", BLUE, RESET, BLUE, RESET);
    printf("%s<%s. %sprev%s -- for previos song in pl\n", BLUE, RESET, BLUE, RESET);
    printf("%sp%s. %splay%s -- for previos song in pl\n", BLUE, RESET, BLUE, RESET);
}

int commandshelp(char* input) {
    if (strcmp(input, "help") == 0) return 0;
    if (strcmp(input, "log") == 0) return 2;
    if (strcmp(input, "songs") == 0) return 1;
    if (strcmp(input, "new-album") == 0) return 4;
    if (strcmp(input, "clear") == 0) return 3;
    if (strcmp(input, "albums") == 0) return 5;
    if (strcmp(input, "specific-album") == 0) return 6;
    if (strcmp(input, "playlist") == 0) return 7;
    if (strcmp(input, "album-to-pl") == 0) return 8;
    if (strcmp(input, "exit") == 0 || strcmp(input, "quit") == 0) return 9;
    if (strcmp(input, "next") == 0) return 14;
    if (strcmp(input, "prev") == 0) return 12;
    if (strcmp(input, "play") == 0) return 10;
    
    return -1;
}

/* TODO
dont go back to start always
adding colours proprly
Error statements
if file does not exist
play pause
playing animantion
*/

int main() {
FILE *logfile_pointer;
song_list* playlist = NULL;
int choice, song_idx;
char input_choice[50], album_name[101];
lib_node* library = NULL;
library = gensong(library);

printcommands();

while(1) {
    printf("%sChoice %s(%s0%s/%shelp%s for commands): ", green1, RESET, BLUE, RESET, BLUE, RESET);
    // fgets(input_choice, 50, stdin);
    // // scanf(" %s", input_choice);
    // // printf(">>%s<<", input_choice);
    // // printf("%lu", strlen(input_choice));
    // // input_choice[strlen(input_choice)-1] = '\0';
    
    fgets(input_choice, 50, stdin);
    if (input_choice[0] == '\n') fgets(input_choice, 50, stdin);
    
    if (strchr(input_choice, '\n') == NULL) {
        int c;
        while ((c = getchar()) != '\n'); // scaning all the characters after 50 to remove them
    }
    else {
        input_choice[strlen(input_choice)-1] = '\0';
    }

    if (input_choice[0] == '\0') {
        continue;
    }

    if (strlen(input_choice) == 1) choice = (int)(input_choice[0] - 48);
    else choice = commandshelp(input_choice);
    // printf(">%d<", choice);

    switch(choice) {
        case 0:
            printcommands();
            logfile_pointer = fopen("log.txt", "a");
            fprintf(logfile_pointer, "0. help\n");
            fclose(logfile_pointer);
            break;
        case 1:
            printf("Enter song number (Enter %s0%s for all songs): ", BLUE, RESET);
            scanf("%d", &song_idx);
            if (song_idx == 0) {
                print_songs(library);
                logfile_pointer = fopen("log.txt", "a");
                fprintf(logfile_pointer, "1.1. show all Songs\n");
                fclose(logfile_pointer);
            }
            else {
                printf_song(song_idx,library);
                logfile_pointer = fopen("log.txt", "a");
                fprintf(logfile_pointer, "1.2. show Song Details --> %d\n", song_idx);
                fclose(logfile_pointer);
            }
            break;
        case 2:
            printf("%s-------Log File-------%s\n", GREEN, RESET);
            logfile_pointer = fopen("log.txt", "a+");
            fprintf(logfile_pointer, "2. log\n");
            char line[71];
            rewind(logfile_pointer);
            while(fgets(line,71,logfile_pointer)){
                printf("%s", line);
            }
            fclose(logfile_pointer);
            break;
        case 3:
            printf("%sWarning!%s This will clear all the log data.%s\nDo you want to do that? (%sy%s/%sn%s): \n", RED, YELLOW, RESET, green1, RESET, red1, RESET);
            char logyesno;
            scanf(" %c", &logyesno);
            if (logyesno=='y'|| logyesno=='Y') {

                logfile_pointer = fopen("log.txt", "w");
                fprintf(logfile_pointer, "3. clear log\n");
                fclose(logfile_pointer);
                printf("Cleared All data of log file!\n");
            }
            break;
        case 4:
            while (1) {
                printf("ENTER THE name of the new album: ");
                fgets(album_name, sizeof(album_name), stdin);
                album_name[strlen(album_name)-1] = '\0';

                if (album_name[0] == '\0') {
                    printf("Name cannot be empty\n");
                    continue;
                }
                if (strchr(album_name, ' ') != NULL) {
                    printf("TYPE A %sSINGLE STRING%s pls\n", RED, RESET);
                    continue;
                }
                break; 
            }
            if (gen_album(album_name)) printf("Created Album \"%s\"\n", album_name);
            logfile_pointer = fopen("log.txt", "a");
            fprintf(logfile_pointer,"4. Created New ablum --> \"%s\"\n", album_name);
            fclose(logfile_pointer);

            char yesno;
            printf("Do you want to add songs right now? (%sy%s/%sn%s): \n", green1, RESET, red1, RESET);
            scanf(" %c", &yesno);

            while (yesno=='y'|| yesno=='Y') {
                printf("Type the index of the song to add, for song list type %s0%s): \n", BLUE, RESET);
                    scanf("%d", &song_idx);
                    if (song_idx == 0) {
                        printf("Library\n");
                        print_songs(library);
                        printf("Type the index of the song to add: \n");
                        scanf("%d", &song_idx);
                    }
                    if (checksong(song_idx, library) == 1){
                        albumadd(song_idx, album_name, library);
                        logfile_pointer = fopen("log.txt", "a");
                        fprintf(logfile_pointer,"6.1. Added Song %d to album --> %s\n", song_idx, album_name);
                        fclose(logfile_pointer);
                    }
                    printf("Do you want to add more songs? (%sy%s/%sn%s): \n", green1, RESET, red1, RESET);
                    scanf(" %c", &yesno);
            }
            break;
        case 5:
            list_albums();
            logfile_pointer = fopen("log.txt", "a");
            fprintf(logfile_pointer,"5. Print Albums\n");
            fclose(logfile_pointer);
            break;
        case 6:
            while (1) {
                printf("Type the name of the album: ");
                fgets(album_name, sizeof(album_name), stdin);
                album_name[strcspn(album_name, "\n")] = '\0';

                if (album_name[0] == '\0') {
                    printf("%sName cannot be empty%s\n",YELLOW ,RESET);
                    continue;
                }
                if (strchr(album_name, ' ') != NULL) {
                    printf("%sAlbum name has to single string%s\n",YELLOW,RESET);
                    continue;
                }
                break; 
            }

            int choice2=-2;
            while(choice2!=-1){
                printf("%s1%s. Add\n%s2%s. Del\n%s3%s. View\n", BLUE, RESET, BLUE, RESET, BLUE, RESET);
                scanf("%d", &choice2);
                switch (choice2)
                {
                case 1:
                    printf("Type the index of the song to add (for songs list type %s0%s): ", BLUE, RESET);
                    scanf("%d", &song_idx);
                    if (song_idx == 0) {
                        printf("Library\n");
                        print_songs(library);
                        printf("Type the index of the song to add: ");
                        scanf("%d", &song_idx);
                    }
                    if (checksong(song_idx, library) == 1){
                        albumadd(song_idx, album_name, library);
                        choice2 = -1;
                    } 
                    else choice2 = -2;
                    logfile_pointer = fopen("log.txt", "a");
                    fprintf(logfile_pointer,"6.1. Added Song %d to album --> %s\n", song_idx, album_name);
                    fclose(logfile_pointer);
                    choice2 = -1;
                    break;
                case 2:
                    printf("Type the index of the song to delete, (for songs in album type %s0%s): ", BLUE, RESET);
                    
                    scanf("%d", &song_idx);
                    if (song_idx == 0) {
                        printf("The Album Contains: \n");
                        list_songs_album(album_name, library);
                        printf("Type the index of the song to delete: ");
                        scanf("%d", &song_idx);
                    }
                    if (checksong(song_idx, library) == 1){
                        albumdel(song_idx, album_name, library);
                        choice2 = -1;
                    } 
                    else choice2 = -1;
                    break;
                case 3:
                    printf("The Album Contains: \n");
                    list_songs_album(album_name, library);
                    logfile_pointer = fopen("log.txt", "a");
                    fprintf(logfile_pointer,"6.3. Show Context of album --> %s\n", album_name);
                    fclose(logfile_pointer);
                    choice2 = -1;
                    break;
                default:
                    printf("Type a valid command\n");
                    choice2 = -2;
                    break;
                }
            }
        break;
        case 7:
            ;
            int choice3=-2;
            while(choice3!=-1){
                printf("%s1%s. Add\n%s2%s. Del\n%s3%s. View\n", BLUE, RESET, BLUE, RESET, BLUE, RESET);
                scanf("%d", &choice3);
                switch (choice3) {
                    case 1:
                        printf("Type the index of the song to add, (for song list type %s0%s): ", BLUE, RESET);
                        scanf("%d", &song_idx);
                        if (song_idx == 0) {
                            printf("Library\n");
                            print_songs(library);
                            printf("Type the index of the song to add: ");
                            scanf("%d", &song_idx);
                        }

                        if (checksong(song_idx, library) == 1){
                            playlist = add_playlist(playlist, song_idx, library);
                        }

                        char yesno;
                        printf("Do you want to add more songs to the playlist? (%sy%s/%sn%s): \n", green1, RESET, red1, RESET);
                        scanf(" %c", &yesno);

                        while (yesno=='y'|| yesno=='Y') {
                            printf("Type the index of the song to add, (for song list type %s0%s): \n", BLUE, RESET);
                                scanf("%d", &song_idx);
                                if (song_idx == 0) {
                                    printf("Library\n");
                                    print_songs(library);
                                    printf("Type the index of the song to add: \n");
                                    scanf("%d", &song_idx);
                                }

                                if (checksong(song_idx, library) == 1){
                                    playlist = add_playlist(playlist, song_idx, library);
                                }
                            printf("Do you want to add more songs to the playlist? (%sy%s/%sn%s): \n", green1, RESET, red1, RESET);
                            scanf(" %c", &yesno);
                        }
                        choice3 = -1;
                        break;
                    case 2:
                        printf("Type the index of the song to delete, (for songs in playlist type %s0%s): ", BLUE, RESET);
                        
                        scanf("%d", &song_idx);
                        if (song_idx == 0) {
                            showpl(playlist, library);
                            printf("Type the index of the song to delete: ");
                            scanf("%d", &song_idx);
                        }
                        if (checksong(song_idx, library) == 1){
                            playlist = del_playlist(playlist, song_idx, library);
                            choice3 = -1;
                        }                        
                        else choice3 = -2;
                        break;
                    case 3:
                        showpl(playlist, library);
                        logfile_pointer = fopen("log.txt", "a");
                        fprintf(logfile_pointer,"7.3. Show Playlist\n");
                        fclose(logfile_pointer);
                        choice3 = -1;
                        break;
                    default:
                        printf("%sGIVE VALID COMMAND!%s\n",RED, RESET);
                        choice3 = -2;
                        break;
                }
            }
        break;
        case 8:
            while (1) {
                printf("Type the album name: ");
                fgets(album_name, sizeof(album_name), stdin);
                album_name[strcspn(album_name, "\n")] = '\0';

                if (album_name[0] == '\0') {
                    printf("%sName cannot be empty%s\n",YELLOW ,RESET);
                    continue;
                }
                if (strchr(album_name, ' ') != NULL) {
                    printf("%sAlbum name has to single string%s\n",YELLOW,RESET);
                    continue;
                }
                break; 
            }

            playlist = add_album_playlist(playlist, album_name, library);
            logfile_pointer = fopen("log.txt", "a");
            fprintf(logfile_pointer,"8. Added Album \"%s\" to playlist\n", album_name);
            fclose(logfile_pointer);
            break;
        case 65:
        case 33:
        case 9:
            printf("%sExiting application...%s\n",GREEN, RESET);
            free_playlist(playlist);
            free_library(library);
            logfile_pointer = fopen("log.txt", "a");
            fprintf(logfile_pointer, "9. Exit\n");
            fclose(logfile_pointer);
            return 0;
        case 12:
            playlist =  playprev(playlist, library);
            logfile_pointer = fopen("log.txt", "a");
            fprintf(logfile_pointer, "<. previous Song\n");
            fclose(logfile_pointer);
            break;
        case 14:
            playlist =  playnext(playlist, library);
            logfile_pointer = fopen("log.txt", "a");
            fprintf(logfile_pointer, ">. next Song\n");
            fclose(logfile_pointer);
            break;
        case 64:
        case 32:
        case 10:
            playlist =  play(playlist, library);
            logfile_pointer = fopen("log.txt", "a");
            fprintf(logfile_pointer, "p. play Song\n");
            fclose(logfile_pointer);
            break;
        default:
            printf("%sInvalid choice. Try again.%s\n", YELLOW, RESET);
        }
}
return 0;
}
