/** constants.h
 * Andrew Ribeiro 
 * November 21, 2009
**/

#pragma once

#include <string>
using std::string;

namespace comandrewribeiroremoterobot
{
	const string REST_ROOT_URL = "http://www.andrewribeiro.com";
	const string REST_API_URL = "/Testing/School/CS240/REST/ROBOTREST.php";
	const int COMMAND_MAX_SIZE = 5000;

	const string RESERVED_WORDS[] = {"moveforward","moveback","turnleft","turnright","sturnleft","sturnright",
		"pturnleft","pturnright"};

	const int MAX_VARIABLE_LENGTH = 30;
}