#include <cassert>
#include <vector>
#include <array>
#include <list>
#include <algorithm>

/*
quadratic complexity!
For loglinear following should work: 
- Insert all elements in sorted new Container.
- Iterate through container and check if it is in sorted container.
    - contains_none and contains_any finished after first match
    - contains_all needs to save pairs and check at the end if all where matched
 */

template <typename Container, typename... T>
bool contains_any(Container& c, T&&... args)
{
    return (... || (std::find(c.begin(), c.end(), args) != c.end()));
}

template <typename Container, typename... T>
bool contains_all(Container& c, T&&... args)
{
    return (... && (std::find(c.begin(), c.end(), args) != c.end()));
}

template <typename Container, typename... T>
bool contains_none(Container& c, T&&... args)
{
    return !(contains_any(c, std::forward<T>(args)...));
}

int main()
{
    std::vector<int> v{ 1, 2, 3, 4, 5, 6 };
    assert(contains_any(v, 0, 3, 30));
    std::array<int, 6> a{ { 1, 2, 3, 4, 5, 6 } };
    assert(contains_all(a, 1, 3, 5, 6));
    std::list<int> l{ 1, 2, 3, 4, 5, 6 };
    assert(!contains_none(l, 0, 6));
    assert(!contains_none(l, 1, 7));
}