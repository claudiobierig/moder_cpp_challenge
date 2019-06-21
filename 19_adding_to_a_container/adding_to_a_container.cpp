#include <iostream>
#include <vector>
#include <deque>

template <typename Container, typename... T>
void push_back(Container& c, T&&... args)
{
    (c.push_back(args), ...);
}

template <typename Container>
void print(Container& c)
{
    for(const auto& value : c){
        std::cout << value << "\n";
    }
    std::cout << "--------------------\n";
}


int main()
{
    std::vector<int> v = {};
    push_back(v, 1, 2, 3, 4);
    print(v);
    push_back(v, 5);
    print(v);

    std::deque<double> d = {};
    push_back(d, 1.1, 2.2, 3.3, 4.4);
    print(d);
}