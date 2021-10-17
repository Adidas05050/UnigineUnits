#pragma once
#include <string>
#include <vector>
#include "DefaultUnit.h"
#include "FileManager.h"

class UnitsManager
{
public:
         // ���������� �������
    const bool ManageUnits(const std::string& filename);

private:
    std::vector<DefaultUnit> m_units; // ������ ������
};