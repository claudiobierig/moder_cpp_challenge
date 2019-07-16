#include "date/tz.h"
#include <iostream>

int main()
{
    //Example from documentation
    //Remaining task seems trivial, skip rest of exercise
    using namespace date;
    using namespace date::literals;
    using namespace std::chrono_literals;
    auto meet_nyc = make_zoned("America/New_York", date::local_days{Monday[1]/May/2016} + 9h);
    auto meet_lon = make_zoned("Europe/London",    meet_nyc);
    auto meet_syd = make_zoned("Australia/Sydney", meet_nyc);
    std::cout << "The New York meeting is " << meet_nyc << '\n';
    std::cout << "The London   meeting is " << meet_lon << '\n';
    std::cout << "The Sydney   meeting is " << meet_syd << '\n';
}
 
