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

void linking(struct PERSON* head, struct PERSON* node, int num) {
    for (int i = 0; i < num; i++) {
        node = node->next;
    }

    node->next = NULL;
    node->next = (struct PERSON*)malloc(sizeof(struct PERSON));

    copy(node, head + num);
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
    for (int i = 0; i < count; i++) {
        if ((string_check1(p->name, string)) == 1 && (strcmp(check, "name")) == 0) {
            printf("%d/%s/%s/%s/%d/%s/%s\n", p->tag, p->date, p->fee_paid, p->name, p->age, p->organ, p->job);
        }
        else if ((string_check1(p->organ, string)) == 1 && (strcmp(check, "organ")) == 0) { // p 2-2
            printf("%d/%s/%s/%s/%d/%s/%s\n", p->tag, p->date, p->fee_paid, p->name, p->age, p->organ, p->job);
        }
        p = p->next;
    }
}

void swap(struct PERSON* a, struct PERSON* b) {
    struct PERSON tmp = *a; // p 3-1
    *a = *b;
    *b = tmp;
}

void sort_in_array_c(struct PERSON* a, int count) {
    int i, j;  // p 3-1

    for (i = 0; i < count - 1; i++) {
        for (j = count - 1; j > i; j--) {
            if (a[j - 1].tag > a[j].tag)
                swap(&a[j - 1], &a[j]);
        }
    }

}

void sort_in_array_p(struct PERSON* a, int count) {
    sort_in_array_c(a, count);
    print_a(a, 0, count);
}

void selection_sort(struct PERSON* p, int count) {
    int i, j, minIndex;                 // p 5-1
    for (i = 0; i < count - 1; i++) {
        minIndex = i;
        for (j = i + 1; j < count; j++) {
            if (p[j].age < p[minIndex].age)
                minIndex = j;
        }
        swap(&p[i], &p[minIndex]);
    }
}
void grouping(struct PERSON* p, int count, int step, int start, int end, const char* name) {
    int j, i;                                       // p 5-1
    FILE* myFile;
    myFile = fopen(name, "w");

    if (myFile == NULL) {
        printf("Could not open Be Opened %s!\n", name);
    }
    for (j = start; j < end; j += step) {
        fprintf(myFile, "\n%d(%d-%d) \n", j, j, j + step - 1);
        for (i = 0; i < count; i++) {
            if (p[i].age >= j && p[i].age < (j + step)) {
                fprintf(myFile, "%d/%s/%s/%s/%d/%s/%s\n", p[i].tag, p[i].date, p[i].fee_paid, p[i].name, p[i].age, p[i].organ, p[i].job);
            }
        }
    }
    printf("Update Clear\n");
    fclose(myFile);
}

void delete_in_array(struct PERSON* p, int* count, const char* check, const char* string) {  // 6-1
    int j;
    int a = *count;
    bool t = true;
    for (int i = 0; i < a; i++) {
        if (t == false) {
            i--;
            t = true;
        }
        if ((string_check1(p[i].name, string)) == 1 && (strcmp(check, "name")) == 0) {
            for (j = i; j < a; j++) {
                p[j] = p[j + 1];
                p[j].tag -= 1;
            }
            a--;
            t = false;
        }
    }
    print_a(p, 0, a);
    *count = a;
}

void tagadd(struct PERSON* p, int* count, int newtag, const char* newDate, const char* newFee_paid, const char* newName, int newAge, const char* newOrgan, const char* newjob) {
    struct PERSON newPerson;
    int i, j, c = *count;
    bool b = true;

    newPerson.tag = newtag;
    strcpy(newPerson.date, newDate);
    strcpy(newPerson.fee_paid, newFee_paid);
    strcpy(newPerson.name, newName);
    newPerson.age = newAge;
    strcpy(newPerson.organ, newOrgan);
    strcpy(newPerson.job, newjob);

    for (i = 0; i < c; i++) {
        if (p[i].tag == newtag && b) {
            c++;
            for (j = c; j > i; j--) {
                p[j] = p[j - 1];
            }
            p[i] = newPerson;
            b = false;
            break;
        }
    }

    if (i == c && b) {
        c++;
        p[i] = newPerson;
    }

    for (i += 1; i < c; i++) {
        p[i].tag += 1;
    }
    print_a(p, 0, c);
    *count = c;
}

