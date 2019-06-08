#include "item.h"

Item::Item()
{
    m_pos = QPoint(-1,-1);

    m_nNumber = 0;
    m_bIsMine = false;
    m_bMarked = false;
    m_bOpen = false;
}

Item::Item(QPoint pos)
{
    m_pos = pos;

    m_nNumber = 0;
    m_bIsMine = false;
    m_bMarked = false;
    m_bOpen = false;
}

