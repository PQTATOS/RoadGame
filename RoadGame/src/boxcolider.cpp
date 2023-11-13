#include "boxcolider.h"

BoxColider::BoxColider()
{

}

bool BoxColider::isOverlap(const BoxColider& obj)
{
    float dx1 = obj.m_min.x() - m_max.x();
    float dy1 = obj.m_min.y() - m_max.y();
    float dx2 = m_min.x() - obj.m_max.x();
    float dy2 = m_min.y() - obj.m_max.y();

    if (dx1 > 0.0f || dy1 > 0.0f)
            return false;

        if (dx2 > 0.0f || dy2 > 0.0f)
            return false;

    return true;
}


void BoxColider::resize()
{

}
