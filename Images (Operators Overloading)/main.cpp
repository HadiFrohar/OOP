#include <iostream>
#include <fstream>
#include <string>
#include "Image.h"
void waitForKey(const std::string& op)
{
	std::cout << "\n" << op << "\n";
	std::cout << "Press any key to continue\n";
	std::cin.ignore(1);
}
int main()
{

	Image left;
	std::ifstream ifs("left.txt");
	ifs >> left;
	ifs.close();
	waitForKey("cout << left");
	std::cout << left;

	Image right;
	ifs.open("right.txt");
	ifs >> right;
	ifs.close();
	waitForKey("cout << right");
	std::cout << right;



	Image smile;
	ifs.open("smile.txt");
	ifs >> smile;
	ifs.close();
	waitForKey("cout << smile");
	std::cout << smile;
	

	Image smiley = (left + right);
	waitForKey("cout << smiley (left+right)");
	std::cout << smiley << std::endl;
	smiley = (left + right) | smile;
	waitForKey("cout << smiley");
	std::cout << smiley;
	
	//the empty image
	Image emptyImg;
	std::cout << "EmptyImg\n";
	std::cin >> emptyImg;
	waitForKey("cout << emptyImg");
	std::cout << emptyImg << std::endl;
	Image nImg(5, 20);
	waitForKey("cout << nImg");
	std::cout << nImg << std::endl;


	waitForKey("left+right");
	std::cout << (left + right) << std::endl;
	std::cout << std::endl;




	waitForKey("right + left");
	std::cout << (right + left) << std::endl;
	std::cout << std::endl;



	waitForKey("left");
	std::cout << left << std::endl;
	std::cout << std::endl;
	waitForKey("right");
	std::cout << right << std::endl;
	std::cout << std::endl;



	waitForKey("left&right");
	std::cout << (left&right) << std::endl;
	std::cout << std::endl;

	waitForKey("right&left");
	std::cout << (right&left) << std::endl;
	std::cout << std::endl;

	waitForKey("left*2");
	std::cout << left*2 << std::endl;


	waitForKey("left | right");
	std::cout << (left | right) << std::endl;
	std::cout << std::endl;

	waitForKey("right | left");
	std::cout << (right | left) << std::endl;
	std::cout << std::endl;

	waitForKey("left");
	std::cout << left << std::endl;
	std::cout << std::endl;
	waitForKey("right");
	std::cout << right << std::endl;
	std::cout << std::endl;

	auto temp = left;
	waitForKey("temp=left");
	std::cout << temp << std::endl;

	temp = right;
	waitForKey("temp=right");
	std::cout << temp << std::endl;

	temp = temp;
	waitForKey("temp=temp");
	std::cout << temp << std::endl;

	waitForKey("right&=left:");
	std::cout << (right &= left) << std::endl;
	std::cout << std::endl;

	waitForKey("right|=left:");
	std::cout << (left |= temp) << std::endl;
	std::cout << std::endl;


	waitForKey("left");
	std::cout << left << std::endl;
	std::cout << std::endl;
	waitForKey("right");
	std::cout << right << std::endl;
	std::cout << std::endl;

	std::cout << std::endl;

	waitForKey("++right");
	std::cout << ++right << std::endl;
	std::cout << std::endl;
	
	waitForKey("--right");
	std::cout << --right << std::endl;
	std::cout << std::endl;

	waitForKey("left");
	std::cout << left << std::endl;
	std::cout << std::endl;

	waitForKey("--left");
	std::cout << --left << std::endl;
	std::cout << std::endl;



	return EXIT_SUCCESS;
}
