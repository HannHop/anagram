/*Assignment 15
Anagrams. The user enters a string.
Write a program that checks a (given) dictionary
for occurrences of anagrams of this string.
For example, ANGLE and GALEN are anagrams.
Use a dictionary for crosswords’ solvers. */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define size_current 128
#define size_w 10

typedef struct List_node{
    char word[30];
    struct List* next;
}List;

void swap(char* a, char* b){
    char temp = *a;
    *a=*b;
    *b=temp;
}

bool is_contained_in (List* dic, char* word) {
    List * current = dic;

    while(current){
        if (strcmp(current->word, word) == 0) {
            return true;
        }
        current = current->next;
    }

    return false;
}


void permute(char *perm_word, int start_index, int end_index, List * head, List * collect_head)
{
   int i;
   if (start_index == end_index) {
    //printf(".. %s ..", perm_word);
    if(!is_contained_in(collect_head, perm_word)){ //checks whether this word exists in collection
        if(is_contained_in(head,perm_word)){ //checks whether it is even realm90
            List * current_c = collect_head;
            while(current_c->next){
                current_c = current_c->next;
            }

            List * new_c = current_c->next;
            new_c = malloc(sizeof(List));
            strcpy(&new_c->word, perm_word);
            current_c->next = new_c;
        }
    }
   }
   else
   {
       for (i = start_index; i <= end_index; i++)
       {
          swap((perm_word+start_index), (perm_word+i));
          permute(perm_word, start_index+1, end_index, head, collect_head);
          swap((perm_word+start_index), (perm_word+i));
       }
   }
}

int main(){
    //char* in_word;
    char in_word[size_w];
    char file_name[128];
    char current_word[size_current];
    FILE* file;
    printf("Welcome to anagram finder.\n\n");

    printf("Write name of dictionary file (without extension)\nRemember, only txt files are supported!\n");
    scanf("%s", &file_name);

    char * file_name_ext = malloc(strlen(file_name) + 4); //'.txt' is 4 character long
    strcpy(file_name_ext, file_name);
    strcat(file_name_ext, ".txt");

    file = fopen(file_name_ext, "r");

    if (!file) {
        printf("Unfortunately, file you would like to use as dictionary doesn't exist. \n");
        return -3;
    }

    int i=0;

    List* head = malloc(sizeof(List));
    List* current = head;

    List* collect_head = malloc(sizeof(List));
    strcpy(&collect_head->word, "");
    collect_head->next = NULL;

    while (!feof(file)) {
        fscanf(file, "%s", &current_word);
        strcpy(&current->word, current_word);

        current->next = malloc(sizeof(List));
        current = current->next;
    }

    fclose(file);

    current = head;

    printf("What is your word?\n");
    scanf("%s", &in_word);

    if(!is_contained_in(head, in_word)) {
        printf("Invalid word! \n");
        return 2222222222;
    }
    printf("Results without given word:"); //only if found

    int len = strlen(in_word);
    permute(in_word,0,len-1,head, collect_head);

    i=0;
    current = collect_head;
    while(current){
        if (strcmp(current->word, in_word) != 0) {
            printf("%s \n", current->word);
            i++;
        }
        current=current->next;
    }


    if(i==1) printf("No other results");

    List* previous;
    current = head;
    while(current->next){
        previous = current;
        current = current->next;
        free(previous);
    }

    current = collect_head;
    while(current->next){
        previous = current;
        current = current->next;
        free(previous);
    }

    free (current);
    free (head);
    free (collect_head);

    return 0;
}
