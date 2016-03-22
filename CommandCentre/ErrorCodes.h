/** ErrorCodes.h
 * Andrew Ribeiro 
 * November 21, 2009
**/

/****** ERROR CODES ******
 * ERROR01: could not connect to the database, database down. 
 * ERROR02: user credentials invalid.
 * ERROR03: user tried to use admin functions, but is not an admin.
 * ERROR04: unimplemented method error. 
 *************************/

#pragma once

#include <string>
using std::string;

namespace comandrewribeiroremoterobot
{
	class ErrorCodes
	{
	public:
		static const string DB_ERROR;
		static const string INVALID_LOGIN;
		static const string NO_ADMIN;
		static const string UNIMPLEMENTED_METHOD;

		static string getDiscription(const string errorCode)
		{
			if(errorCode.compare(ErrorCodes::DB_ERROR) == 0)
			{
				return "No database connection could be attained... It's our fault";
			}
			else if(errorCode.compare(ErrorCodes::INVALID_LOGIN) == 0)
			{
				return "Username or password is incorrect";
			}
			else if(errorCode.compare(ErrorCodes::NO_ADMIN) == 0)
			{
				return "You cannot use admin functions";
			}
			else if(errorCode.compare(ErrorCodes::UNIMPLEMENTED_METHOD) == 0)
			{
				return "Functionality requested is not currently supported."; 
			}

			return "No discription available for this error";
		}

	};

	const string ErrorCodes::DB_ERROR = "ERROR01";
	const string ErrorCodes::INVALID_LOGIN = "ERROR02";
	const string ErrorCodes::NO_ADMIN = "ERROR03";
	const string ErrorCodes::UNIMPLEMENTED_METHOD = "ERROR04";
}