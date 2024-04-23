//
// Created by hungt on 4/21/2024.
//

#include <stdio.h>
#include "System.h"
#include <stdbool.h>
#include "src/core/Admin.database.h"
#include "src/core/Staff.database.h"



int main(){
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
    struct Staff newStaff = {6,"td","5858", "manager",8500};
    if(registerStaff(newStaff)) {
           printf(" Regisfekjge");
    }else{
           printf("fkyfagye");
    }
    return 0;
}