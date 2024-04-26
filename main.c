////
//// Created by hungt on 4/21/2024.
////

#include <stdio.h>
#include <stdbool.h>
#include "System.h"
#include "stdlib.h"

#include "src/core/Staff.database.h"

int main(){
      srand(time(NULL));
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
DateWork dateWork = {
        .username = "1234",
        .date = {
                .year = 2024,
                .month = 4,
                .day = 25,
        },
        .time = 30,
        .status = 0,
        .paid = 10.00
};
    //updateDateWork("database/datework.txt","93e41c6e-2091-41b9-b36b-c7ce94edc677", &dateWork, "time");

    addDateWork("database/datework.txt",&dateWork);
    return 0;
}
