#include "PinakaStudio.h"

void CPinakaStudio::run()
{
	processDriverCode();
}

void CPinakaStudio::processDriverCode()
{
    pke::Vector<int> values{ 10, 20, 30 };

    values.pushBack(40);

    std::cout << values[0] << '\n';
    std::cout << values[3] << '\n';
}