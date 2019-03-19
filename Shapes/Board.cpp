#include "Board.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include "macros.h"
#include <string>
#include "Utilities.h"

Board::Board()
{
    clear();
}

void Board::clear()
{
    // To workaround VS bug about using decltype with scope operator
    using BoardType = decltype(m_paintBoard);

    m_paintBoard = BoardType(MAX_X + 1, BoardType::value_type(MAX_Y + 1, 0));
}

void Board::print()
{
	std::cout << std::string(MAX_X, '=') << "\n";

	for (decltype(m_paintBoard[0].size()) row = 0; 
		row < m_paintBoard[0].size();
		++row)
	{
		for (decltype(m_paintBoard.size()) col = 0; col < m_paintBoard.size(); ++col)
		{
			if (m_paintBoard[col][m_paintBoard[0].size() -1 - row])
			{
				std::cout << '*';
            }
            else
            {
                std::cout << ' ';
            }
        }
        std::cout << std::endl;
    }
	std::cout << std::string(MAX_X, '=') << "\n";
}

void Board::drawLine(const Vertex& v1, const Vertex& v2)
{
    if (v2 < v1)
    {
        drawLine(v2, v1);
        return;
    }

    if (!v1.isValid() || !v2.isValid())
    {
        return;
    }

    if (sameX(v1, v2)) // parallel to the y axis
    {
        int x = static_cast<int>(v2.m_x);
        for (int i = static_cast<int>(v1.m_y); i <= v2.m_y; ++i)
        {
            m_paintBoard[x][i] = 1;
        }
    }
    else if (sameY(v1, v2)) // parallel to the x axis
    {
        int y = static_cast<int>(v2.m_y);
        for (int i = static_cast<int>(v1.m_x); i <= v2.m_x; ++i)
        {
            m_paintBoard[i][y] = 1;
        }
    }
    else // use DDA algorithm to draw
    {
        double slope = (v2.m_y - v1.m_y) / (v2.m_x - v1.m_x);
        Vertex lv1 = v1, lv2 = v2; // local copies for being able to swap them
        int estimateIndex;

        if (std::abs(slope) < 1)
        {
            if (slope > 0)
            {
                std::swap(lv1, lv2);
            }

            for (int i = static_cast<int>(std::min(lv1.m_x, lv2.m_x)),
                     end = static_cast<int>(std::max(lv1.m_x, lv2.m_x));
                 i <= end;
                 ++i)
            {
                estimateIndex = static_cast<int>(
                    std::floor(lv1.m_y + (i - lv1.m_x) * slope + 0.5));
                m_paintBoard[i][estimateIndex] = 1;
            }
        }
        else
        {
            if (lv1.m_y > lv2.m_y)
            {
                std::swap(lv1, lv2);
            }
            for (int i = static_cast<int>(lv1.m_y); i <= lv2.m_y; i++)
            {
                estimateIndex = static_cast<int>(
                    std::floor(lv1.m_x + (i - lv1.m_y) * (1 / slope) + 0.5));
                m_paintBoard[estimateIndex][i] = 1;
            }
        }
    }
}
