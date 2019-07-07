#include <iostream>

#include <date/date.h>

int main(){
    if(date::day{1}.ok()){
        std::cout << "ok\n";
    }
    std::cout << "meeting times\n";
}