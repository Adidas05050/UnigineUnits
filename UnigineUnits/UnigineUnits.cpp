#include <iostream>
#include "DefaultUnit.h"

int main()
{
    UnitsManager* unitsManager = new UnitsManager();
    if (!unitsManager->ManageUnits("D:/Unigine/UnigineUnits/Debug/", "test.txt"))
    {
        std::cout << "\nERROR!\n";
        return -1;
    }
    return 0;
}
