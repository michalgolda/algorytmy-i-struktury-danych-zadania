#include <iostream>
#include <fstream>
#include <string>

struct President {
    std::string firstName;
    std::string lastName;
    int startYear;
    int endYear;
    std::string politicalParty;
};

President* parseData(char* filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cout << "Something went wrong during data file opening." << std::endl;
        exit(0);
    }
}

int main(int argc, char* argv[]) {
    if (argc > 2 || argc == 1)
    {
        std::cout << "Correct usage: main <data-file-path>" << std::endl;
        exit(0);
    }

    char* filePath = argv[1];
    President* presidents[] = parseData(filePath);

    return 0;
}
