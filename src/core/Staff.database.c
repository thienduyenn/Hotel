//
// Created by THIEN DUYEN on 4/25/2024.
//
#include "Staff.database.h"
#include"../utils/generateUUID.h"

#define USERNAME_PREFIX "username: "
#define MAX_LINE_LENGTH 256


bool assignRole(const char *filename, const char *username, User *newUser, const char *role) {
    if (!update_user(filename, username, newUser, "role")) {
        return false;
    }
    return true;

}

bool getAllUser(const char *filename, User *listUsers, int *size) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return false;
    }

    User user;
    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), file)) {
        // Remove trailing newline character
        line[strcspn(line, "\n")] = 0;

        // Check if the line starts with the 'username' field
        if (strncmp(line, USERNAME_PREFIX, strlen(USERNAME_PREFIX)) == 0) {
            // Extract the username from the current line
            strcpy(user.username, line + strlen(USERNAME_PREFIX));

            // If the username matches, proceed to populate the rest of the fields


            // Read and print the rest of the user details
            fgets(user.password, sizeof(user.password), file);

            fgets(user.email, sizeof(user.email), file);

            fgets(user.phone, sizeof(user.phone), file);

            fgets(user.role, sizeof(user.role), file);

            listUsers[*size] = user;
            *size += 1;
        }
    }

    fclose(file);

    return true;
}
bool addDateWork( char *filename,  DateWork *dateWork){
    FILE *file = fopen(filename, "a");
    if (file == NULL){
        printf(" Can't open file\n ");
        return false;
    }

    generate_uuid(dateWork->uuid);

    fprintf(file, "%s, ", dateWork -> uuid);
    fprintf(file, "%s, ", dateWork ->username);
    fprintf(file, "%d-%d-%d,", dateWork->date.year, dateWork->date.month, dateWork->date.day);
    fprintf(file,"%d, ", dateWork->time);
    fprintf(file,"%d, ", dateWork->status);
    fprintf(file,"%.2f\n", dateWork->paid);

    fclose(file);
    return true;
}
bool updateDataWork(const char  *filename, const char *username, DateWork *dataWork, const char *fieldToUpdate){

;}

bool calculateSalary(const char *filename, const char *username, float *salary) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf(" Can't open file\n ");
        return false;
    }
    DateWork dateWork;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,], %[^,], %d-%d-%d, %d, %d, %f",
               dateWork.uuid, dateWork.username,
               &dateWork.date.year, &dateWork.date.month, &dateWork.date.day,
               &dateWork.time, &dateWork.status, &dateWork.paid);

        if (strcmp(dateWork.username, username) == 0) {
            *salary += dateWork.paid *(float)dateWork.time;
        }
    }
    fclose(file);
    return true;
}
