#pragma once
#include <string>
#include <vector>

class DefaultUnit
{
public:
    struct Vector2
    {
        Vector2() : x(0.f), y(0.f) { }
        float x;
        float y;
        const Vector2 operator-(const Vector2& vec2) const
        {
            Vector2 result;
            result.x = this->x - vec2.x;
            result.y = this->y - vec2.y;
            return result;
        }

        const Vector2 operator/=(const float value)
        {
            Vector2 result;
            result.x = this->x / value;
            result.y = this->y / value;
            return result;
        }
        void norm()
        {
            const float lenght = sqrtf(x*x + y*y);
            x /= lenght;
            y /= lenght;
        }
    };

    DefaultUnit(const std::string& name, const Vector2& position, const Vector2& direction, const float viewDistance, const float m_viewSector);

    const Vector2&  GetPosition() const { return m_position; }
    const Vector2&  GetDirection() const { return m_direction; }
    const float     GetViewDistance() const { return m_viewDistance; }
    const float     GetViewSector() const { return m_viewSector; }
    const int       GetVisibleUnits() const { return m_visibleUnits; }
    void            AddVisibleUnit() { ++m_visibleUnits; } 
    const bool      IsInViewSector(const DefaultUnit& unit);
    const std::string& GetName() const { return m_name; }
private:
    std::string m_name;
    float       m_viewDistance;
    float       m_viewSector;
    int         m_visibleUnits;
    Vector2     m_direction;
    Vector2     m_position;
    Vector2     m_viewStartSector;
    Vector2     m_viewEndSector;
   
};

class InfoLoader
{
public:
    bool ParseFile(const std::string& filename, std::vector<DefaultUnit>& units);
    bool SaveFile(const std::string& filename, const std::vector<DefaultUnit>& units);
};

class UnitsManager
{
public:
    typedef DefaultUnit::Vector2 Vector2;

    bool ManageUnits(const std::string& path, const std::string& filename);

    //void FindUnitsInViewSector(int start, int end);
private:
    std::vector<DefaultUnit> m_units;
};