# Lessons Learned

## 21.07.2019 List of Open Source libraries

Stumbled onto a [list](https://en.cppreference.com/w/cpp/links/libs) of Open Source libraries.

## 20.07.2019 git submodules (75)

Had to look up submodules again, so:

~~~sh
# First time
cd external
git submodule add https://github.com/nlohmann/json.git
# and on VM after a pull
git submodule init
git submodule update
~~~

## 20.07.2019 nlohmann/json (75-76)

The syntax is very simple.

~~~c++
// create an empty structure (null)
json j;

// add a number that is stored as double (note the implicit conversion of j to an object)
j["pi"] = 3.141;

// add a Boolean that is stored as bool
j["happy"] = true;

// add a string that is stored as std::string
j["name"] = "Niels";

// add another null object by passing nullptr
j["nothing"] = nullptr;

// add an object inside the object
j["answer"]["everything"] = 42;

// add an array that is stored as std::vector (using an initializer list)
j["list"] = { 1, 0, 2 };

// add another object (using an initializer list of pairs)
j["object"] = { {"currency", "USD"}, {"value", 42.99} };

// instead, you could also write (which looks very similar to the JSON above)
json j2 = {
  {"pi", 3.141},
  {"happy", true},
  {"name", "Niels"},
  {"nothing", nullptr},
  {"answer", {
    {"everything", 42}
  }},
  {"list", {1, 0, 2}},
  {"object", {
    {"currency", "USD"},
    {"value", 42.99}
  }}
};
~~~

Missed

~~~c++
void to_json(json& j, CustomObject const & co)
{
   j = json{ {"my", "representation"} };
}
~~~

which allows the library to automatically loop over containers.

Skipped 76. Again, syntax seems very clear:

~~~c++
//ifile as std::ifstream and jdata as json:
ifile >> jdata;
//looping over top array movies and getting the id:
for (auto & element : jdata.at("movies")){
    auto id = element.at("id").get<unsigned int>();
}
~~~

Exception handling is used for errors. Probably when missing a parameter or having a typemissmatch.

Setup was really simple.

## 19.07.2019 Design Patterns (67-72)

Only thought of solutions and read answers.

- 67: Would have implemented it with just a vector of password validators.
- 68: Wouldn't have used same baseclass for single and combined rules (so basically not used composite).
- 69: Didn't know template method pattern, but would have basically done the same. Probably without the factory on top.
- 70: Didn't know chain of command pattern. Can't think of a problem I encountered where I would have liked to use it. Could be nice in error handling.
- 71: Had basically the same thoughts.
- 72: Would also have used the strategy pattern. Probably would have made price_calculator a function in Order class. A bit less coupled this way. Very similar problem in [Fluent Python](https://github.com/fluentpython/example-code/blob/master/07-closure-deco/strategy_best4.py) with a bit less functionality, but only a few lines of code using decorators (python decorators, not the design pattern).

## 19.07.2019 std::condition_variable and std::unique_lock (66)

Not implemented, only from reading the book answer. See also [CppCoreGuidelines](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rconc-wait) and a more detailed description on [modernescpp](https://www.modernescpp.com/index.php/c-core-guidelines-be-aware-of-the-traps-of-condition-variables).
I think implementing an Event Loop with these constructs should be possible such that an async function doesn't disturb the reading:

~~~c++
sync_stuff();
async_sleep(); //or some expensive operation
continue_sync_stuff_after_async_sleep();
~~~

Example from [cppreference](https://en.cppreference.com/w/cpp/thread/condition_variable):

~~~c++
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex m;
std::condition_variable cv;
std::string data;
bool ready = false;
bool processed = false;

void worker_thread()
{
    // Wait until main() sends data
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, []{return ready;});

    // after the wait, we own the lock.
    std::cout << "Worker thread is processing data\n";
    data += " after processing";

    // Send data back to main()
    processed = true;
    std::cout << "Worker thread signals data processing completed\n";

    // Manual unlocking is done before notifying, to avoid waking up
    // the waiting thread only to block again (see notify_one for details)
    lk.unlock();
    cv.notify_one();
}

int main()
{
    std::thread worker(worker_thread);
    data = "Example data";
    // send data to the worker thread
    {
        std::lock_guard<std::mutex> lk(m);
        ready = true;
        std::cout << "main() signals data ready for processing\n";
    }
    cv.notify_one();
    // wait for the worker
    {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, []{return processed;});
    }
    std::cout << "Back in main(), data = " << data << '\n';
    worker.join();
}
~~~

~~~sh
main() signals data ready for processing
Worker thread is processing data
Worker thread signals data processing completed
Back in main(), data = Example data after processing
~~~

## 18.07.2019 std::priority_queue (66)

Not implemented, only from reading the book answer.

~~~c++
//https://en.cppreference.com/w/cpp/container/priority_queue
#include <queue>

std::priority_queue<int> q;
for(int n : {1,8,5,6,3,4,0,9,7,2})
    q.push(n);
print_queue(q);//9 8 7 6 5 4 3 2 1 0
~~~

## 18.07.2019 futures and async (61)

~~~c++
#include <future>

auto handle = std::async(std::launch::async, function, args...);

//do stuff here

handle.wait(); //in case of function beeing void
auto result = handle.get(); //in case of function having a return value
~~~

Additionally we need to link against pthread.

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
