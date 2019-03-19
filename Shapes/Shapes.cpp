#include <iostream>
#include <string>

#include "macros.h"
#include "Vertex.h"
#include "Board.h"

#define RECTANGLE           1
#define ISOSCELESTRIANGLE   1
#define HOUSE               1
#define KITE                1

#if RECTANGLE
#include "Rectangle.h"
void drawAndPrint(const Rectangle&, Board&);
#endif

#if ISOSCELESTRIANGLE
#include "IsoscelesTriangle.h"
void drawAndPrint(const IsoscelesTriangle&, Board&);
#endif

#if HOUSE
#include "House.h"
void drawAndPrint(const House&, Board&);
#endif

#if KITE
#include "Kite.h"
void drawAndPrint(const Kite&, Board&);
void readVerticesForKite(Vertex vertices[3], bool upper);
#endif

void waitForEnter();
void printVertex(const Vertex& vertex);
Vertex readVertex();

int main()
{
    Board board;

#if RECTANGLE
    {
        board.clear();
        Vertex vertices[2];
        std::cout << "Please enter x and y coordinates for the bottom-left "
            "vertex of the rectangle:\n";
        vertices[0] = readVertex();
        std::cout << "Please enter x and y coordinates for the top-right vertex"
            " of the rectangle:\n";
        vertices[1] = readVertex();
        std::cin.ignore(); // ignore the enter

        Rectangle rect(vertices);
        drawAndPrint(rect, board);

        board.clear();
        std::cout << "Now scaled by factor of 2:\n\n";
        bool scaling = rect.scale(2);
        if (scaling)
        {
            drawAndPrint(rect, board);
        }
        else
        {
            std::cout << "Scaling failed!\n";
        }
    }
#endif // RECTANGLE

#if ISOSCELESTRIANGLE
    {
        board.clear();
        Vertex vertices[3];
        std::cout << "Please enter x and y coordinates for the first vertex of "
            "the triangle:\n";
        vertices[0] = readVertex();
        std::cout << "Please enter x and y coordinates for the second vertex "
            "of the triangle:\n";
        vertices[1] = readVertex();
        std::cout << "Please enter x and y coordinates for the third vertex of "
            "the triangle:\n";
        vertices[2] = readVertex();
        std::cin.ignore(); // ignore the enter

        IsoscelesTriangle triangle(vertices);
        drawAndPrint(triangle, board);

        board.clear();
        std::cout << "Now scaled by factor of 2:\n\n";
        bool scaling = triangle.scale(2);
        if (scaling)
        {
            drawAndPrint(triangle, board);
        }
        else
        {
            std::cout << "Scaling failed!\n";
        }
    }
#endif // ISOSCELESTRIANGLE

#if HOUSE
    {
        board.clear();
        Vertex triVertices[3];
        std::cout << "Please enter x and y coordinates for the first vertex of "
            "the triangle of the roof:\n";
        triVertices[0] = readVertex();
        std::cout << "Please enter x and y coordinates for the second vertex "
            "of the triangle of the roof:\n";
        triVertices[1] = readVertex();
        std::cout << "Please enter x and y coordinates for the third vertex of "
            "the triangle of the roof:\n";
        triVertices[2] = readVertex();

        Vertex rectVertices[2];
        std::cout << "Please enter x and y coordinates for the bottom-left "
            "vertex of the rectangle of the basis:\n";
        rectVertices[0] = readVertex();
        std::cout << "Please enter x and y coordinates for the top-right vertex"
            " of the rectangle of the basis:\n";
        rectVertices[1] = readVertex();
        std::cin.ignore(); // ignore the enter

        Rectangle rect(rectVertices);
        IsoscelesTriangle triangle(triVertices);
		House house(rect, triangle);
        drawAndPrint(house, board);

        board.clear();
        std::cout << "Now scaled by factor of 2:\n\n";
        bool scaling = house.scale(2);
        if (scaling)
        {
            drawAndPrint(house, board);
        }
        else
        {
            std::cout << "Scaling failed!\n";
        }
    }
#endif // HOUSE

#if KITE
    {
        board.clear();
        Vertex firstTriangle[3];
        Vertex secondTriangle[3];
        readVerticesForKite(firstTriangle, true);
        readVerticesForKite(secondTriangle, false);
		IsoscelesTriangle triangles[2] = { firstTriangle, secondTriangle };
        Kite kite(triangles);
        drawAndPrint(kite, board);

        board.clear();
        std::cout << "Now scaled by factor of 2:\n\n";
        bool scaling = kite.scale(2);
        if (scaling)
        {
            drawAndPrint(kite, board);
        }
        else
        {
            std::cout << "Scaling failed!\n";
        }
    }
#endif // KITE
}

