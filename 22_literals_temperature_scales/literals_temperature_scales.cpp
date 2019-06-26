#include <iostream>
#include "temperature_literals.h"

int main()
{
    auto k1 = Kelvin(10);
    auto k2 = Kelvin(10);
    auto k3 = k1 + k2;
    try{
        auto k4 = k1 - k3;
        std::cout << k4 << "\n";
    }catch(const std::underflow_error& e){
        std::cout << e.what() << "\n";
    }
    try{
        auto k4 = Kelvin(-1);
        std::cout << k4 << "\n";
    }catch(const std::underflow_error& e){
        std::cout << e.what() << "\n";
    }
    std::cout << k3 + 3_K << "\n";
}