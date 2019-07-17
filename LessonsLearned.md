# Lessons Learned

## 17.07.2019 linking against pthread (61)

Needed to link against pthread ([Stackoverflow](https://stackoverflow.com/questions/1620918/cmake-and-libpthread)):

~~~cmake
find_package (Threads)
target_link_libraries (parallel_transforms ${CMAKE_THREAD_LIBS_INIT})
~~~

## 17.07.2019 async + features vs threads (61)

No big difference on my Laptop. However async needed a bit of tuning when to stop the recursion.
A correct implementation should be aware of the depth and have the maximal depth depending on `std::thread::hardware_concurrency()` as in the book solution instead of the number of elements (or probably additional to).

## 17.07.2019 Git submodules (43)

Git submodules seemed to be an easier way, compared to ExternalProject_Add. It allows local modification for debugging, VS Code finds the source code, a clean build can be performed without a `git pull` and worked out of the box. Setup on a new PC only requires additional

~~~sh
git submodule init
git submodule update
~~~

## 07.07.2019 ExternalProject_Add (43)

Add a git repo via [CMake](https://cmake.org/cmake/help/latest/module/ExternalProject.html):

~~~CMake
include(ExternalProject)
find_package(Git REQUIRED)

list(APPEND DATE_CMAKE_ARGS
    "-DCMAKE_INSTALL_PREFIX=${EXTERNAL_PATH}"
    "-DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}"
    "-DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}"
)

ExternalProject_Add(
    date
    GIT_REPOSITORY      https://github.com/HowardHinnant/date.git
    GIT_TAG             v2.4.1
    GIT_SHALLOW         1
    CMAKE_ARGS          ${DATE_CMAKE_ARGS}
    PREFIX              ${EXTERNAL_PATH}/date/prefix
    TMP_DIR             ${EXTERNAL_PATH}/date/tmp
    STAMP_DIR           ${EXTERNAL_PATH}/date/stamp
    DOWNLOAD_DIR        ${EXTERNAL_PATH}/date/download
    SOURCE_DIR          ${EXTERNAL_PATH}/date/src
    BINARY_DIR          ${EXTERNAL_PATH}/date/build
)
~~~

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
