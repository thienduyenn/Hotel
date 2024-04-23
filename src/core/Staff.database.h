//
// Created by THIEN DUYEN on 4/23/2024.
//

#ifndef FILEUTILSV2_STAFF_DATABASE_H
#define FILEUTILSV2_STAFF_DATABASE_H

#include <stdbool.h>
#include "entity/staff.h"


int loginStaff(char *username, char *password);
bool registerStaff(struct Staff newStaff);

#endif //FILEUTILSV2_STAFF_DATABASE_H
