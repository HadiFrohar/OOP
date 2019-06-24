#pragma once
#include <exception>
//If user opening file failed
class FileNotOpen : public std::exception
{
public:
	const char * what() const noexcept {

		return "Error, couldn't open file!";
	}
};

//error occured in cfg file
class ConfigError : public std::exception
{
public:
	const char * what() const noexcept {

		return "Error, a configuration file is corrupt!";
	}
};