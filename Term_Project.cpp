#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 30

struct PERSON {
	int tag;
	char date[30];
	char fee_paid[10];
	char name[25];
	int age;
	char organ[35];
	char job[15];

};

void init(struct PERSON* p) {
	FILE* myInFile;
	myInFile = fopen("registraion_data.txt", "r");
	if (myInFile == NULL) {
		printf("Could not open Be Opened!\n");
	}
	else {
		for (int i = 0; i < MAX; i++) {
			fscanf(myInFile, "%d", &p[i].tag);
			fgetc(myInFile);
			fgets(p[i].date, sizeof(20), myInFile);
			fgets(p[i].fee_paid, sizeof(10), myInFile);

			printf("%d %s %s\n", p[i].tag, p[i].date,p[i].fee_paid);
		}
	}
	fclose(myInFile);

}
void main() {
	struct PERSON person[MAX];
	init(person);
}