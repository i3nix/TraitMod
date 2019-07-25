#include "TM_Exception.h"

namespace TMLib
{
	TM_Exception::TM_Exception(const char* error, const char* file, const char* function, TM_ILogger& logger) : mError(error), mLogger(logger)
	{
		mLogger << "!!! An exception was thrown!\n" << "\tError: " << error << "\n" << "\tFile: " << file << ";\tMethod: " << function << "\n";
	}

	TM_Exception::~TM_Exception()
	{
	}

	void TM_Exception::Add(const char* file, const char* function)
	{
		mLogger << "\tFile: " << file << ";\tMethod: " << function << "\n";
	}
};
