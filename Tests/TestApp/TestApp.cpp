#include "TestApp.h"

#include <Pinaka/Core/PinakaEngineInc.h>
#include <Pinaka/Foundation/Math/Point2D.h>
#include <Pinaka/Foundation/Math/Point3D.h>
#include <Pinaka/Foundation/Math/Vector2D.h>
#include <Pinaka/Foundation/Math/Vector3D.h>

#include <iomanip>
#include <iostream>
#include <limits>

namespace
{
    void printValue(const char* label, double value)
    {
        std::cout << std::left << std::setw(24) << label
            << std::right << std::fixed << std::setprecision(4) << value << '\n';
    }
}

void TestApp::printHeader(const char* title) const
{
    std::cout << '\n'
        << "+==========================================================+\n"
        << "| " << std::left << std::setw(57) << title << "|\n"
        << "+==========================================================+\n";
}

void TestApp::printPass(const char* label, bool condition) const
{
    std::cout << (condition ? "[PASS] " : "[FAIL] ") << label << '\n';
}

void TestApp::pause() const
{
    std::cout << "\nPress Enter to return to the menu...";
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    std::cin.get();
}

void TestApp::runContainerVectorTest()
{
    printHeader("PINAKA VECTOR CONTAINER");

    pke::Vector<int> values{ 10, 20, 30 };
    printPass("Initializer-list construction", values.size() == 3);

    values.pushBack(40);
    printPass("pushBack appends 40", values.at(3) == 40);

    values.frontInsert(5);
    printPass("frontInsert prepends 5", values.at(0) == 5);

    values.insertAt(25, 3);
    printPass("insertAt inserts 25", values.at(3) == 25);

    std::cout << "\nContents: ";
    for (int i = 0; i < values.size(); ++i)
    {
        std::cout << values[i] << (i + 1 < values.size() ? " -> " : "\n");
    }

    pke::Vector<int> matches;
    printPass("Linear search finds 25", values.linearSearch(25, matches) && matches.size() == 1);
    printValue("Size", static_cast<double>(values.size()));
    printValue("Capacity", static_cast<double>(values.capacity()));

    pause();
}

void TestApp::runSLinkedListTest()
{
    printHeader("SINGLY LINKED LIST");

    pke::SLinkedList<int> list{ 10, 20, 30 };
    printPass("Initializer-list construction", list.size() == 3);

    list.pushfront(5);
    list.pushback(40);
    list.insertAt(25, 3);
    printPass("Push/insert operations", list.size() == 5 && list.search(25));

    std::cout << "\nContents: ";
    for (auto it = list.begin(); it != list.end(); ++it)
    {
        std::cout << *it << ' ';
    }
    std::cout << '\n';

    std::cout << "\nFront: " << list.front() << "  Back: " << list.back() << '\n';
    printPass("No cycle detected", !list.isCycle());

    list.reverse();
    std::cout << "Reversed: ";
    for (auto it = list.begin(); it != list.end(); ++it)
    {
        std::cout << *it << ' ';
    }
    std::cout << '\n';

    pause();
}

void TestApp::runPoint2DTest()
{
    printHeader("POINT 2D");

    pke::Point2D origin;
    pke::Point2D point(3.0, 4.0);

    printPass("Default origin is (0, 0)", origin.x() == 0.0 && origin.y() == 0.0);
    printPass("Distance from origin is 5", point.distance(origin) == 5.0);

    origin.setX(1.0);
    origin.setY(1.0);
    printPass("Setters update coordinates", origin.x() == 1.0 && origin.y() == 1.0);

    printValue("Point x", point.x());
    printValue("Point y", point.y());
    printValue("Updated distance", point.distance(origin));

    pause();
}

void TestApp::runPoint3DTest()
{
    printHeader("POINT 3D");

    pke::Point3D origin;
    pke::Point3D point(1.0, 2.0, 2.0);

    printPass("Default origin is (0, 0, 0)", origin.x() == 0.0 && origin.y() == 0.0 && origin.z() == 0.0);
    printPass("Distance from origin is 3", point.distance(origin) == 3.0);

    point.setX(3.0);
    point.setY(4.0);
    point.setZ(12.0);
    printPass("Setters update all coordinates", point.x() == 3.0 && point.y() == 4.0 && point.z() == 12.0);

    printValue("Point x", point.x());
    printValue("Point y", point.y());
    printValue("Point z", point.z());
    printValue("Distance from origin", point.distance(origin));

    pause();
}

