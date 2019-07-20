#include <iostream>
#include <fstream>
#include <iomanip>
#include <nlohmann/json.hpp>

// for convenience
using json = nlohmann::json;

class CastMember{
public:
    CastMember() = delete;
    explicit CastMember(std::string name_, std::string star_) : name(name_), star(star_){};
    json get_json() const;
private:
    std::string name;
    std::string star;
};

class Director{
public:
    Director() = delete;
    explicit Director(std::string name_) : name(name_){};
    json get_json() const;
private:
    std::string name;
};

class Writer{
public:
    Writer() = delete;
    explicit Writer(std::string name_) : name(name_){};
    json get_json() const;
private:
    std::string name;
};

class Movie{
public:
    Movie() = delete;
    explicit Movie(std::string title_, int year_, int length_) : title(title_), year(year_), length(length_), id(next_id){next_id++;};
    void add_cast_member(CastMember castMember){castMembers.push_back(castMember);};
    void add_director(Director director){directors.push_back(director);};
    void add_writer(Writer writer){writers.push_back(writer);};
    json get_json() const;
private:
    static int next_id;

    std::string title;
    int year;
    int length;
    int id;
    std::vector<CastMember> castMembers;
    std::vector<Director> directors;
    std::vector<Writer> writers;
};

int Movie::next_id = 0;

json CastMember::get_json() const{
    return {
        {"name", name},
        {"star", star}
    };
}

json Director::get_json() const{
    return {
        {"name", name}
    };
}

json Writer::get_json() const{
    return {
        {"name", name}
    };
}

json Movie::get_json() const{
    json result = {
        {"id", id},
        {"title", title},
        {"year", year},
        {"length", length}
    };
    result["cast"] = json::array();
    for(const auto& castMember : castMembers){
        result["cast"].push_back(castMember.get_json());
    }
    result["directors"] = json::array();
    for(const auto& director : directors){
        result["directors"].push_back(director.get_json());
    }
    result["writers"] = json::array();
    for(const auto& writer : writers){
        result["writers"].push_back(writer.get_json());
    }
    return result;
}

json get_json(std::vector<Movie>& movies){
    json result;
    result["movies"] = json::array();
    
    for(const auto& movie : movies){
        result["movies"].push_back(movie.get_json());
    }
    return result;
}

void write_to_file(json& j, std::string filename){
    std::ofstream o(filename);
    o << std::setw(4) << j << std::endl;
}

int main(){
    std::vector<Movie> movies;
    Movie m("Forest Gump", 1994, 202);
    m.add_cast_member(CastMember("Forrest Gump", "Tom Hanks"));
    m.add_cast_member(CastMember("Mrs. Gump", "Sally Field"));
    m.add_cast_member(CastMember("Jenny Curran", "Robin Wright"));
    m.add_cast_member(CastMember("Bubba Blue", "Mykelti Williamson"));
    m.add_director(Director("Robert Zemeckis"));
    m.add_writer(Writer("Winston Groom"));
    m.add_writer(Writer("Eric Roth"));
    Movie m2("Hello", 123, 435);
    movies.push_back(m);
    movies.push_back(m2);
    json j = get_json(movies);
    write_to_file(j, "movies.json");
    return 0;
}
