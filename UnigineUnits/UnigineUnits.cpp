#include <iostream>
#include "DefaultUnit.h"

int main()
{
    UnitsManager* unitsManager = new UnitsManager();
    if (!unitsManager->Init("D:/Unigine/UnigineUnits/Debug/test.txt"))
        std::cout << "\nERROR!\n";
}
