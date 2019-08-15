#pragma once
#include "TM_ILogger.h"

namespace TMLib
{
	/*
		An interface for working with databases
	*/
	class TM_IDatabase
	{
	public:
								TM_IDatabase() {}
		virtual					~TM_IDatabase() {}
		virtual void			Connect(const char* host, int port, const char* login, const char* pass) = 0;
		virtual void			Disconnect() = 0;
		virtual void			SetDatabase(const char* name) = 0;
		virtual void			SetTable(const char* name) = 0;

		virtual void			AddRowByString(const char* field, const char* value) = 0;
		virtual void			RemoveRowByString(const char* field, const char* value) = 0;
		//Changes an integer value of a field in a row with keyvalue of a keyfield
		virtual void			ChangeInteger(const char* keyfield, const char* keyvalue, const char* field, const int value) = 0;
		virtual void			ChangeString(const char* keyfield, const char* keyvalue, const char* field, const char* value) = 0;
		virtual const int		GetInteger(const char* keyfield, const char* keyvalue, const char* field) = 0;
		virtual const char*		GetString(const char* keyfield, const char* keyvalue, const char* field) = 0;
	};
};
