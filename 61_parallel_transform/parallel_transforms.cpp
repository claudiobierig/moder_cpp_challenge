#include <iostream>
#include <algorithm>
#include <vector>
#include <future>
#include <numeric>
#include <array>
#include <chrono>
#include <random>
#include <assert.h>
#include <thread>

//https://en.cppreference.com/w/cpp/thread/async example parallel_sum
template <typename RandomIt, typename UnaryFunction>
void parallel_loop(RandomIt beg, RandomIt end, UnaryFunction func)
{
    auto len = end - beg;
    if (len < 100000){
        std::transform(beg, end, beg, func);
        return;
    }
    RandomIt mid = beg + len/2;
    auto handle = std::async(std::launch::async,
                             parallel_loop<RandomIt, UnaryFunction>, mid, end, func);
    parallel_loop(beg, mid, func);
    handle.wait();
}

template <typename Container, typename UnaryFunction>
Container parallel_loop(Container c, UnaryFunction func)
{
    parallel_loop(c.begin(), c.end(), func);
    return c;
}

//Book solution
template <typename T, typename F>
std::vector<T> palter(std::vector<T> data, F&& f)
{
   if (data.size() <= 10000)
   {
      std::transform(
         std::begin(data), std::end(data), std::begin(data),
         std::forward<F>(f));
   }
   else
   {
      std::vector<std::thread> threads;
      int thread_count = std::thread::hardware_concurrency();
      auto first = std::begin(data);
      auto last = first;
      auto size = data.size() / thread_count;
      for (int i = 0; i < thread_count; ++i)
      {
         first = last;
         last = i == thread_count - 1 ? std::end(data) : first + size;

         threads.emplace_back([first, last, &f]() {
            std::transform(first, last, first,
               std::forward<F>(f));
         });
      }

      for (int i = 0; i < thread_count; ++i)
         threads[i].join();
   }

   return data;
}

int main()
{
    std::string s("hello");
    parallel_loop(s.begin(), s.end(), [](unsigned char c) -> unsigned char { return std::toupper(c); });
    std::cout << s << '\n';
    std::vector<int> v(1234567, 1);
    parallel_loop(v.begin(), v.end(), [](int i) -> int { return 2*i; });
    std::cout << std::accumulate(v.begin(), v.end(), 0) << "\n";

    //Book example
    //Setup
    const size_t count = 10000000;
    std::vector<int> data(count);
    std::random_device rd;
    std::mt19937 mt;
    auto seed_data = std::array<int, std::mt19937::state_size> {};
    std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
    std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
    mt.seed(seq);
    std::uniform_int_distribution<> ud(1, 100);
    std::generate_n(std::begin(data), count, [&mt, &ud]() {return ud(mt); });
  
    //seq transform
    auto start = std::chrono::system_clock::now();
    auto data1 = data;
    std::transform(data1.begin(), data1.end(), data1.begin(), [](int const e) {return e * e; });
    auto end = std::chrono::system_clock::now();
    auto t1 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "time: " << t1.count() << "ms" << std::endl;

    //parallel
    start = std::chrono::system_clock::now();
    auto result = parallel_loop(data, [](int const e) {return e * e; });
    end = std::chrono::system_clock::now();
    auto t2 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "time: " << t2.count() << "ms" << std::endl;

    //Book solution
    start = std::chrono::system_clock::now();
    auto r2 = palter(data, [](int const e) {return e * e; });
    end = std::chrono::system_clock::now();
    auto t3 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "time: " << t3.count() << "ms" << std::endl;

    assert(data1 == result);
    assert(data1 == r2);
}
