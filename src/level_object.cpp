#include "level_object.hpp"

LevelObject::LevelObject(double x, double y, double w, double h) : m_x(x), m_y(y), m_w(w), m_h(h)
{
}
double &LevelObject::X()
{
    return m_x;
}
double &LevelObject::Y()
{
    return m_y;
}
double &LevelObject::W()
{
    return m_w;
}
double &LevelObject::H()
{
    return m_h;
}