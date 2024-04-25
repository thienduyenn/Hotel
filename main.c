////
//// Created by hungt on 4/21/2024.
////

#include <stdio.h>
#include <stdbool.h>
#include "System.h"
#include "stdlib.h"

#include "src/core/Staff.database.h"

int main(){
//    srand(time(NULL));
//    bool exit = false;
//
//    while(!exit){
//        char option;
//        printf("Your option:");
//        scanf("%s", &option);
//        printf("-----------\n");
//
//
//        exit = Choose(option);
//    }

    float salary = 0;
    calculateSalary("database/dateWork.txt", "TD", &salary);
    printf("Salary: %f", salary);
    return 0;
}
