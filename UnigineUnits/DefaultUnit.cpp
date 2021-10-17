#include "DefaultUnit.h"
#include <cmath>

//-------------------------------------------------------
DefaultUnit::DefaultUnit(const std::string& name, const Coordinates& position, const Coordinates& direction, 
						 const float viewDistance, const float viewSector)
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
	Coordinates relativePosition = (unit.GetPosition() - GetPosition());
	// Если не находится в радиусе видимости, то и проверять на сектор нет смысла
	if (!(m_viewDistance * m_viewDistance >= (relativePosition.x * relativePosition.x + relativePosition.y * relativePosition.y)))
		return false;

	relativePosition.norm();
	const float point = GetDirection().x * relativePosition.x + GetDirection().y * relativePosition.y;
	// Если угол к точке выходит за рамки половины сектор, то цель не видна
	return (std::acos(point) * 180.0 / 3.14) <= GetViewSector() / 2;
}
//-------------------------------------------------------