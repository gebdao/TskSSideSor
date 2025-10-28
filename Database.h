#pragma once
#ifndef DATABASE_H
#define DATABASE_H

#include <mysql/mysql.h>

void AddItemToDatabase(int playerID, int itemVNUM, int quantity, int equipInfo);

#endif // DATABASE_H
