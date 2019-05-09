#pragma once
#include <istream>

class Utils
{
public:
	Utils() = delete;
	~Utils() = delete;
	static int readInt(std::istream& is); //reads integer from stream
	static char readChar(std::istream& is); //reads char from stream
private:
	static void cleanStream(std::istream &is); //cleans stream state, removes items from stream (ignore)
};

