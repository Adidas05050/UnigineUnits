#pragma once
#include <string>
#include <vector>
#include "DefaultUnit.h"

class FileManager
{
public:
         // �������� ���������� �� �����
    bool ParseFile(const std::string& filename, std::vector<DefaultUnit>& units);
         // ��������� ���������� ���������� � ������   
    bool SaveFile(const std::string& filename, const std::vector<DefaultUnit>& units);
};
