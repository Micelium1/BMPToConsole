#pragma once
#include <string>
#include <fstream>
#include <memory>

class BMParser
{
public:
	BMParser();
	BMParser(const std::string& filename);
	void openBMP(const std::string& fileName);
	void displayBMP();
	void closeBMP();
	~BMParser();
private:
	std::shared_ptr<std::fstream> file;
};

