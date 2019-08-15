#pragma once
#include <string>
#include <stack>

#include "TM_FileLogger.h"

#define TM_DEFAULT_ERROR_LOG_FILE_NAME "Error.log"

namespace TMLib
{
	/*
		Each exception should be converted into this class
		Holds an error string and the place, where an exception was thrown.
	*/
	class TM_Exception
	{
	public:
								TM_Exception(const char* error, const char* file, const char* function);
								~TM_Exception();
		void					 Add(const char* file, const char* function);
		std::string				 GetError() const;
	private:
		static TM_FileLogger	mLogger;
		std::string				mError;
	};
};