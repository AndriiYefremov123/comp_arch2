#include <iostream>
#include "calculator.h"

int main() {
    double a = 10, b = 5;
    std::cout << "Add: " << Calculator::Add(a, b) << std::endl;
    std::cout << "Sub: " << Calculator::Sub(a, b) << std::endl;
    return 0;
}