#if RECTANGLE
void drawAndPrint(const Rectangle& rect, Board& board)
{
    rect.draw(board);
    board.print();
    waitForEnter();

    std::cout << "Now with the bounding rectangle, too:\n";
    Rectangle boundingRect = rect.getBoundingRectangle();
    boundingRect.draw(board);
    board.print();
    waitForEnter();


    std::cout << "The bottom-left vertex of the rectangle is: ";
    printVertex(rect.getBottomLeft());
    std::cout << '\n';

    std::cout << "The top-right vertex is: ";
    printVertex(rect.getTopRight());
    std::cout << '\n';

    std::cout << "The perimeter of the rectangle is: " << rect.getPerimeter()
        << '\n';

    std::cout << "The area of the rectangle is: " << rect.getArea() << '\n';

    std::cout << "The center of the Rectangle is: ";
    printVertex(rect.getCenter());
    std::cout << '\n';

    waitForEnter();
}
#endif // RECTANGLE

#if ISOSCELESTRIANGLE
void drawAndPrint(const IsoscelesTriangle& triangle, Board& board)
{
    triangle.draw(board);
    board.print();
    waitForEnter();

    std::cout << "Now with the bounding rectangle, too:\n";
    Rectangle boundingRect = triangle.getBoundingRectangle();
    boundingRect.draw(board);
    board.print();
    waitForEnter();

    std::cout << "The vertices of the triangle are:\n";
    for (int i = 0; i < 3; ++i)
    {
        printVertex(triangle.getVertex(i));
        std::cout << '\n';
    }

    std::cout << "The perimeter of the triangle is: " << triangle.getPerimeter()
        << '\n';

    std::cout << "The area of the triangle is: " << triangle.getArea() << '\n';

    std::cout << "The center of the triangle is: ";
    printVertex(triangle.getCenter());
    std::cout << '\n';

    waitForEnter();
}
#endif // ISOSCELESTRIANGLE

#if HOUSE
void drawAndPrint(const House& house, Board& board)
{
    house.draw(board);
    board.print();
    waitForEnter();

    std::cout << "Now with the bounding rectangle, too:\n";
    Rectangle boundingRect = house.getBoundingRectangle();
    boundingRect.draw(board);
    board.print();
    waitForEnter();

    std::cout << "The perimeter of the house is: " << house.getPerimeter()
        << '\n';

    std::cout << "The area of the house is: " << house.getArea() << '\n';

    std::cout << "The center of the house is: ";
    printVertex(house.getCenter());
    std::cout << '\n';

    waitForEnter();
}
#endif // HOUSE

#if KITE
void drawAndPrint(const Kite& kite, Board& board)
{
    kite.draw(board);
    board.print();
    waitForEnter();

    std::cout << "Now with the bounding rectangle, too:\n";
    Rectangle boundingRect = kite.getBoundingRectangle();
    boundingRect.draw(board);
    board.print();
    waitForEnter();

    std::cout << "The height of the kite is: " << kite.getTotalHeight()
        << '\n';

    std::cout << "The perimeter of the kite is: "
        << kite.getPerimeter() << '\n';

    std::cout << "The area of the kite is: " << kite.getArea() << '\n';

    std::cout << "The center of the kite is: ";
    printVertex(kite.getCenter());
    std::cout << '\n';

    waitForEnter();
}

void readVerticesForKite(Vertex vertices[3], bool upper)
{
    for (int i = 0; i < 3; ++i)
    {
        std::cout << "Please enter x and y coordinates for vertex " << i + 1
            << " of the " << (upper ? "top " : "bottom ") << "triangle:\n";
        vertices[i] = readVertex();
    }
}
#endif // KITE

void waitForEnter()
{
    std::cout << "Press Enter to continue...\n";
    std::string line;
    std::getline(std::cin, line);
}

void printVertex(const Vertex& vertex)
{
    std::cout << "(" << vertex.m_x << ", " << vertex.m_y << ")";
}

Vertex readVertex()
{
    Vertex result;
    std::cin >> result.m_x >> result.m_y;
    return result;
}
