#ifndef TESTING
#define TESTING

typedef struct song_list
{   
    int index;
    int song_index;
    struct song_list* next;
    struct song_list* prev;
}song_list;

typedef struct lib_node
{
    int index;
    char songname[101];
    char singer[101];
    int time;
    struct lib_node* next;
}lib_node;

// From Whatsapp group
#define YELLOW "\033[1;33m"
#define RESET "\033[0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define WHITE "\033[1;37m"
#define PINK "\033[1;35m"
#define BLUE "\033[34m"
#define green1 "\033[32m"
#define red1 "\033[31m"

void printcommands();

#endif