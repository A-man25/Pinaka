#include "../../../PinakaEngine/src/Pinaka/Core/PinakaEngineInc.h" // temp: to be removed

int main()
{
    pke::Vector<int> values{ 10, 20, 30 };

    values.pushBack(40);

    std::cout << values[0] << '\n';
    std::cout << values[3] << '\n';

    return 0;

}