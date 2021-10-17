#include <iostream>
#include "UnitsManager.h"

int main()
{
    UnitsManager* unitsManager = new UnitsManager();
    std::string filename;
    std::cout << "Input filename with full path or write default for default file.\n";
    std::cin >> filename;
    if (filename == "default")
        filename = "D:/Unigine/UnigineUnits/Debug/test.txt";

    if (!unitsManager->ManageUnits(filename))
    {
        std::cout << "\nERROR!\n";
        return -1;
    }
    std::cout << "Done";
    return 0;
}
