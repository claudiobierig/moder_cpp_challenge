#ifndef TEMPERATURE_LITERALS_H
#define TEMPERATURE_LITERALS_H

#include <iostream>
#include <exception>

/*
Leaving following points open:
- Celsius + Fahrenheit
- Convert between two
- Addition/Substraction should only work in the same scale so no work here
- Compare two different scales
- Testcases
 */

class Kelvin{
public:
    Kelvin() = default;
    Kelvin(double temp){
        if(temp<0) {throw std::underflow_error("Cannot have less than 0K");} 
        temperature = temp;
    };
    virtual ~Kelvin() = default;
    Kelvin(const Kelvin& other) = default;
    Kelvin(Kelvin&& other) = default;
    Kelvin& operator=(const Kelvin& other) = default;
    Kelvin& operator=(Kelvin&& other) = default;

    double getTemperature() const {return temperature;};

    Kelvin& operator+=(const Kelvin& rhs)
    {
        temperature += rhs.getTemperature();
        return *this;
    };
    
    friend Kelvin operator+(Kelvin lhs, const Kelvin& rhs)
    {
        lhs += rhs;
        return lhs;
    };

    Kelvin& operator-=(const Kelvin& rhs)
    {
        if(temperature < rhs.temperature){
            throw std::underflow_error("Cannot have less than 0 K");
        }
        temperature -= rhs.getTemperature();
        return *this;
    };
    
    friend Kelvin operator-(Kelvin lhs, const Kelvin& rhs)
    {
        lhs -= rhs;
        return lhs;
    };


private:
    double temperature = 0;
};

inline bool operator<(const Kelvin& lhs, const Kelvin& rhs){ return lhs.getTemperature() < rhs.getTemperature(); }
inline bool operator>(const Kelvin& lhs, const Kelvin& rhs){ return rhs < lhs; }
inline bool operator<=(const Kelvin& lhs, const Kelvin& rhs){ return !(lhs > rhs); }
inline bool operator>=(const Kelvin& lhs, const Kelvin& rhs){ return !(lhs < rhs); }
inline bool operator==(const Kelvin& lhs, const Kelvin& rhs){ return lhs.getTemperature() == rhs.getTemperature(); }
inline bool operator!=(const Kelvin& lhs, const Kelvin& rhs){ return !(lhs == rhs); }

std::ostream& operator<<(std::ostream& os, const Kelvin& obj)
{
    os << obj.getTemperature() << " K";
    return os;
};

Kelvin operator""_K ( long double temperature )
{
    return Kelvin(temperature);
}

Kelvin operator""_K ( unsigned long long temperature )
{
    return Kelvin(temperature);
}
 

#endif //TEMPERATURE_LITERALS_H