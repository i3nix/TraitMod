#pragma once
#include <mysqlx/xdevapi.h>

#define TM_DEFAULT_MYSQL_HOST "localhost"
#define TM_DEFAULT_MYSQL_PORT 33060
#define TM_DEFAULT_MYSQL_LOGIN "root"
#define TM_DEFAULT_MYSQL_PASSWORD "qwe123rty456"

/*
This class provides an interface for working with MySQL databases, using X DevAPI
*/
class TM_Database
{
public:
							TM_Database();
							~TM_Database();
protected:
	void					Connect(const char* host, int port, const char* login, const char* pass);
	void					Disconnect();
	void					SetDatabase(const char* name);
	void					SetTable(const char* name);
	mysqlx::Table			*mTable;
private:
	mysqlx::Session			*mSession;
	mysqlx::Schema			*mDatabase;
};
