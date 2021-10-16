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
    };
    DefaultUnit(const std::string& name, const Vector2& position, const Vector2& direction, const float viewDistance, const float viewSector);

    const Vector2&  GetPosition() const { return m_position; }
    const Vector2&  GetDirection() const { return m_direction; }
    const float     GetViewDistance() const { return m_viewDistance; }
    const float     GetViewSector() const { return m_viewSector; }
private:
    std::string m_name;
    Vector2     m_direction;
    Vector2     m_position;
    float       m_viewDistance;
    float       m_viewSector;
};

class InfoLoader
{
public:
    bool ParseFile(const std::string& filename, std::vector<DefaultUnit>& units);
    bool SaveFile(const std::string& filename, std::vector<DefaultUnit> units);
};

class UnitsManager
{
public:
    bool Init(const std::string& filename);
private:
    
    std::vector<DefaultUnit> m_units;
};