#include "TM_Database.h"
#include "TM_Exception.h"

namespace TMLib
	{
	TM_Database::TM_Database(TM_ILogger& logger) : TM_IDatabase(logger), mDatabase(NULL), mSession(NULL), mTable(NULL)
	{
		mLogger << "Database object created\n";
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
		mLogger << "Database object destroyed\n";
	}

	void TM_Database::Connect(const char* host, int port, const char* login, const char* pass)
	{
		if(mSession != NULL)
			throw TM_Exception("Connection already exists","TM_Database","TM_Database::Connect",mLogger);
		try
		{
			mSession = new mysqlx::Session(host,port,login,pass);
			mLogger << "Connected to database:\n" << "\tHost: " << host << "\n\tPort: " << port << "\n\tLogin: " << login << "\n\tPassword: " << pass << "\n";
		}
		catch(mysqlx::Error e)
		{
			throw TM_Exception(e.what(),"TM_Database","TM_Database::Connect",mLogger);
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
				mLogger << "Disconnected from database\n";
			}
			catch(mysqlx::Error e)
			{
				TM_Exception(e.what(),"TM_Database","TM_Database::Disconnect",mLogger);
			}
			delete mSession;
			mSession = NULL;
		}
	}

	void TM_Database::SetDatabase(const char* name)
	{
		if(mSession == NULL)
			throw TM_Exception("Connection does not exist","TM_Database","TM_Database::SetDatabase",mLogger);
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
			mLogger << "Database set to " << name << "\n";
		}
		catch(mysqlx::Error e)
		{
			throw TM_Exception(e.what(),"TM_Database","TM_Database::SetDatabase",mLogger);
		}
	}

	void TM_Database::SetTable(const char* name)
	{

		if(mSession == NULL)
			throw TM_Exception("Connection does not exist","TM_Database","TM_Database::SetTable",mLogger);
		if(mDatabase == NULL)
			throw TM_Exception("Database is not set","TM_Database","TM_Database::SetTable",mLogger);
		if(mTable != NULL)
			delete mTable;
		try{
			mTable = new mysqlx::Table(mDatabase->getTable(name));
			mLogger << "Table set to " << name << "\n";
		}
		catch(mysqlx::Error e)
		{
			throw TM_Exception(e.what(),"TM_Database","TM_Database::SetTable",mLogger);
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
			throw TM_Exception(e.what(),"TM_Database","TM_Database::AddRowByString",mLogger);
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
			throw TM_Exception(e.what(),"TM_Database","TM_Database::RemoveRowByString",mLogger);
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
			throw TM_Exception(e.what(),"TM_Database","TM_Database::ChangeInteger",mLogger);
		}
	}
	
	int	 TM_Database::GetInteger(const char* keyfield, const char* keyvalue, const char* field)
	{
		try
		{
			mysqlx::RowResult res = mTable->select(field).where(GenerateWhere(keyfield)).bind("value",keyvalue).execute();
			mysqlx::Row x = res.fetchOne();
			return x[0];
		}
		catch(mysqlx::Error e)
		{
			throw TM_Exception(e.what(),"TM_Database","TM_Database::GetInteger",mLogger);
		}
	}

};
