//
// Created by THIEN DUYEN on 4/23/2024.
//

#include "Admin.database.h"
#include <string.h>
#include <stdio.h>

bool ReadFromFileStaff(char *filename, struct Staff *listStaff, int *numberStaff) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return false;
    }
    while (!feof(file)) {
        struct Staff staff;
        fscanf(file, "%d", &staff.id);
        fscanf(file, "%s", staff.username);
        fscanf(file, "%s", staff.password);
        fscanf(file, "%s", staff.role);
        fscanf(file, "%f", &staff.salary);
        listStaff[*numberStaff] = staff;
        *numberStaff += 1;
    }
    return true;
}

bool AdminLogin(char *username, char *password){
    if (strcmp(username, "TD") == 0 && strcmp(password, "123") ==0) {
        return true;
    }
    return false;
}

void getAllStaffs(struct Staff *listStaff, int *numberStaff){
    ReadFromFileStaff("database/staff.txt", listStaff, numberStaff);

}