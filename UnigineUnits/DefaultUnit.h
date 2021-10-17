#pragma once
#include <string>
#include <vector>

class DefaultUnit
{
public:
    
    struct Coordinates
    {
        Coordinates() : x(0.f), y(0.f) { }
        float x;
        float y;

        void norm()
        {
            const float lenght = sqrtf(x * x + y * y);
            x /= lenght;
            y /= lenght;
        }

        const Coordinates operator-(const DefaultUnit::Coordinates& vec2) const
        {
            DefaultUnit::Coordinates result;
            result.x = this->x - vec2.x;
            result.y = this->y - vec2.y;
            return result;
        }

        const Coordinates& operator/=(const float value)
        {
            this->x = this->x / value;
            this->y = this->y / value;
            return *this;
        }
    };

    DefaultUnit(const std::string& name, const Coordinates& position, const Coordinates& direction, const float viewDistance, const float m_viewSector);

    // Получение информации о юните
    const Coordinates&      GetPosition() const { return m_position; }
    const Coordinates&      GetDirection() const { return m_direction; }
    const float             GetViewDistance() const { return m_viewDistance; }
    const float             GetViewSector() const { return m_viewSector; }
    const std::string&      GetName() const { return m_name; }
    // //

                    // Получить число юнитов в поле зрения
    const int       GetVisibleUnits() const { return m_visibleUnits; }

                    // Добавление видимого юнита
    void            AddVisibleUnit() { ++m_visibleUnits; } 

                    // Находится ли юнит в зоне видимости?
    const bool      IsInViewSector(const DefaultUnit& unit);
    

private:
    std::string     m_name;             // Имя юнита
    float           m_viewDistance;     // Дистанция обзора
    float           m_viewSector;       // [Градусы] Сектор обзора
    int             m_visibleUnits;     // Кол-во видимых юнитов
    Coordinates     m_direction;        // Направления взгляда
    Coordinates     m_position;         // Позиция юнита
   
};
