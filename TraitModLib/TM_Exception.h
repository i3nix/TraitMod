#pragma once
#include <string>
#include <stack>

#include "TM_ILogger.h"

namespace TMLib
{
	/*
		Each exception should be converted into this class
		Holds an error string and the place, where an exception was thrown.
	*/
	class TM_Exception
	{
	public:
		TM_Exception(const char* error, const char* file, const char* function, TM_ILogger& logger);
		~TM_Exception();
		void Add(const char* file, const char* function);
	private:
		TM_ILogger& mLogger;
		std::string mError;
	};
};
