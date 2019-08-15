#pragma once
#include <mysqlx/xdevapi.h>

#include "TM_IDatabase.h"

#define TM_DEFAULT_MYSQL_HOST "localhost"
#define TM_DEFAULT_MYSQL_PORT 33060
#define TM_DEFAULT_MYSQL_LOGIN "root"
#define TM_DEFAULT_MYSQL_PASSWORD "qwe123rty456"

namespace TMLib
	{

	/*
	This class works with MySQL databases, using X DevAPI
	*/
	class TM_Database : public TM_IDatabase
	{
	public:
								TM_Database();
		virtual					~TM_Database();
		void					Connect(const char* host, int port, const char* login, const char* pass);
		void					Disconnect();
		void					SetDatabase(const char* name);
		void					SetTable(const char* name);

		void					AddRowByString(const char* field, const char* value);
		void					RemoveRowByString(const char* field, const char* value);

		void					ChangeInteger(const char* keyfield, const char* keyvalue, const char* field, const int value);
		void					ChangeString(const char* keyfield, const char* keyvalue, const char* field, const char* value);

		const int				GetInteger(const char* keyfield, const char* keyvalue, const char* field);
		const char*				GetString(const char* keyfield, const char* keyvalue, const char* field);
	private:
		mysqlx::Table			*mTable;
		mysqlx::Session			*mSession;
		mysqlx::Schema			*mDatabase;

		const std::string		GenerateWhere(const char* field) const;
	};
};
