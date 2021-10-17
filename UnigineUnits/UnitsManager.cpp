#include "UnitsManager.h"
#include <iostream>
#include <thread>

namespace
{
//-------------------------------------------------------
// Поиск юнитов в секторе обзора
void FindUnitsInViewSector(std::vector<DefaultUnit*>& tempUnit, const std::vector<DefaultUnit>& originalUnits)
{
	// Из-за потенциального изменения позиций юнитов не стал упорядочивать данные,
	// поэтому каждый раз перебираю весь массив юнитов, ускорение достигается потоками
	for (auto& unit : tempUnit)
	{
		for (const auto& originalUnit : originalUnits)
		{
			// Игнорируем самого себя
			if (&*unit == &originalUnit)
				continue;

			// Проверяем нахождение в видимости
			if (unit->IsInViewSector(originalUnit))
				unit->AddVisibleUnit();

		}
	}
}
//-------------------------------------------------------
}
//-------------------------------------------------------
const bool UnitsManager::ManageUnits(const std::string& filename)
{
	FileManager* manager = new FileManager();
	// Загружаем информацию о юнитах
	if (!manager->ParseFile(filename, m_units))
		return false;

	
	std::vector<std::vector<DefaultUnit*>> tempVectors;
	std::vector<std::thread> threads;
	int threadsCount = 0;
	std::cout << "Input theards count: ";
	std::cin >> threadsCount;
	if (threadsCount > m_units.size())
	{
		threadsCount = 1;
		std::cout << "More threads than units! Threads count will be 1\n";
	}
	// Из-за нехватки знаний для решения проблем доступа в многопоточности
	// использую разделение массива юнитов на число потоков 
	for (int thread = 0; thread < threadsCount; ++thread)
	{
		std::vector<DefaultUnit*> tempVector;
		int maxSize = (m_units.size() / threadsCount) * (thread + 1);
		for (int i = (m_units.size() / threadsCount) * thread ; i < maxSize; i++)
			tempVector.push_back(&m_units[i]);
		tempVectors.emplace_back(tempVector);
		threads.push_back(std::thread(FindUnitsInViewSector, ref(tempVectors[thread]), ref(m_units)));
	}

	for (auto& thr : threads) 
	{
		thr.join();
	}

	// Сохранение полученной информации о юнитах
	const int dotIndex = filename.find_last_of(".");
	const std::string& saveFilename = filename.substr(0, dotIndex) + "_output" +
									  filename.substr(dotIndex);

	if (!manager->SaveFile(saveFilename, m_units))
		return false;

	return true;
}
//-------------------------------------------------------
