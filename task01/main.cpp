#include <iostream>


bool isPower(int a)
{
    return a > 0 && (a & (a - 1)) == 0;
}


int main()
{
    int number = 0;
    std::cout << "Insert: ";
    std::cin >> number;
    std::cout << isPower(number) << std::endl;
    return 0;
}
