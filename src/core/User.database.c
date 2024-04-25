//
// Created by hungt on 4/21/2024.
//

//
// Created by hungt on 4/21/2024.
//

//
// Created by hungt on 4/21/2024.
//

#include "User.database.h"

#define USERNAME_PREFIX "username: "
#define MAX_LINE_LENGTH 256



/*
 * ADD USER
 * */
void add_user(const char *filename, const User* user){
    if(search_user_by_username(filename, user->username, false)){
        printf("User already exists!\n");
        return;
    }

    FILE *file = fopen(filename, "a"); // Open for appending
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fprintf(file, "username: %s\n", user->username);
    fprintf(file, "password: %s\n", user->password);
    fprintf(file, "role: %s\n", "member");
    fprintf(file, "email: %s\n", user->email);
    fprintf(file, "phone: %s\n", user->phone);

    fclose(file);
}

/*
 * SEARCH USER
 * */

bool search_user_by_username(const char *filename, const char *usernameToSearch, bool printActive) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return false;
    }

    User user;
    char line[MAX_LINE_LENGTH];
    bool foundUser = false;

    while (fgets(line, sizeof(line), file)) {
        // Remove trailing newline character
        line[strcspn(line, "\n")] = 0;

        // Check if the line starts with the 'username' field
        if (strncmp(line, USERNAME_PREFIX, strlen(USERNAME_PREFIX)) == 0) {
            // Extract the username from the current line
            strcpy(user.username, line + strlen(USERNAME_PREFIX));

            // If the username matches, proceed to populate the rest of the fields
            if (strcmp(user.username, usernameToSearch) == 0) {
                if(printActive){
                    printf("%s\n", line); // Print username

                    // Read and print the rest of the user details
                    fgets(user.password, sizeof(user.password), file); printf("%s", user.password);
                    fgets(user.email, sizeof(user.email), file); printf("%s", user.email);
                    fgets(user.phone, sizeof(user.phone), file); printf("%s", user.phone);
                    fgets(user.role, sizeof(user.role), file); printf("%s", user.role);
                }
                foundUser = true;
                break;
            }
        }
    }

    fclose(file);

    if(printActive){
        if (!foundUser) {
            printf("User '%s' not found.\n", usernameToSearch);
        }
    }

    return foundUser;
}

/*
 * UPDATE USER
 * */

bool update_user(const char *filename, const char *username, User *updatedUserData, const char *fieldToUpdate) {
    printf("Updating user: %s\n", username);

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file for reading");
        return false;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (!tempFile) {
        perror("Error opening temporary file for writing");
        fclose(file);
        return false;
    }

    User currentUser;
    bool updated = false;
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (sscanf(buffer, "username: %s\n", currentUser.username) == 1 && strcmp(currentUser.username, username) == 0) {
            // Found the user to update
            updated = true;
            fgets(buffer, sizeof(buffer), file); // Read the password
            sscanf(buffer, "password: %s\n", currentUser.password);
            fgets(buffer, sizeof(buffer), file); // Read the phone
            sscanf(buffer, "phone: %s\n", currentUser.phone);

            // Update the necessary field
            if (strcmp(fieldToUpdate, "password") == 0) {
                strcpy(currentUser.password, updatedUserData->password);
            } else if (strcmp(fieldToUpdate, "phone") == 0) {
                strcpy(currentUser.phone, updatedUserData->phone);
            }

            // Write updated info
            fprintf(tempFile, "username: %s\npassword: %s\nphone: %s\n", currentUser.username, currentUser.password, currentUser.phone);
            continue;
        }
        // Write all other lines as is
        fputs(buffer, tempFile);
    }

    fclose(file);
    fclose(tempFile);

    if (updated) {
        // Commit changes by renaming files
        remove(filename);
        rename("temp.txt", filename);
        return true;
    } else {
        remove("temp.txt");
        return false;
    }
}

/*
 * REMOVE USER
 * */

