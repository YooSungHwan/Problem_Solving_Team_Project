#define _CRT_SECURE_NO_WARNINGS
#define MAX 100
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct PERSON {
    int tag;
    char date[20];
    char fee_paid[10];
    char name[25];
    int age;
    char organ[35];
    char job[15];
    struct PERSON* next;
};

void init(struct PERSON* p, const char* string, int* count) { // initialize file
    FILE* myInFile;
    int i = 0;

    myInFile = fopen(string, "r");

    if (myInFile == NULL) {
        printf("Could not open Be Opened!\n");
    }
    else {
        while (fscanf(myInFile, "%d/%[^/]/%[^/]/%[^/]/%d/%[^/]/%s", &p[i].tag, &p[i].date, &p[i].fee_paid, &p[i].name, &p[i].age, &p[i].organ, &p[i].job) != EOF) {
            i++;
        }
        *count = i;
    }
    fclose(myInFile);

}

void copy(struct PERSON* newNode, struct PERSON* p) { // linking the struct
    newNode->tag = p->tag;
    strcpy(newNode->date, p->date);
    strcpy(newNode->fee_paid, p->fee_paid);
    strcpy(newNode->name, p->name);
    newNode->age = p->age;
    strcpy(newNode->organ, p->organ);
    strcpy(newNode->job, p->job);
}

struct PERSON* linking(struct PERSON* head, struct PERSON* node, int num) {
    for (int i = 0; i < num; i++) {
        node = node->next;
    }

    node->next = NULL;
    node->next = (struct PERSON*)malloc(sizeof(struct PERSON));

    copy(node, head + num);
    return node;
}

void print_a(struct PERSON* p, int start, int end) {
    if (start == end) {
        printf("%d/%s/%s/%s/%d/%s/%s\n", p[start].tag, p[start].date, p[start].fee_paid, p[start].name, p[start].age, p[start].organ, p[start].job);
    }
    for (int i = start; i < end; i++) {
        printf("%d/%s/%s/%s/%d/%s/%s\n", p[i].tag, p[i].date, p[i].fee_paid, p[i].name, p[i].age, p[i].organ, p[i].job);
    }
}

int string_check1(const char* a, const char* b) { // I use string_check because of Choi
    int j = 0;
    for (int i = 0; a[i] != '\0'; i++) {
        if (a[i] == b[j])
            j++;
        else
            j = 0;
        if (strlen(b) == j)
            return 1;
    }
    return 0;
}

void search_in_array(struct PERSON* p, int count, const char* check, const char* string) {
    for (int i = 0; i < count; i++) { // p 1-1
        if ((string_check1(p[i].name, string)) == 1 && (strcmp(check, "name")) == 0) {
            print_a(p, i, i);
        }
        else if ((string_check1(p[i].organ, string)) == 1 && (strcmp(check, "organ")) == 0) { // p 2-1
            print_a(p, i, i);
        }
    }
}

void search_in_linked_list(struct PERSON* p, int count, const char* check, const char* string) {// p 1-2
    if ((string_check1(p->name, string)) == 1 && (strcmp(check, "name")) == 0) {
        printf("%d/%s/%s/%s/%d/%s/%s\n", p->tag, p->date, p->fee_paid, p->name, p->age, p->organ, p->job);
    }
    else if ((string_check1(p->organ, string)) == 1 && (strcmp(check, "organ")) == 0) { // p 2-2
        printf("%d/%s/%s/%s/%d/%s/%s\n", p->tag, p->date, p->fee_paid, p->name, p->age, p->organ, p->job);
    }
}

void swap(struct PERSON* a, struct PERSON* b) {
    struct PERSON tmp = *a; // p 3-1
    *a = *b;
    *b = tmp;
}


void sort_in_array(struct PERSON* a, int count) {
    int i, j;  // p 3-1

    for (i = 0; i < count - 1; i++) {
        for (j = count - 1; j > i; j--) {
            if (a[j - 1].tag > a[j].tag)
                swap(&a[j - 1], &a[j]);
        }
    }
    print_a(a, 0, count);
}

int main(void) {
    struct PERSON person[MAX];
    struct PERSON* ps = NULL;
    struct PERSON* list = (struct PERSON*)malloc(sizeof(struct PERSON));
    ps = (struct PERSON*)malloc(sizeof(struct PERSON));
    int count;

    init(person, "registraion_data.txt", &count);

    printf("p1-1=============================================================\n\n");
    search_in_array(person, count, "name", "Choi");

    printf("\np1-2=============================================================\n\n");
    for (int i = 0; i < count; i++) {
        list = linking(person, ps, i);
        search_in_linked_list(list, count, "name", "Choi");
    }
    printf("\np2-1=============================================================\n\n");
    search_in_array(person, count, "organ", "Gachon University");
    printf("\np2-2=============================================================\n\n");
    for (int i = 0; i < count; i++) {
        list = linking(person, ps, i);
        search_in_linked_list(list, count, "organ", "Gachon University");
    }
    printf("\np3-1=============================================================\n\n");
    sort_in_array(person, count);
    printf("\np4-1=============================================================\n\n");
    for (int i = 0; i < count; i++) {
        list = linking(person, ps, i);
        printf("%d/%s/%s/%s/%d/%s/%s\n", list->tag, list->date, list->fee_paid, list->name, list->age, list->organ, list->job);
    }
}
