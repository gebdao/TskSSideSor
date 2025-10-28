#include "Database.h"
#include <iostream>
#include <mysql/mysql.h>
#include <windows.h>
#include "Shengming.h" // Fișierul pentru citirea din INI
#include "MainApp.h"

void AddItemToDatabase(int playerID, int itemVNUM, int quantity, int equipInfo) {
	if (playerID <= 0) {
		std::cerr << "Invalid player ID" << std::endl;
		return;  // Nu insera în baza de date dacă playerID este invalid
	}

	// Citirea valorilor de conexiune din LoginInfo.ini
	char db_host[100], db_user[100], db_password[100], db_name[100];
	int db_port;

	GetPrivateProfileStringA("LOGININFO", "mDB_1_IP", "", db_host, sizeof(db_host), "CONFIG\\LoginInfo.ini");
	GetPrivateProfileStringA("LOGININFO", "mDB_1_ID", "", db_user, sizeof(db_user), "CONFIG\\LoginInfo.ini");
	GetPrivateProfileStringA("LOGININFO", "mDB_1_PASSWORD", "", db_password, sizeof(db_password), "CONFIG\\LoginInfo.ini");
	db_port = GetPrivateProfileInt("LOGININFO", "mDB_1_PORT", 3306, "CONFIG\\LoginInfo.ini");

	// Crează conexiune la baza de date
	MYSQL* conn;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, db_host, db_user, db_password, db_name, db_port, NULL, 0);

	if (conn) {
		// Comanda SQL
		std::string query = "INSERT INTO player_items (player_id, item_vnum, quantity, equip_info) "
			"VALUES (" + std::to_string(playerID) + ", " + std::to_string(itemVNUM) + ", "
			+ std::to_string(quantity) + ", " + std::to_string(equipInfo) + ")";

		// Execută query-ul
		if (mysql_query(conn, query.c_str())) {
			std::cerr << "Failed to insert item: " << mysql_error(conn) << std::endl;
		}
		else {
			std::cout << "Item inserted successfully!" << std::endl;
		}
		mysql_close(conn);
	}
	else {
		std::cerr << "Database connection failed: " << mysql_error(conn) << std::endl;
	}
}
