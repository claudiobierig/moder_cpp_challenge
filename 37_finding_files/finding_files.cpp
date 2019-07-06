#include <iostream>
#include <regex>
#include <filesystem>

int main(int argc, char *argv[]){
    /*
    Input: Regex folder
    stdout: all files that match
     */
    if(argc != 3){
        std::cout << "Takes exactly two arguments:\nregex folder\n";
        std::cout << argc - 1 << " arguments were given:\n";
        for (int i = 1; i < argc; ++i) 
            std::cout << argv[i] << "\n";
        return -1;
    }
    std::regex re {argv[1]};
    std::string_view folder {argv[2]};
    for(auto& p: std::filesystem::recursive_directory_iterator(folder.data()))
    {
        if(std::regex_match(std::string(p.path().filename()), re))
        {
            std::cout << p.path().filename() << '\n';
        }
    }
}