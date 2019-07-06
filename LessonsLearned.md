# Lessons Learned

## 06.07.2019 Using gcc-8 with cmake (37)

So far I used gcc-7, but filesystem is not included. Everything works with clang-7.
I didn't get gcc-8 to work:

~~~sh
cmake -DCMAKE_C_COMPILER=/usr/bin/clang-7 -DCMAKE_CXX_COMPILER=/usr/bin/clang++-7 ../ #works
cmake -DCMAKE_C_COMPILER=gcc-8 -DCMAKE_CXX_COMPILER=g++-8 ../ #doesn't work
~~~

It stalls and never finishes to run.
Compiling on the commandline works fine:

~~~sh
g++-8 -std=c++17 ../37_finding_files/finding_files.cpp -lstdc++fs -o finding_files
~~~

Since cmake and g++-8 work I guess that it is some setup problem. Will be continued.

## 06.07.2019 Raw strings (37)

[String literals](https://en.cppreference.com/w/cpp/language/string_literal)

~~~c++
const char* s1 = R"foo(
Hello
World
)foo";
//same as
const char* s2 = "\nHello\nWorld\n";
~~~

## 06.07.2019 std::filesystem (37)

- Using `std::filesystem` requires linking against `stdc++fs`.
- `directory_iterator` (iterate over directory) vs. `recursive_directory_iterator` (also iterates over subdirectories)
- [Get the filename](https://en.cppreference.com/w/cpp/filesystem/path/filename): `for(auto& file : iterator){auto filename = file.path().filename();}`

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
