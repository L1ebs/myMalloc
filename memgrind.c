#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "mymalloc.c"

#define RUNS 50
#define LOOPS 120

void task1(int display) {
    int i;
    if(display){
    check_memory();
    print_memory();}
    for (i = 0; i < LOOPS; i++) {
            char *p = (char *)malloc(1);
            if(display){
                check_memory();
                print_memory();
            }
            free(p);
            if(display){
                check_memory();
                print_memory();
            }
        
    }
}

void task2(int display){
    if(display){
    check_memory();
    print_memory();}
    int i, j;
    char *array[LOOPS];
    for (i = 0; i < LOOPS; i++) {
        
        array[i] = (char *)malloc(1);
        if(display){
            check_memory();
            print_memory();}
    }
    for (j = 0; j < LOOPS; j++) {
        free(array[j]);
        if(display){
            check_memory();
            print_memory();}
    }
}

void task3(int display) {
    if(display){
        check_memory();
        print_memory();
    }
    int i, j;
    int mallocs = 0;
    int frees = 0;
    char *array[LOOPS];
    for (i = 0; i < LOOPS; i++) {
        //print_memory();
        int r = rand() % 2;
        if (r == 0 && mallocs < LOOPS) {
            array[mallocs] = (char *)malloc(1);
            if(display){
                check_memory();
                print_memory();
            }
            mallocs++;
        } else if (frees < mallocs) {
            free(array[frees]);
            if(display){
                check_memory();
                print_memory();
            }
            frees++;
        }
        //print_memory();
    }
    for (j = frees; j < mallocs; j++) {
        //print_memory();
        free(array[j]);
        if(display){
                check_memory();
                print_memory();
            }
        //print_memory();
    }
}
//Task 4: Allocate and free large chunks of memory

//allocate and free large chunks of memory, stressing the ability of your malloc and free functions
void task4(int display) {
    if(display){
                check_memory();
                print_memory();
            }
    int i;
    for (i = 0; i < LOOPS; i++) {
        char *p = (char *)malloc(1024*1024);
        if(display){
                check_memory();
                print_memory();
            }
        free(p);
        if(display){
                check_memory();
                print_memory();
            }
    }
}

//Task 5: Allocate and free memory in a random pattern
//allocate and free memory in a random pattern, stressing the ability of your malloc and free functions to handle arbitrary patterns of memory allocation and deallocation.
void task5(int display) {
    if(display){
        check_memory();
        print_memory();
    }
    int i, j;
    int mallocs = 0;
    int frees = 0;
    char *array[LOOPS];
    for (i = 0; i < LOOPS; i++) {
        int r = rand() % 2;
        if (r == 0 && mallocs < LOOPS) {
            array[mallocs] = (char *)malloc(rand() % 1024);
            if(display){
                check_memory();
                print_memory();
            }
            mallocs++;
        } else if (frees < mallocs) {
            free(array[frees]);
            if(display){
                check_memory();
                print_memory();
            }
            frees++;
        }
    }
    for (j = frees; j < mallocs; j++) {
        free(array[j]);
        if(display){
                check_memory();
                print_memory();
            }
    }
}



int main() {
    char input[100];
    int display_info = 0;
    printf("Do you want to display memory info?\nthis can greatly increase the time\nwill also show results of err.c\n(y/n): ");
    fgets(input, sizeof(input), stdin);
    if (strlen(input) == 2 && (input[0] == 'y' || input[0] == 'Y' || input[0] == 'n' || input[0] == 'N')) {
        display_info = (input[0] == 'y') || (input[0] == 'Y'); 
    } else {
        printf("Invalid input. Please enter 'y' or 'n'.\n");
        exit(1);
    }
    if(display_info){
        int result = system("gcc -o err err.c");
        for (int test = 1; test < 6; test++) {
            result=0;
            if (result == 0) {
                char command[50];
                sprintf(command, "./err %d", test);
                result = system(command);
            }
            printf("err %d result: %d\n", test, result);
        }
    }
    int i, j;
    struct timeval start, end;
    long task1_time[RUNS], task2_time[RUNS], task3_time[RUNS], task4_time[RUNS],task5_time[RUNS];
    for (i = 0; i < RUNS; i++) {
        gettimeofday(&start, NULL);
        for (j = 0; j < LOOPS; j++) {
            task1(display_info);
        }
        gettimeofday(&end, NULL);
        task1_time[i] = (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec);

        gettimeofday(&start, NULL);
        for (j = 0; j < LOOPS; j++) {
            task2(display_info);   
        }
        gettimeofday(&end, NULL);
        task2_time[i] = (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec);

        gettimeofday(&start, NULL);
        for (j = 0; j < LOOPS; j++) {
            task3(display_info);
            
        }
        gettimeofday(&end, NULL);
        task3_time[i] = (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec);

        gettimeofday(&start, NULL);
        for (j = 0; j < LOOPS; j++) {
            task4(display_info);
            
        }
        gettimeofday(&end, NULL);
        task4_time[i] = (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec);

        gettimeofday(&start, NULL);
        for (j = 0; j < LOOPS; j++) {
            task5(display_info);

        }
        gettimeofday(&end, NULL);
        task5_time[i] = (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec);
    }

    long task1_avg = 0;
    long task2_avg = 0;
    long task3_avg = 0;
    long task4_avg = 0;
    long task5_avg = 0;
    for (i = 0; i < RUNS; i++) {
        task1_avg += task1_time[i];
        task2_avg += task2_time[i];
        task3_avg += task3_time[i];
        task4_avg += task4_time[i];
        task5_avg += task5_time[i];
    }
    task1_avg /= RUNS;
    task2_avg /= RUNS;
    task3_avg /= RUNS;
    task4_avg /= RUNS;
    task5_avg /= RUNS;

    printf("Task 1: %ld microseconds\n", task1_avg);
    printf("Task 2: %ld microseconds\n", task2_avg);
    printf("Task 3: %ld microseconds\n", task3_avg);
    printf("Task 4: %ld microseconds\n", task4_avg);
    printf("Task 5: %ld microseconds\n", task5_avg);   
    check_memory();

    return 0;
}

