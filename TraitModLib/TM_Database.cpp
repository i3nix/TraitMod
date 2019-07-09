#include "TM_Database.h"

TM_Database::TM_Database() : mDatabase(NULL), mSession(NULL), mTable(NULL)
{
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
}

void TM_Database::Connect(const char* host, int port, const char* login, const char* pass)
{
	if(mSession != NULL)
		throw "Connection already exists";
	try
	{
		mSession = new mysqlx::Session(host,port,login,pass);
	}
	catch(mysqlx::Error e)
	{
		throw e.what();
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
		}
		catch(mysqlx::Error e)
		{
			//maybe need to do something here
		}
		delete mSession;
		mSession = NULL;
	}
}

void TM_Database::SetDatabase(const char* name)
{
	if(mSession == NULL)
		throw "Connection does not exist";
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
	}
	catch(mysqlx::Error e)
	{
		throw e.what();
	}
}

void TM_Database::SetTable(const char* name)
{

	if(mSession == NULL)
		throw "Connection does not exist";
	if(mDatabase == NULL)
		throw "Database is not set";
	if(mTable != NULL)
		delete mTable;
	try{
		mTable = new mysqlx::Table(mDatabase->getTable(name));
	}
	catch(mysqlx::Error e)
	{
		throw e.what();
	}
}
