#pragma once
#include <string>
#include <vector>
#include "DefaultUnit.h"

class FileManager
{
public:
         // Загрузка информации из файла
    bool ParseFile(const std::string& filename, std::vector<DefaultUnit>& units);
         // Сохранить полученную информацию о юнитах   
    bool SaveFile(const std::string& filename, const std::vector<DefaultUnit>& units);
};
