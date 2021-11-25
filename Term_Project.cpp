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

void init(struct PERSON* p, char* string, int* count) { // initialize file
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

void linking(struct PERSON* p, int count) { // linking the struct
	for (int i = 0; i < count; i++) {
		struct PERSON* p = NULL;
		p = (struct PERSON*)malloc(sizeof(struct PERSON));
		p->next = p + 1;
	}
}

int string_check(char* a, char* b) { // I use string_check because of Choi
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

void search_in_array(struct PERSON* p, int count, char* check, char* string) {
	for (int i = 0; i < count; i++) { // p 1-1
		if ((string_check(p[i].name, string)) == 1 && (strcmp(check, "name")) == 0) {
			printf("%d/%s/%s/%s/%d/%s/%s\n", p[i].tag, p[i].date, p[i].fee_paid, p[i].name, p[i].age, p[i].organ, p[i].job);
		}
		else if ((string_check(p[i].organ, string)) == 1 && (strcmp(check, "organ")) == 0) { // p 2-1
			printf("%d/%s/%s/%s/%d/%s/%s\n", p[i].tag, p[i].date, p[i].fee_paid, p[i].name, p[i].age, p[i].organ, p[i].job);
		}
	}
}

void search_in_linked_list(struct PERSON* p, int count, char* check, char* string) {
	for (int i = 0; i < count; i++) { // p 1-2
		if ((string_check(p[i].name, "Choi")) == 1 && (strcmp(check, "name")) == 0) {
			printf("%d/%s/%s/%s/%d/%s/%s\n", p[i].tag, p[i].date, p[i].fee_paid, p[i].name, p[i].age, p[i].organ, p[i].job);
		}
		else if ((string_check(p[i].organ, "Gachon University")) == 1 && (strcmp(check, "organ")) == 0) { // p 2-2
			printf("%d/%s/%s/%s/%d/%s/%s\n", p[i].tag, p[i].date, p[i].fee_paid, p[i].name, p[i].age, p[i].organ, p[i].job);
		}
		p->next = p + 1;
	}
}


void main() {
	struct PERSON person[MAX];
	int count;

	init(person, "registraion_data.txt", &count);

	linking(person, count);

	printf("p1-1=============================================================\n\n");
	search_in_array(person, count, "name", "Choi");

	printf("\np1-2=============================================================\n\n");
	search_in_linked_list(person, count, "name", "Choi");

	printf("\np2-1=============================================================\n\n");
	search_in_array(person, count, "organ", "Gachon University");

	printf("\np2-2=============================================================\n\n");
	search_in_linked_list(person, count, "organ", "Gachon University");
}