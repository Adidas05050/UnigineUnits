#include "DefaultUnit.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <thread>
namespace
{
const int THREADS = 12;
//-------------------------------------------------------
bool compareUnits(const DefaultUnit* unit1, const DefaultUnit* unit2)
{
	const int result = int(unit1->GetPosition().x > unit2->GetPosition().x);

	// Если одна координата совпадает, то сравниваем по второй
	if (result == 0)
		return unit1->GetPosition().y - unit2->GetPosition().y < 0 ? true : false;
	else
		return result < 0? true : false;
}
//-------------------------------------------------------
void FindUnitsInViewSector(std::vector<DefaultUnit*>& tempUnit, const std::vector<DefaultUnit>& originalUnits)
{
	for (auto& unit : tempUnit)
	{
		for (const auto& originalUnit : originalUnits)
		{
			if (&*unit == &originalUnit)
				continue;

			if (unit->IsInViewSector(originalUnit))
				unit->AddVisibleUnit();

		}
	}
}
//-------------------------------------------------------
}
DefaultUnit::DefaultUnit(const std::string& name, const Vector2& position, const Vector2& direction, const float viewDistance, const float viewSector)
	: m_name(name)
	, m_position(position)
	, m_direction(direction)
	, m_viewDistance(viewDistance)
	, m_visibleUnits(0)
	, m_viewSector(viewSector)
{
	// сразу нормализуем направление
	m_direction.norm();
}
//-------------------------------------------------------
const bool DefaultUnit::IsInViewSector(const DefaultUnit& unit)
{
	Vector2 relativePosition = (unit.GetPosition() - GetPosition());
	// Если не находится в радиусе видимости, то и проверять на сектор нет смысла
	if (!(m_viewDistance * m_viewDistance >= (relativePosition.x * relativePosition.x + relativePosition.y * relativePosition.y)))
		return false;

	relativePosition.norm();
	const float point = GetDirection().x * relativePosition.x + GetDirection().y * relativePosition.y;
	// Если угол к точке выходит за рамки половины сектор, то цель не видна
	return (std::acos(point) * 180.0 / 3.14) < GetViewSector() / 2;
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
	// Если считали полную информацию, но файл кончился принудительно добавляем последний
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

	std::vector<std::vector<DefaultUnit*>> tempVectors;
	std::vector<std::thread> threads;
	for (int thread = 0; thread < THREADS; ++thread)
	{
		std::vector<DefaultUnit*> tempVector;
		int maxSize = (m_units.size() / THREADS) * (thread + 1);
		for (int i = (m_units.size() / THREADS) * thread ; i < maxSize; i++)
			tempVector.push_back(&m_units[i]);
		tempVectors.emplace_back(tempVector);
		threads.push_back(std::thread(FindUnitsInViewSector, ref(tempVectors[thread]), ref(m_units)));
	}

	for (auto& thr : threads) 
	{
		thr.join();
	}
	m_units.clear();

	std::cout << "Done";
	return true;
}
//-------------------------------------------------------
