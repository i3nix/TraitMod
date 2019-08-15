#include "TM_Database.h"
#include "TM_Exception.h"
#include "TM_ConsoleLogger.h"

namespace TMLib
	{
	TM_Database::TM_Database() : mDatabase(NULL), mSession(NULL), mTable(NULL)
	{
		TM_ConsoleLogger::GetDefaultLogger() << "Database object created\n";
	}

	TM_Database::~TM_Database()
	{
		if(mTable != NULL)
			delete mTable;
		if(mDatabase != NULL)
			delete mDatabase;
		if(mSession != NULL)
		{
			mSession->close();
			delete mSession;
		}
		TM_ConsoleLogger::GetDefaultLogger() << "Database object destroyed\n";
	}

	void TM_Database::Connect(const char* host, int port, const char* login, const char* pass)
	{
		if(mSession != NULL)
			throw TM_Exception("Connection already exists","TM_Database","TM_Database::Connect");
		try
		{
			mSession = new mysqlx::Session(host,port,login,pass);
			TM_ConsoleLogger::GetDefaultLogger() << "Connected to database:\n" << "\tHost: " << host << "\n\tPort: " << port << "\n\tLogin: " << login << "\n\tPassword: " << pass << "\n";
		}
		catch(mysqlx::Error e)
		{
			throw TM_Exception(e.what(),"TM_Database","TM_Database::Connect");
		}
	}

	void TM_Database::Disconnect()
	{
		if(mTable != NULL)
		{
			delete mTable;
			mTable = NULL;
		}
		if(mDatabase != NULL)
		{
			delete mDatabase;
			mDatabase = NULL;
		}
		if(mSession != NULL)
		{
			try{
				mSession->close();
				TM_ConsoleLogger::GetDefaultLogger() << "Disconnected from database\n";
			}
			catch(mysqlx::Error e)
			{
				TM_Exception(e.what(),"TM_Database","TM_Database::Disconnect");
			}
			delete mSession;
			mSession = NULL;
		}
	}

	void TM_Database::SetDatabase(const char* name)
	{
		if(mSession == NULL)
			throw TM_Exception("Connection does not exist","TM_Database","TM_Database::SetDatabase");
		if(mDatabase != NULL)
		{
			if(mTable != NULL)
			{
				delete mTable;
				mTable = NULL;
			}
			delete mDatabase;
		}
		try{
			mDatabase = new mysqlx::Schema(mSession->getSchema(name));
			TM_ConsoleLogger::GetDefaultLogger() << "Database set to " << name << "\n";
		}
		catch(mysqlx::Error e)
		{
			throw TM_Exception(e.what(),"TM_Database","TM_Database::SetDatabase");
		}
	}

	void TM_Database::SetTable(const char* name)
	{

		if(mSession == NULL)
			throw TM_Exception("Connection does not exist","TM_Database","TM_Database::SetTable");
		if(mDatabase == NULL)
			throw TM_Exception("Database is not set","TM_Database","TM_Database::SetTable");
		if(mTable != NULL)
			delete mTable;
		try{
			mTable = new mysqlx::Table(mDatabase->getTable(name));
			TM_ConsoleLogger::GetDefaultLogger() << "Table set to " << name << "\n";
		}
		catch(mysqlx::Error e)
		{
			throw TM_Exception(e.what(),"TM_Database","TM_Database::SetTable");
		}
	}

	const std::string TM_Database::GenerateWhere(const char* field) const
	{
		std::string str(field);
		str += " like :value";
		return str;
	}

	void TM_Database::AddRowByString(const char* field, const char* value)
	{
		try
		{
			mTable->insert(field).values(value).execute();
		}
		catch(mysqlx::Error e)
		{
			throw TM_Exception(e.what(),"TM_Database","TM_Database::AddRowByString");
		}
	}

	void TM_Database::RemoveRowByString(const char* field, const char* value)
	{
		try
		{
			mTable->remove().where(GenerateWhere(field)).bind("value",value).execute();
		}
		catch(mysqlx::Error e)
		{
			throw TM_Exception(e.what(),"TM_Database","TM_Database::RemoveRowByString");
		}
	}

	void TM_Database::ChangeInteger(const char* keyfield, const char* keyvalue, const char* field, const int value)
	{
		try
		{
			mTable->update().set(field, value).where(GenerateWhere(keyfield)).bind("value",keyvalue).execute();
		}
		catch(mysqlx::Error e)
		{
			throw TM_Exception(e.what(),"TM_Database","TM_Database::ChangeInteger");
		}
	}

	void TM_Database::ChangeString(const char* keyfield, const char* keyvalue, const char* field, const char* value)
	{
		try
		{
			mTable->update().set(field, value).where(GenerateWhere(keyfield)).bind("value",keyvalue).execute();
		}
		catch(mysqlx::Error e)
		{
			throw TM_Exception(e.what(),"TM_Database","TM_Database::ChangeString");
		}
	}

	const int TM_Database::GetInteger(const char* keyfield, const char* keyvalue, const char* field)
	{
		try
		{
			mysqlx::RowResult res = mTable->select(field).where(GenerateWhere(keyfield)).bind("value",keyvalue).execute();
			mysqlx::Row x = res.fetchOne();
			return x[0];
		}
		catch(mysqlx::Error e)
		{
			throw TM_Exception(e.what(),"TM_Database","TM_Database::GetInteger");
		}
	}

	const char* TM_Database::GetString(const char* keyfield, const char* keyvalue, const char* field)
	{
		try
		{
			mysqlx::RowResult res = mTable->select(field).where(GenerateWhere(keyfield)).bind("value",keyvalue).execute();
			mysqlx::Row x = res.fetchOne();
			return std::string(x[0]).c_str();
		}
		catch(mysqlx::Error e)
		{
			throw TM_Exception(e.what(),"TM_Database","TM_Database::GetInteger");
		}
	}

};
