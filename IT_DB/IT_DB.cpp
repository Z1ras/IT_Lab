#include "Data.h"

Database_Manager mng;

int main()
{
    SetConsoleOutputCP(1251);
    while (true)
        mng.run();
    std::cout << "Hello World!\n";
}

