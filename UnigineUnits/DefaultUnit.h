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

    // ��������� ���������� � �����
    const Coordinates&      GetPosition() const { return m_position; }
    const Coordinates&      GetDirection() const { return m_direction; }
    const float             GetViewDistance() const { return m_viewDistance; }
    const float             GetViewSector() const { return m_viewSector; }
    const std::string&      GetName() const { return m_name; }
    // //

                    // �������� ����� ������ � ���� ������
    const int       GetVisibleUnits() const { return m_visibleUnits; }

                    // ���������� �������� �����
    void            AddVisibleUnit() { ++m_visibleUnits; } 

                    // ��������� �� ���� � ���� ���������?
    const bool      IsInViewSector(const DefaultUnit& unit);
    

private:
    std::string     m_name;             // ��� �����
    float           m_viewDistance;     // ��������� ������
    float           m_viewSector;       // [�������] ������ ������
    int             m_visibleUnits;     // ���-�� ������� ������
    Coordinates     m_direction;        // ����������� �������
    Coordinates     m_position;         // ������� �����
   
};
