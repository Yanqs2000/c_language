#include <iostream>
#include "head.h"

int main() {
    int a, b;
    std::cout << "Enter two numbers: ";
    std::cin >> a >> b;

    auto sum = add(a, b) + 2;
    auto difference = subtract(a, b) + 2;
    auto product = multipy(a, b) + 2;

    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Difference: " << difference << std::endl;
    std::cout << "Product: " << product << std::endl;

    return 0;
}