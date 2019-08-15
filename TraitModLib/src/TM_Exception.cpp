#include "TM_Exception.h"

namespace TMLib
{
	TM_Exception::TM_Exception(const char* error, const char* file, const char* function) : mError(error)
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

	std::string TM_Exception::GetError() const
	{
		return mError;
	}

	TM_FileLogger TM_Exception::mLogger(TM_DEFAULT_ERROR_LOG_FILE_NAME);
};