void linking_print(struct PERSON* p, struct PERSON* node, int count) {
    for (int i = 0; i < count; i++) {
        linking(p, node, i);
    }
    for (int i = 0; i < count; i++) {
        printf("%d/%s/%s/%s/%d/%s/%s\n", node->tag, node->date, node->fee_paid, node->name, node->age, node->organ, node->job);
        node = node->next;
    }
}

void recentarr(struct PERSON* p, const char* fileName, int count, int arrnum) {
    FILE* copyFile;

    copyFile = fopen(fileName, "w");

    for (int i = 0; i < arrnum; i++) {
        fprintf(copyFile, "%d/%s/%s/%s/%d/%s/%s\n", p[count - i - 1].tag, p[count - i - 1].date, p[count - i - 1].fee_paid, p[count - i - 1].name, p[count - i - 1].age, p[count - i - 1].organ, p[count - i - 1].job);
    }

    fclose(copyFile);
}

int checkSum(struct PERSON* p, int arrnum, int count, int divide) {
    int check = 0;

    if (divide) {
        for (int i = 0; i < arrnum; i++) {
            int j = 0;
            int sum = 0;
            while (p[i].name[j]) {
                sum += p[i].name[j];
                j++;
            }
            check ^= sum;
        }
    }
    else {
        for (int i = 0; i < arrnum; i++) {
            int j = 0;
            int sum = 0;
            while (p[count - i - 1].name[j]) {
                sum += p[count - i - 1].name[j];
                j++;
            }
            check ^= sum;
        }
    }
    return check;
}


void checksumFile(int checksum, const char* fileName) {
    FILE* checksumF;

    checksumF = fopen(fileName, "w");

    fprintf(checksumF, "original checksum result = %d", checksum);

    fclose(checksumF);
}

int read_copy_checksum(const char* fileName, int arrnum, int count, int divide) {
    FILE* copyFile;
    struct PERSON p[MAX];
    int i = 0;

    copyFile = fopen(fileName, "r");

    if (copyFile == NULL) {
        printf("error");
    }

    while (fscanf(copyFile, "%d/%[^/]/%[^/]/%[^/]/%d/%[^/]/%s", &p[i].tag, &p[i].date, &p[i].fee_paid, &p[i].name, &p[i].age, &p[i].organ, &p[i].job) != EOF) {
        i++;
    }

    fclose(copyFile);
    return checkSum(p, arrnum, count, divide);
}

void checksum_check(int original, int copy) {
    if (original == copy) {
        printf("copy success");
    }
    else {
        printf("copy failed");
    }
}

