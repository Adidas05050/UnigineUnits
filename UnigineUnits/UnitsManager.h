#pragma once
#include <string>
#include <vector>
#include "DefaultUnit.h"
#include "FileManager.h"

class UnitsManager
{
public:
         // Управление юнитами
    const bool ManageUnits(const std::string& filename);

private:
    std::vector<DefaultUnit> m_units; // список юнитов
};