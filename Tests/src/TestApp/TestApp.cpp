#include "TestApp.h"
#include <Pinaka/Core/PinakaEngineInc.h>

void TestApp::runVectorTest()
{
    std::cout << "\n"
        << "============================================================\n"
        << "                    VECTOR TESTS\n"
        << "============================================================\n";

    pke::Vector<int> values{ 10, 20, 30 };

    std::cout << "\n[Initial Vector]\n";
    std::cout << "values[0] : " << values[0] << '\n';
    std::cout << "values[1] : " << values[1] << '\n';
    std::cout << "values[2] : " << values[2] << '\n';

    std::cout << "\n[Push Back]\n";
    values.pushBack(40);
    std::cout << "Pushed      : 40\n";
    std::cout << "values[3]   : " << values[3] << '\n';

    std::cout << "\n------------------------------------------------------------\n"
        << "                    VECTOR TESTS DONE\n"
        << "------------------------------------------------------------\n";
}

void TestApp::runSLinkedListTest()
{
    std::cout << "\n"
        << "============================================================\n"
        << "                SINGLY LINKED LIST TESTS\n"
        << "============================================================\n";

    pke::SLinkedList<int> list{ 10, 20, 30 };

    std::cout << "\n[Initial List]\n";
    for (auto it = list.begin(); it != list.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << '\n';

    std::cout << "\n[Push Back]\n";
    list.pushback(40);
    std::cout << "Pushed      : 40\n";
    std::cout << "Back        : " << list.back() << '\n';

    std::cout << "\n[Push Front]\n";
    list.pushfront(5);
    std::cout << "Pushed      : 5\n";
    std::cout << "Front       : " << list.front() << '\n';

    std::cout << "\n[Insert At]\n";
    list.insertAt(25, 3);
    std::cout << "Inserted    : 25 at index 3\n";
    std::cout << "list[3]     : " << list.at(3) << '\n';

    std::cout << "\n[Search]\n";
    std::cout << "Search 30   : " << (list.search(30) ? "Found" : "Not Found") << '\n';
    std::cout << "Search 100  : " << (list.search(100) ? "Found" : "Not Found") << '\n';

    std::cout << "\n[Pop Front]\n";
    std::cout << "Removed     : " << list.popfront() << '\n';

    std::cout << "\n[Pop Back]\n";
    std::cout << "Removed     : " << list.popback() << '\n';

    std::cout << "\n[Current List]\n";
    for (auto it = list.begin(); it != list.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << '\n';

    std::cout << "\n[Reverse]\n";
    list.reverse();

    for (auto it = list.begin(); it != list.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << '\n';

    std::cout << "\n[List Information]\n";
    std::cout << "Size        : " << list.size() << '\n';
    std::cout << "Is Empty    : " << (list.isEmpty() ? "Yes" : "No") << '\n';
    std::cout << "Has Cycle   : " << (list.isCycle() ? "Yes" : "No") << '\n';

    std::cout << "\n------------------------------------------------------------\n"
        << "              SINGLY LINKED LIST TESTS DONE\n"
        << "------------------------------------------------------------\n";
}