#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include <string.h>

void print_int (element_t ev) {
  int* e = ev;
  printf ("%d\n", *e);
}

void print_str (element_t ev) {
  char e[100];
  strcpy(e,ev);
  puts(e);
}

void pickNumber (element_t* rv, element_t av) {
    char* a = av;
    int **r = (int**) rv;
    if (*r == NULL) {
        *r = malloc(sizeof(int));
    }

    char* c;
    int d = strtol(av, &c, 10);
    if (d == 0) {
        **r = -1;
    } else {
        **r = d;
    }
} 

void map_two_lists (element_t* rv, element_t av, element_t bv) {
    int *a = av;
    char *b = bv;
    char **r = (char**) rv;

    if (*r == NULL) {
        *r = malloc(strlen(b) + 1);
    }

    if (*a == -1) {
        strcpy(*r, b);
    } else {
        r = NULL;
    }
}

int isPositive (element_t av) {
  int *a = av;
  return (*a >=0);
}

int isNotNull (element_t av) {
  int *a = av;
  return ! (*a == NULL);
}

void join_all (element_t* rv, element_t av, element_t bv) {
  char *a = av, *b = bv, **r = (char**) rv;
  if (*r == NULL)
    *r = malloc(sizeof(int));

  strcat (*r,b);
  strcat (*r, " ");
}

void truncate_str (element_t* rv, element_t av, element_t bv) {
    int *a = av;
    char *b = bv;
    char **r = (char**) rv;

    if (*r == NULL) {
        *r = malloc(strlen(b) + 1);
    }

    strncpy(*r,b,*a);
}

void find_max (element_t* rv, element_t av, element_t bv) {
    int *a = av;
    char *b = bv;
    int **r = (int**) rv;

    if (*r == NULL) {
        *r = malloc(sizeof(int));
    }

    
    if (**r >= *b) {
    } else {
        **r = *b;
    }
}

int main(int argc, char *argv[]) {
    struct list* arguments = list_create();

    for (int i = 0; i < argc -1; i++) {
        element_t element = argv[i+1];
        list_append (arguments, element);
    }

    // printf ("step1:\n");
    // list_foreach (print_str, arguments);

    struct list* list0 = list_create(); // int list (not filtered)
    list_map1(pickNumber,list0,arguments);
    // printf ("step2:\n");
    // list_foreach (print_int, list0);

    struct list* list1 = list_create();  // string list (not filtered)
    list_map2 (map_two_lists, list1, list0, arguments);
    // printf ("step3:\n");
    // list_foreach (print_str, list1);
    
    struct list* list2 = list_create();  // int list (filtered)
    list_filter (isPositive, list2, list0);
    // printf ("step4:\n");
    // list_foreach (print_int, list2);

    struct list* list3 = list_create();  // string list (filtered)
    list_filter (isNotNull, list3, list1);
    // printf ("step5:\n");
    // list_foreach (print_str, list3);

    struct list* list4 = list_create();
    list_map2(truncate_str,list4,list2,list3);
    // printf ("step6,7:\n");
    list_foreach (print_str, list4);

    char s[40];
    char *sp = &s;
    list_foldl(join_all,(element_t*) &sp,list4);
    // printf ("step8:\n");
    puts(s);

    int num = 0, *np = &num;
    list_foldl (find_max, (element_t*) &np, list2);
    printf ("%d\n", num);

    list_foreach (free, list0);
    list_foreach (free, list1);
    list_foreach (free, list4);

    list_destroy (list0);
    list_destroy (list1);
    list_destroy (list2);
    list_destroy (list3);
    list_destroy (list4);
    list_destroy (arguments);
}