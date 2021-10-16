#include "DefaultUnit.h"
#include <fstream>
#include <iostream>
#include <algorithm>

namespace
{
bool compareUnits(const DefaultUnit* unit1, const DefaultUnit* unit2)
{
	const int result = int(unit1->GetPosition().x > unit2->GetPosition().x);

	// ���� ���� ���������� ���������, �� ���������� �� ������
	if (result == 0)
		return unit1->GetPosition().y - unit2->GetPosition().y < 0 ? true : false;
	else
		return result < 0? true : false;
}
}
DefaultUnit::DefaultUnit(const std::string& name, const Vector2& position, const Vector2& direction, const float viewDistance, const float viewSector)
	: m_name(name)
	, m_position(position)
	, m_direction(direction)
	, m_viewDistance(viewDistance)
	, m_viewSector(viewSector)
{
}
//-------------------------------------------------------
bool InfoLoader::ParseFile(const std::string& filename, std::vector<DefaultUnit>& units)
{
	bool isInfoLittle = true;
	std::ifstream file(filename);
	std::string name, temp;
	float distance = 0.f, sector = 0.f;
	DefaultUnit::Vector2 position, direction;

	while (!file.eof()) {
		file >> temp;
		if (temp == "sector" or temp == "Sector") 
		{
			file >> temp;
			// ������� ������� � �����
			if (temp.back() == ',')
				temp.pop_back();
			sector = stof(temp);
		}
		else if (temp == "distance")
		{
			file >> temp;
			// ������� ������� � �����
			if (temp.back() == ',')
				temp.pop_back();
			distance = stof(temp);
		}
		else if (temp == "position") 
		{
			file >> temp;
			size_t openIndex = temp.find_first_of("(");
			size_t middleIndex = temp.find_first_of(",");
			// ���� ������ ���, �� ���� � �������
			
			if (openIndex == std::string::npos)
			{
				std::cout << "\n Error position without coordinates! \n";
				continue;
			}
			position.x = stof(temp.substr(openIndex + 1, middleIndex - 1));
			size_t endIndex = temp.find_first_of(")");

			// ��-�� ������� ����������� ������ ����� �� ���������
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
			// ���� ������ ���, �� ���� � �������
			
			if (openIndex == std::string::npos)
			{
				std::cout << "\n Error direction without coordinates! \n";
				continue;
			}
			direction.x = stof(temp.substr(openIndex + 1, middleIndex - 1));

			size_t endIndex = temp.find_first_of(")");

			// ��-�� ������� ����������� ������ ����� �� ���������
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
		else // ���� ��������� ���-�� ��������� ������� �� ���
		{
			// �� ��������� ����� ���� ��� ������. �� �� ����� ��� ���� ���������� ���
			if (isInfoLittle)
			{
				temp.pop_back(); // ������� �������
				name = temp;
				isInfoLittle = false;
				continue;
			}
			
			// ������� ��������� ����� � ������ � ��������� �����������
			units.push_back(DefaultUnit(name, position, direction, distance, sector));

			// � ����� ������ ��� ����������
			temp.pop_back(); // ������� �������
			name = temp;
		}
	}
	// ���� ������� ������ ����������, �� ���� �������� ������������� ��������� ���������
	if(!isInfoLittle)
		units.push_back(DefaultUnit(name, position, direction, distance, sector));

	return true;
}
//-------------------------------------------------------
bool InfoLoader::SaveFile(const std::string& filename, std::vector<DefaultUnit> units)
{
	return false;
}
//-------------------------------------------------------
bool UnitsManager::Init(const std::string& filename)
{
	InfoLoader* loader = new InfoLoader();
	if (!loader->ParseFile(filename, m_units))
		return false;
	
	std::vector<DefaultUnit*> sortedUnits;
	for(auto& unit : m_units)
		sortedUnits.push_back(&unit);
	// ��������� ������, ����� ����� �������� ��� �������
	std::sort(sortedUnits.begin(), sortedUnits.end(), compareUnits);

	return true;
}
//-------------------------------------------------------

//-------------------------------------------------------