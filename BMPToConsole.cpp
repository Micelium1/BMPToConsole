#include <iostream>
#include "BMParser.h"

int main(int argc, char* argv[])
{
    setlocale(0,"");
    if (argc < 2) {
        std::cerr << "Использование: " << argv[0] << " <путь_к_файлу>" << std::endl;
        return 1;
    }
    std::string filename;
    filename = argv[1];
    BMParser Parser;
    try { Parser.openBMP(filename); }
    catch (std::runtime_error& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    try { Parser.displayBMP(); }
    catch (std::runtime_error& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    std::system("pause");
    return 0;
}
