////
//// Created by THIEN DUYEN on 4/23/2024.
////

#ifndef FILEUTILSV2_STAFF_DATABASE_H
#define FILEUTILSV2_STAFF_DATABASE_H

#include <stdbool.h>
#include "User.database.h"
#include "../utils/Date.h"

typedef struct {
    char uuid[85];
    char username[85];
    Date date;
    int time;
    bool status;
    float paid;
} DateWork;


bool assignRole(const char *filename, const char *username, User *newUser, const char *role);
bool getAllUser(const char *filename, User *listUsers, int *size);

bool addDateWork(char *filename, DateWork *dateWork);
bool updateDataWork(const char *filename, const char *username, DateWork *dateWork, const char *fieldToUpdate);

bool getAllDateWorks(const char *filename, DateWork *listDateWorks, int *size);
bool searchDateWorkByUsername(const char *filename, const char *username, DateWork *listDateWorks, int *size);

bool calculateSalary(const char *filename, const char *username, float *salary, int month, int year);

#endif //FILEUTILSV2_STAFF_DATABASE_H
