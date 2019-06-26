# Lessons Learned

## 26.06.2019 Using a template parameter to define the scale and type traits for conversion (22)

Book answer, not implemented. I would have written Constructors taking an object of the other class as argument. But having just one class with a Template Parameter defining the scale is need and probably saves a lot of code when writing all 3 scales.
The struct `conversion_traits` is necessary since we somehow need to know about both scales. The following is a code snippet from the book answer.

~~~c++
enum class scale
{
    celsius,
    fahrenheit,
    kelvin
};

template <scale S>
class quantity
{
    const double amount;
public:
    constexpr explicit quantity(double const a) : amount(a) {}

    explicit operator double() const { return amount; }
};

template <scale S, scale R>
struct conversion_traits
{
    static double convert(double const value) = delete;
};

template <>
struct conversion_traits<scale::celsius, scale::kelvin>
{
    static double convert(double const value)
    {
        return value + 273.15;
    }
};

template <>
struct conversion_traits<scale::kelvin, scale::celsius>
{
    static double convert(double const value)
    {
        return value - 273.15;
    }
};

template <scale R, scale S>
constexpr quantity<R> temperature_cast(quantity<S> const q)
{
    return quantity<R>(conversion_traits<S, R>::convert(static_cast<double>(q)));
}

auto t1{ 36.5_deg };
auto tk = temperature_cast<scale::kelvin>(t1);
~~~

## 26.06.2019 User defined literals (22)

Since C++11 there are user defined literals:

~~~c++
Kelvin operator""_K ( long double temperature )
{
    return Kelvin(temperature);
}

Kelvin k = 10.0_K;
~~~

Since these are most likely used in libraries, they should be namespaced.

## 21.06.2019 Fold Expressions (19, 20)

For compile time recursion in variadic templates there are fold expressions since C++17:

~~~c++
template <typename Container, typename... T>
void push_back(Container& c, T&&... args)
{
    (c.push_back(args), ...);
}

template <typename Container, typename... T>
bool contains_any(Container& c, T&&... args)
{
    return (... || (std::find(c.begin(), c.end(), args) != c.end()));
}

template <typename Container, typename... T>
bool contains_none(Container& c, T&&... args)
{
    return !(contains_any(c, std::forward<T>(args)...));
}
~~~
