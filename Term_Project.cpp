#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 30

struct PERSON {
	int tag;
	char date[20];
	char fee_paid[10];
	char name[25];
	int age;
	char organ[35];
	char job[15];

};

void init(struct PERSON* p) {
	FILE* myInFile;
	int i = 0, j = 1, k = 0;
	char date[20];

	myInFile = fopen("registraion_data.txt", "r");

	if (myInFile == NULL) {
		printf("Could not open Be Opened!\n");
	}
	else {
		while (fscanf(myInFile, "%d/%[^/]/%[^/]/%[^/]/%d/%[^/]/%s", &p[i].tag, &p[i].date, &p[i].fee_paid, &p[i].name, &p[i].age, &p[i].organ, &p[i].job) != EOF) {
			i++;
		}

	}
	fclose(myInFile);

}
void main() {
	struct PERSON person[MAX];
	init(person);
}