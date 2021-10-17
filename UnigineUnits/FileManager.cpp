#include "FileManager.h"
#include <fstream>
#include <iostream>

//-------------------------------------------------------
bool FileManager::ParseFile(const std::string& filename, std::vector<DefaultUnit>& units)
{
	bool isInfoLittle = true;
	std::ifstream file(filename);
	if (!file.is_open())
	{
		std::cout << "File can`t open for reading.\n";
		return false;
	}

	std::string name, temp;
	float distance = 0.f, sector = 0.f;
	DefaultUnit::Coordinates position, direction;

	while (!file.eof()) {
		file >> temp;
		if (temp == "sector" or temp == "Sector") 
		{
			file >> temp;
			// Удаляем запятые в конце
			if (temp.back() == ',')
				temp.pop_back();
			sector = stof(temp);
		}
		else if (temp == "distance")
		{
			file >> temp;
			// Удаляем запятые в конце
			if (temp.back() == ',')
				temp.pop_back();
			distance = stof(temp);
		}
		else if (temp == "position") 
		{
			file >> temp;
			size_t openIndex = temp.find_first_of("(");
			size_t middleIndex = temp.find_first_of(",");
			// Если скобки нет, то беда с данными
			
			if (openIndex == std::string::npos)
			{
				std::cout << "\n Error position without coordinates! \n";
				continue;
			}
			position.x = stof(temp.substr(openIndex + 1, middleIndex - 1));
			size_t endIndex = temp.find_first_of(")");

			// Из-за пробела закрывающая скобка могла не считаться
			if (endIndex == std::string::npos)
			{
				file >> temp;
				temp = temp.substr(0, temp.find_first_of(")"));
			}
			else
			{
				temp = temp.substr(middleIndex + 1, endIndex);
			}

			position.y = stof(temp);
		}
		else if (temp == "direction") 
		{
			file >> temp;
			size_t openIndex = temp.find_first_of("(");
			size_t middleIndex = temp.find_first_of(",");
			// Если скобки нет, то беда с данными
			
			if (openIndex == std::string::npos)
			{
				std::cout << "\n Error direction without coordinates! \n";
				continue;
			}
			direction.x = stof(temp.substr(openIndex + 1, middleIndex - 1));

			size_t endIndex = temp.find_first_of(")");

			// Из-за пробела закрывающая скобка могла не считаться
			if (endIndex == std::string::npos)
			{
				file >> temp;
				temp = temp.substr(0, temp.find_first_of(")"));
			}
			else
			{
				temp = temp.substr(middleIndex + 1, endIndex);
			}
			direction.y = stof(temp);
		}
		else // Если считываем что-то невнятное считаем за имя
		{
			// Не добавляем юнита если это первый. Мы не знаем про него информацию ещё
			if (isInfoLittle)
			{
				temp.pop_back(); // Убираем запятую
				name = temp;
				isInfoLittle = false;
				continue;
			}
			
			// Сначала добавляем юнита в список с имеющейся информацией
			units.push_back(DefaultUnit(name, position, direction, distance, sector));

			// А потом читаем имя следующего
			temp.pop_back(); // Убираем запятую
			name = temp;
		}
	}

	file.close();
	return true;
}
//-------------------------------------------------------
bool FileManager::SaveFile(const std::string& filename, const std::vector<DefaultUnit>& units)
{
	std::ofstream file(filename);
	if (!file.is_open())
	{ 
		std::cout << "File can`t open for writing.\n";
		return false;
	}

	for (const auto& unit : units)
		file << unit.GetName() << ": sees " << unit.GetVisibleUnits() << "\n";

	file.close();
	return true;
}
//-------------------------------------------------------