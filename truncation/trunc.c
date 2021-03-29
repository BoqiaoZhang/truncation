#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include <ctype.h>
#include "list.h"
// #include "test.c"


void print (element_t ev) {
  int* e = (int *)ev;
  printf ("%d\n", *e);
}

void print_str (element_t ev) {
  char* e = (char *)ev;
  printf ("%s\n", e);
  // char e[100];
  // strcpy(e,ev);
  // puts(e);
}

void string_to_int (element_t* rv, element_t av) {
    char *a = av; //input
    int **r = (int**) rv;  //output
    char *remaning; // = remaning;
    if (*r == NULL) { 
        *r = malloc(sizeof(int));
    }
    int digit_or_not = isdigit(*a);
    int number = strtol(a, &remaning, 10);
    if (digit_or_not == 0) {
        // not a number
        **r = -1;
    } else {
        **r = number;
    }
}

void number_to_null (element_t* rv, element_t av, element_t bv) {
  // printf("number_to_null starts\n");
  char **r = (char**) rv;
  char *a = (char*) av;
  int *b = (int *) bv;
  if (*r = NULL) {
    *r = malloc(strlen(a)+1);
  }
  if (*b != -1) {
    //int 
    r = NULL;
  } else {
    // string
    // strcpy(*r, a);
    *r = strdup(a);
    // printf("%p\n", r);
    // printf("0x%x\n", r);
    // printf("%p\n", *r);
    // gets(*r);
    // printf("%s\n", *r);
  }
}

int remove_negatives (element_t av) {
    //return true when *av is non-negative
  // printf("remove_negatives starts\n");
  int *a = av;
  if (*a >= 0) {
      return 1;
  } else {
      return 0;
  }
}

int remove_null (element_t av) {
    //return true when *av is non-negative
  // printf("remove_null starts\n");
  char *a = av;
  if (a == NULL) {
      return 0;
  } else {
      return 1;
  }
}

void my_trunc (element_t* rv, element_t av, element_t bv) {
  char **r = (char**) rv;
  int *a = (int*) av;
  char *b = (char *) bv;
  // printf("cast works");
  // if (*r == NULL) {
  //   *r = malloc(*a+1);
  // }
  // strncpy(*r,b,*a);
  // if (*a >= strlen(b)) {
  //   *r = strdup(b);
  //   //strcpy(*r, b);
  // } else {
  //   *r = strdup(b);
  *r = strdup(b);
  if (strlen(*r) > *a) {
    (*r)[*a] = 0;
  } else {
    //do nothing
  }
    //strncpy(*r, b, *a+1);
  
}

void merge_str (element_t* rv, element_t av, element_t bv) {
  char* a = (char*) av;  // a = *r
  char* b = (char*) bv;  // string
  char** r = (char**) rv;  // acc
  int total_strlen = strlen(*r) + strlen(b) + 2;
  *r = (char *) realloc(*r, total_strlen); 
  // char white_space[] = { " " };

  // if (a == NULL) {
  //   a = malloc(strlen(b)+1);
  // }
  // if (strlen(a) == 0) { // the first element
  //   //int total_strlen = strlen(a) + strlen(b) + 2; // 1 for '/0'
  //   //*r = (char *) realloc(*r, total_strlen); 
  //   printf("%s\n", *r); 
  //   printf("%s\n", *r); 
  //   printf("%s\n", b);
  //   //strcat(*r, b);
  // } else {
  //   //int total_strlen = strlen(a) + strlen(b) + 2; // 1 for space, 1 for '/0'
  //   //*r = (char *) realloc(*r, total_strlen); 
  //   strcat(*r, " ");
  //   //strcat(*r, b);
  // } //a bb cc
  if (strlen(*r)) {
    strcat(*r, " ");
  }
  strcat(*r, b);
}

void find_max (element_t* rv, element_t av, element_t bv) {
  int* a = (int*) av;  // a = *r = cur_max
  int* b = (int*) bv;  // number to cmp
  int **r = (int**) rv;  // cur_max
  if (*b >= *a) {
    **r = *b;
  } else {
    **r = *a;
  }
}

int main(int argc, char *argv[]) {
    
    // step 1
    int size = argc - 1;
    struct list *l0 = list_create(); 
    // l0: initial list (0 aa 1 bb cc 2)

    for (int i=0; i < size; i++) {
        element_t e = strdup(argv[i+1]);
        // element_t e = argv[i+1];
        list_append(l0, e);
    }
    
    // step 2
    struct list *l1 = list_create();
    list_map1(string_to_int, l1, l0); 
    // list_foreach(print,l1);
    // l1: int list (0 -1 1 -1 -1 2)
 
    // step 3
    struct list *l2 = list_create();
    list_map2(number_to_null, l2, l0, l1);
    // l2: str_null list: (null aa null bb cc null)

    // step 4
    struct list *l3 = list_create();
    list_filter(remove_negatives, l3, l1);
    // l3: remove_natives: (0 1 2)
    //list_foreach(print,l3);

    // step 5
    struct list *l4 = list_create();
    list_filter(remove_null, l4, l2);
    // l4: remove_null: (aa bb cc)
    // char *c;
    // *c = "test test";
    // printf("%s\n", c);
    // list_foreach(print_str,l4);
    

    // printf("works up to here\n");

    // step 6
    struct list *l5 = list_create();
    list_map2(my_trunc, l5, l3, l4);
    // list_foreach(print_str,l5);
    // l4: trunc_str: (a bb cc)

    // step 7
    list_foreach(print_str,l5);
    // list_foreach(print_str,l0);
    // list_foreach(print_str,l5);
    // list_foreach(print_str,l5);


    // step 8
    // if (l5->len == 0) {
    //   printf("\n");
    // } else {
    //   char* out = malloc(1);
    //   *out = '\0';
    //   list_foldl(merge_str, &out, l5);
    //   printf("%s", out);
    //   printf("\n");
    //   // char* first_str = malloc(strlen(l5->data[0]));
    //   // first_str = strdup(l5->data[0]);
    //   // list_foldl(merge_str, &first_str, l5);
    // }
    char* out = malloc(1);
    *out = 0;
    list_foldl(merge_str, (element_t *) &out, l5);
    printf("%s", out);
    printf("\n");

    // step 9
    int max = 0;
    int* max_pointer = &max;
    list_foldl(find_max,(element_t *) &max_pointer, l3);
    printf("%d\n", max);

    list_foreach (free, l0);  
    list_foreach (free, l1); 
    list_foreach (free, l2); 
    //list_foreach (free, l3);  
    //list_foreach (free, l4); 
    list_foreach (free, l5); // for some 
    // step 10
    list_destroy (l0);
    list_destroy (l1);
    list_destroy (l2);
    list_destroy (l3);
    list_destroy (l4);
    list_destroy (l5);   
    free(out);

    return 1;
}