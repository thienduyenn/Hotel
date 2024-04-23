//
// Created by THIEN DUYEN on 4/23/2024.
//

#ifndef FILEUTILSV2_ADMIN_DATABASE_H
#define FILEUTILSV2_ADMIN_DATABASE_H

#include <stdbool.h>
#include "entity/admin.h"
#include "entity/staff.h"

bool AdminLogin(char *username, char *password);

void getAllStaffs(struct Staff *listStaff, int *numberStaff);

#endif //FILEUTILSV2_ADMIN_DATABASE_H