int remove_user(const char *filename, const char *usernameToRemove) {

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file for reading");
        return -1;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (!tempFile) {
        perror("Error opening temporary file for writing");
        fclose(file);
        return -1;
    }

    char line[256];
    int found = 0;
    int skipSection = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, USERNAME_PREFIX)) {
            char *lineUsername = line + strlen(USERNAME_PREFIX);
            lineUsername[strcspn(lineUsername, "\n")] = 0; // Remove newline

            if (strcmp(lineUsername, usernameToRemove) == 0) {
                found = 1;
                skipSection = 1; // Begin skipping lines for this user
                continue; // Skip adding this line
            }
        }

        // If we encounter a blank line, it signifies the end of a user section
        if (strcmp(line, "\n") == 0) {
            skipSection = 0; // Stop skipping lines
        }

        // If not skipping, write the line to temp file
        if (!skipSection) {
            fprintf(tempFile, "%s", line);
        }
    }

    fclose(file);
    fclose(tempFile);

    // Remove and rename files based on whether the user was found
    if (found) {
        remove(filename);
        rename("temp.txt", filename);
        printf("User %s removed.\n", usernameToRemove);
    } else {
        remove("temp.txt"); // No need to keep temp file if no user was removed
        printf("User %s not found.\n", usernameToRemove);
    }
    return found ? 1 : 0;
}

//int login(const char *filename, const char *username, const char *password) {
//    FILE  *tokenFile = fopen("database/token.txt", "w");
//    if (!tokenFile) {
//        printf("Error opening token file!\n");
//        return 0; // Exit the function if the token file cannot be opened.
//    }
//    FILE *file = fopen(filename, "r");
//    if (file == NULL) {
//        printf("File could not be opened for reading.\n");
//        return 0;
//    }
//
//    User user;
//    char line[256];
//    int found = 0;
//
//    while (fgets(line, sizeof(line), file) != NULL) {
//        // Trim newline character
//        line[strcspn(line, "\r\n")] = 0;
//
//        // Matching line with username
//        if (strncmp(line, "username: ", 10) == 0) {
//            // Copy the username from the line by offsetting by 10 characters
//            strcpy(user.username, line + 10);
//
//            // Next line should be the password of this user
//            if (fgets(line, sizeof(line), file) != NULL) {
//                line[strcspn(line, "\r\n")] = 0;
//                // Ensure it is formatted as a password line
//                if (strncmp(line, "password: ", 10) == 0) {
//                    strcpy(user.password, line + 10);
//
//                    if (!strcmp(user.username, username) && !strcmp(user.password, password)) {
//                        // Collect potential additional details like role
//                        fgets(line, sizeof(line), file); // Assuming role is the next item
//                        line[strcspn(line, "\r\n")] = 0;
//                        if (strncmp(line, "role: ", 6) == 0) {
//                            strcpy(user.role, line + 6);
//                            printf("Login successful!\n");
//                            fprintf(tokenFile, "username: %s\nrole: %s\n", user.username, user.role);
//                            found = 1;
//                            break;
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//        if (!found) {
//            printf("Login faiiled!\n");
//        }
//
//
//    fclose(tokenFile);
//    fclose(file);
//    return found;
//}

bool read_user(FILE* file, User* user) {
    char line[256];
    bool hasUsername = false, hasPassword = false, hasRole = false;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\r\n")] = 0; // Remove newline characters

        if (strncmp(line, "username: ", 10) == 0) {
            strcpy(user->username, line + 10);
            hasUsername = true;
        } else if (strncmp(line, "password: ", 10) == 0) {
            strcpy(user->password, line + 10);
            hasPassword = true;
        } else if (strncmp(line, "role: ", 6) == 0) {
            strcpy(user->role, line + 6);
            hasRole = true;
        }

        // Check if all necessary data is gathered to complete user reading
        if (hasUsername && hasPassword && hasRole) {
            break;  // Exit once all required data is read
        }
    }

    // Return true only if all necessary fields are read
    return hasUsername && hasPassword && hasRole;
}

int login(const char *filename, const char *username, const char *password) {
    FILE *tokenFile = fopen("database/token.txt", "w");
    if (!tokenFile) {
        perror("Error opening token file\n");
        return 0;
    }
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("File could not be opened for reading\n");
        fclose(tokenFile);
        return 0;
    }

    User user;
    bool found = false;

    while (read_user(file, &user)) {
        if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0) {
            printf("Login successful!\n");
            fprintf(tokenFile, "username: %s\nrole: %s\n", user.username, user.role);
            found = true;
            break;
        }
    }

    if (!found) {
        printf("Login failed!\n");
    }

    fclose(tokenFile);
    fclose(file);
    return found ? 1 : 0;
}