void TestApp::runVector2DTest()
{
    printHeader("VECTOR 2D");

    pke::Vector2D a(3.0, 4.0);
    pke::Vector2D b(1.0, 2.0);
    pke::Vector2D sum = a + b;

    printPass("Addition", sum == pke::Vector2D(4.0, 6.0));
    printPass("Magnitude of (3,4)", a.getMagnitude() == 5.0);
    printPass("Squared magnitude", a.getSquaredMagnitude() == 25.0);

    pke::Vector2D unit = a.normalize();
    printValue("Normalized x", unit.getXcomp());
    printValue("Normalized y", unit.getYcomp());
    printValue("Normalized magnitude", unit.getMagnitude());

    pause();
}

void TestApp::runVector3DTest()
{
    printHeader("VECTOR 3D");

    pke::Vector3D a(1.0, 0.0, 0.0);
    pke::Vector3D b(0.0, 1.0, 0.0);
    pke::Vector3D c(3.0, 4.0, 12.0);

    pke::Vector3D sum = a + b;
    printPass("Addition", sum == pke::Vector3D(1.0, 1.0, 0.0));
    printPass("Magnitude of (3,4,12)", c.getMagnitude() == 13.0);
    printPass("Dot product", a.alignmentWith(b) == 0.0);

    pke::Vector3D cross = a.crossProduct(b);
    printPass("Cross product is (0,0,1)", cross == pke::Vector3D(0.0, 0.0, 1.0));
    printPass("Vectors are perpendicular", a.isPerpendicularTo(b));

    pke::Vector3D unit = c.normalize();
    printValue("Normalized x", unit.getXcomp());
    printValue("Normalized y", unit.getYcomp());
    printValue("Normalized z", unit.getZcomp());
    printValue("Normalized magnitude", unit.getMagnitude());

    pke::Vector3D pointVector(pke::Point3D(1.0, 2.0, 3.0), pke::Point3D(4.0, 6.0, 3.0));
    printPass("Point-to-point vector", pointVector == pke::Vector3D(3.0, 4.0, 0.0));

    pause();
}

void TestApp::runSmartPointerTest()
{
    printHeader("SMART POINTERS");

    pke::Unique_ptr<int> unique(new int(42));
    printPass("Unique_ptr owns value", unique.get() != nullptr && *unique == 42);

    pke::Shared_ptr<int> first(new int(42));
    pke::Shared_ptr<int> second = first;
    printPass("Shared_ptr copy shares ownership", first.use_count() == 2 && *second == 42);

    first.reset();
    printPass("Reset releases one owner", first.get() == nullptr && second.use_count() == 1);

    pause();
}

void TestApp::runAllTests()
{
    runContainerVectorTest();
    runSLinkedListTest();
    runPoint2DTest();
    runPoint3DTest();
    runVector2DTest();
    runVector3DTest();
    runSmartPointerTest();
}

void TestApp::run()
{
    bool running = true;
    while (running)
    {
        printHeader("PINAKA TEST DRIVER");
        std::cout
            << "  1. Pinaka Vector Container\n"
            << "  2. Singly Linked List\n"
            << "  3. Point 2D\n"
            << "  4. Point 3D\n"
            << "  5. Vector 2D\n"
            << "  6. Vector 3D\n"
            << "  7. Smart Pointers\n"
            << "  8. Run Every Test\n"
            << "  0. Exit\n"
            << "+----------------------------------------------------------+\n"
            << "Selection: ";

        int selection = -1;
        std::cin >> selection;

        if (!std::cin)
        {
            std::cin.clear();
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            continue;
        }

        switch (selection)
        {
        case 1: runContainerVectorTest(); break;
        case 2: runSLinkedListTest(); break;
        case 3: runPoint2DTest(); break;
        case 4: runPoint3DTest(); break;
        case 5: runVector2DTest(); break;
        case 6: runVector3DTest(); break;
        case 7: runSmartPointerTest(); break;
        case 8: runAllTests(); break;
        case 0: running = false; break;
        default:
            std::cout << "\nUnknown selection. Please choose a menu option.\n";
            break;
        }
    }

    std::cout << "\nPinaka Test Driver closed.\n";
}