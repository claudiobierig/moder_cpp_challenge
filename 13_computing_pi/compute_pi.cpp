#include <cmath>
#include <iomanip>
#include <iostream>

int main(){
    double pi_approx = 0;
    double pi_old = -1;
    int k = 0;
    while(std::abs(pi_approx - pi_old) > 0.001)
    {
        pi_old = pi_approx;
        pi_approx += std::sqrt(12)*std::pow(-3,-k)/(2*k+1);
        ++k;
    }
    std::cout << std::fixed << std::setprecision(2) << pi_approx << "\n";
}