int main(void) {
    struct PERSON person[MAX];
    struct PERSON* ps = (struct PERSON*)malloc(sizeof(struct PERSON));
    int count, newtag;

    init(person, "registraion_data.txt", &count);
    for (int i = 0; i < count; i++) {
        linking(person, ps, i);
    }
    printf("p1-1=============================================================\n\n");
    search_in_array(person, count, "name", "Choi");

    printf("\np1-2=============================================================\n\n");
    search_in_linked_list(ps, count, "name", "Choi");

    printf("\np2-1=============================================================\n\n");
    search_in_array(person, count, "organ", "Gachon University");

    printf("\np2-2=============================================================\n\n");
    search_in_linked_list(ps, count, "organ", "Gachon University");

    printf("\np3-1=============================================================\n\n");
    sort_in_array_p(person, count);

    printf("\np4-1=============================================================\n\n");
    linking_print(person, ps, count);

    printf("\np5-1=============================================================\n\n");
    selection_sort(person, count); #define _CRT_SECURE_NO_WARNINGS
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

    void linking(struct PERSON* head, struct PERSON* node, int num) {
        for (int i = 0; i < num; i++) {
            node = node->next;
        }

        node->next = NULL;
        node->next = (struct PERSON*)malloc(sizeof(struct PERSON));

        copy(node, head + num);
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
        for (int i = 0; i < count; i++) {
            if ((string_check1(p->name, string)) == 1 && (strcmp(check, "name")) == 0) {
                printf("%d/%s/%s/%s/%d/%s/%s\n", p->tag, p->date, p->fee_paid, p->name, p->age, p->organ, p->job);
            }
            else if ((string_check1(p->organ, string)) == 1 && (strcmp(check, "organ")) == 0) { // p 2-2
                printf("%d/%s/%s/%s/%d/%s/%s\n", p->tag, p->date, p->fee_paid, p->name, p->age, p->organ, p->job);
            }
            p = p->next;
        }
    }

    void swap(struct PERSON* a, struct PERSON* b) {
        struct PERSON tmp = *a; // p 3-1
        *a = *b;
        *b = tmp;
    }

    void sort_in_array_c(struct PERSON* a, int count) {
        int i, j;  // p 3-1

        for (i = 0; i < count - 1; i++) {
            for (j = count - 1; j > i; j--) {
                if (a[j - 1].tag > a[j].tag)
                    swap(&a[j - 1], &a[j]);
            }
        }

    }

    void sort_in_array_p(struct PERSON* a, int count) {
        sort_in_array_c(a, count);
        print_a(a, 0, count);
    }

    void selection_sort(struct PERSON* p, int count) {
        int i, j, minIndex;                 // p 5-1
        for (i = 0; i < count - 1; i++) {
            minIndex = i;
            for (j = i + 1; j < count; j++) {
                if (p[j].age < p[minIndex].age)
                    minIndex = j;
            }
            swap(&p[i], &p[minIndex]);
        }
    }
    void grouping(struct PERSON* p, int count, int step, int start, int end, const char* name) {
        int j, i;                                       // p 5-1
        FILE* myFile;
        myFile = fopen(name, "w");

        if (myFile == NULL) {
            printf("Could not open Be Opened %s!\n", name);
        }
        for (j = start; j < end; j += step) {
            fprintf(myFile, "\n%d(%d-%d) \n", j, j, j + step - 1);
            for (i = 0; i < count; i++) {
                if (p[i].age >= j && p[i].age < (j + step)) {
                    fprintf(myFile, "%d/%s/%s/%s/%d/%s/%s\n", p[i].tag, p[i].date, p[i].fee_paid, p[i].name, p[i].age, p[i].organ, p[i].job);
                }
            }
        }
        printf("Update Clear\n");
        fclose(myFile);
    }

    void delete_in_array(struct PERSON* p, int* count, const char* check, const char* string) {  // 6-1
        int j;
        int a = *count;
        bool t = true;
        for (int i = 0; i < a; i++) {
            if (t == false) {
                i--;
                t = true;
            }
            if ((string_check1(p[i].name, string)) == 1 && (strcmp(check, "name")) == 0) {
                for (j = i; j < a; j++) {
                    p[j] = p[j + 1];
                    p[j].tag -= 1;
                }
                a--;
                t = false;
            }
        }
        print_a(p, 0, a);
        *count = a;
    }

    void tagadd(struct PERSON* p, int* count, int newtag, const char* newDate, const char* newFee_paid, const char* newName, int newAge, const char* newOrgan, const char* newjob) {
        struct PERSON newPerson;
        int i, j, c = *count;
        bool b = true;

        newPerson.tag = newtag;
        strcpy(newPerson.date, newDate);
        strcpy(newPerson.fee_paid, newFee_paid);
        strcpy(newPerson.name, newName);
        newPerson.age = newAge;
        strcpy(newPerson.organ, newOrgan);
        strcpy(newPerson.job, newjob);

        for (i = 0; i < c; i++) {
            if (p[i].tag == newtag && b) {
                c++;
                for (j = c; j > i; j--) {
                    p[j] = p[j - 1];
                }
                p[i] = newPerson;
                b = false;
                break;
            }
        }

        if (i == c && b) {
            c++;
            p[i] = newPerson;
        }

        for (i += 1; i < c; i++) {
            p[i].tag += 1;
        }
        print_a(p, 0, c);
        *count = c;
    }

    void linking_print(struct PERSON* p, struct PERSON* node, int count) {
        for (int i = 0; i < count; i++) {
            linking(p, node, i);
        }
        for (int i = 0; i < count; i++) {
            printf("%d/%s/%s/%s/%d/%s/%s\n", node->tag, node->date, node->fee_paid, node->name, node->age, node->organ, node->job);
            node = node->next;
        }
    }

    void recentarr(struct PERSON* p, const char* fileName, int count, int arrnum) {
        FILE* copyFile;

        copyFile = fopen(fileName, "w");

        for (int i = 0; i < arrnum; i++) {
            fprintf(copyFile, "%d/%s/%s/%s/%d/%s/%s\n", p[count - i - 1].tag, p[count - i - 1].date, p[count - i - 1].fee_paid, p[count - i - 1].name, p[count - i - 1].age, p[count - i - 1].organ, p[count - i - 1].job);
        }

        fclose(copyFile);
    }

    int checkSum(struct PERSON* p, int arrnum, int count, int num) {
        int check = 0;

        for (int i = 0; i < arrnum; i++) {
            int j = 0;
            int sum = 0;
            while (p[i + num].name[j]) {
                sum += p[i + num].name[j];
                j++;
            }
            check ^= sum;
        }
        return check;
    }


    void checksumFile(int checksum, const char* fileName) {
        FILE* checksumF;

        checksumF = fopen(fileName, "w");

        fprintf(checksumF, "original checksum result = %d", checksum);

        fclose(checksumF);
    }

    int read_copy_checksum(const char* fileName, int arrnum, int count, int num) {
        FILE* copyFile;
        struct PERSON p[MAX];
        int i = 0;

        copyFile = fopen(fileName, "r");

        if (copyFile == NULL) {
            printf("error");
        }

        while (fscanf(copyFile, "%d/%[^/]/%[^/]/%[^/]/%d/%[^/]/%s", &p[i].tag, &p[i].date, &p[i].fee_paid, &p[i].name, &p[i].age, &p[i].organ, &p[i].job) != EOF) {
            i++;
        }

        fclose(copyFile);
        return checkSum(p, arrnum, count, num);
    }

    void checksum_check(int original, int copy) {
        if (original == copy) {
            printf("copy success");
        }
        else {
            printf("copy failed");
        }
    }

    int main(void) {
        struct PERSON person[MAX];
        struct PERSON* ps = (struct PERSON*)malloc(sizeof(struct PERSON));
        int count, newtag;

        init(person, "registraion_data.txt", &count);
        for (int i = 0; i < count; i++) {
            linking(person, ps, i);
        }
        printf("p1-1=============================================================\n\n");
        search_in_array(person, count, "name", "Choi");

        printf("\np1-2=============================================================\n\n");
        search_in_linked_list(ps, count, "name", "Choi");

        printf("\np2-1=============================================================\n\n");
        search_in_array(person, count, "organ", "Gachon University");

        printf("\np2-2=============================================================\n\n");
        search_in_linked_list(ps, count, "organ", "Gachon University");

        printf("\np3-1=============================================================\n\n");
        sort_in_array_p(person, count);

        printf("\np4-1=============================================================\n\n");
        linking_print(person, ps, count);

        printf("\np5-1=============================================================\n\n");
        selection_sort(person, count);
        grouping(person, count, 10, 10, 80, "P5-1.txt");

        printf("\np6-1=============================================================\n\n");
        sort_in_array_c(person, count);
        delete_in_array(person, &count, "name", "Choi");

        printf("\np6-2=============================================================\n\n");
        linking_print(person, ps, count);

        printf("\np7-1=============================================================\n\n");
        printf("Enter Paik's tag: ");
        scanf("%d", &newtag);
        tagadd(person, &count, newtag, "2021-11-30", "yes", "Gildong Paik", 35, "Gachon University", "Student");

        printf("\np7-2=============================================================\n\n");
        linking_print(person, ps, count);

        printf("\np8=============================================================\n\n");
        recentarr(person, "P8-1.txt", count, 10);
        checksumFile(checkSum(person, 10, count, 0), "P8-2.txt");
        checksum_check(read_copy_checksum("P8-1.txt", 10, count, 0), checkSum(person, 10, count, count - 10));
    }
    grouping(person, count, 10, 10, 80, "P5-1.txt");

    printf("\np6-1=============================================================\n\n");
    sort_in_array_c(person, count);
    delete_in_array(person, &count, "name", "Choi");

    printf("\np6-2=============================================================\n\n");
    linking_print(person, ps, count);

    printf("\np7-1=============================================================\n\n");
    printf("Enter Paik's tag: ");
    scanf("%d", &newtag);
    tagadd(person, &count, newtag, "2021-11-30", "yes", "Gildong Paik", 35, "Gachon University", "Student");

    printf("\np7-2=============================================================\n\n");
    linking_print(person, ps, count);

    printf("\np8=============================================================\n\n");
    recentarr(person, "P8-1.txt", count, 10);
    checksumFile(checkSum(person, 10, count, 0), "P8-2.txt");
    checksum_check(read_copy_checksum("P8-1.txt", 10, count, 1), checkSum(person, 10, count, 0));
}