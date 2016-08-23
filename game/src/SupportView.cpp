#include "SupportView.h"

SupportView::SupportView(IGameEngine &_engine): engine(_engine)
{}

std::string
SupportView::get_line(const std::string &str) const noexcept
{
    std::string input;
    std::cout << "[ " << str << " ]: ";
    std::getline(std::cin, input);
    return input;
}

void
SupportView::out_line(size_t len, char c) const noexcept
{
    std::cout << '=';
    for (uint i = 0; i < len; i++){
        std::cout << c;
    }
    std::cout << '=' << std::endl;
}
    
void
SupportView::out_string(const size_t len, const std::string &str) const noexcept
{
    size_t indent = (len - str.size()) >> 1;
    
    std::cout << '=';
    
    for (uint i = 0; i < indent; i++){
        std::cout << ' ';
    }
    
    std::cout << str;
    
    for (uint i = 0; i < (indent + (len - str.size()) % 2); i++){
        std::cout << ' ';
    }
    
    std::cout << '=' << std::endl;
}

void
SupportView::clear() const noexcept
{
    for (uint i = 0; i < 5; i++){
        std::cout << std::endl;
    }
}

void
SupportView::window(const std::vector<const std::string> &lines) const noexcept
{
    size_t window_size = 0;
    
    for (std::string str : lines){
        if (str.size() > window_size){
            window_size = str.size();
        }
    }
    window_size += 2;
    
    out_line(window_size, '=');
    out_line(window_size,' ');
    
    for (std::string str : lines){
        out_string(window_size, str);
    }
    out_line(window_size,' ');
    out_line(window_size, '=');
}

std::string
SupportView::to_upper(const std::string &str) const noexcept
{
    std::stringstream s;
    
    for (char c : str){
        s << toupper(c);
    }
    return s.str();
}
    
Resource
SupportView::to_resource(const std::string &str) const
{
    std::string resource = str;
    std::transform(resource.begin(), resource.end(),
                   resource.begin(), ::toupper);
    
    if (resource == "WOOL"){
        return Resource::WOOL;
        
    } else if (resource == "WOOD") {
        return Resource::WOOD;
        
    } else if (resource == "CLAY") {
        return Resource::CLAY;
    
    } else if (resource == "ORE"){
        return Resource::ORE;
    
    } else if (resource == "GRAIN"){
        return Resource::GRAIN;
    }
    throw std::invalid_argument("Wrong input");
}

CrossCorner
SupportView::to_corner(const std::string &str) const
{
    std::string corner = str;
    std::transform(corner.begin(), corner.end(),
                   corner.begin(), ::toupper);
    
    if (corner == "TOP"){
        return CrossCorner::TOP;
    
    } else if (corner == "BOTTOM"){
        return CrossCorner::BOTTOM;
    }
    throw std::invalid_argument("Wrong input");
}

RoadSide
SupportView::to_side(const std::string &str) const
{
    std::string side = str;
    std::transform(side.begin(), side.end(),
                   side.begin(), ::toupper);
    
    if (side == "UP"){
        return RoadSide::UP;
    
    } else if (side == "RIGHT"){
        return RoadSide::RIGHT;
    
    } else if (side == "DOWN"){
        return RoadSide::DOWN;
    }
    throw std::invalid_argument("Wrong input");
}

const std::string
SupportView::to_string(Resource resource) const
{
    if (resource == Resource::WOOL){
        return "WOOL ";
        
    } else if (resource == Resource::WOOD) {
        return "WOOD ";
        
    } else if (resource == Resource::CLAY) {
        return "CLAY ";
        
    } else if (resource == Resource::ORE){
        return "ORE ";
        
    } else if (resource == Resource::GRAIN){
        return "GRAIN ";
    }
    return "";
}
    
std::vector<std::string>
SupportView::get_build_args(const std::string &mes) const 
{
    std::vector<std::string> args;
    std::string input = get_line(mes + " (Format: WORD COORD WORD)");
    std::smatch m;
    
    if (!std::regex_search(input, m, Regexp::WORD)){
        throw std::invalid_argument("Wrong input");
    }
    args.push_back(m[0]);
    input = m.suffix();
    
    if (!std::regex_search(input, m, Regexp::COORD)){
        throw std::invalid_argument("Wrong input");
    }
    args.push_back(m[0]);
    
    input = m.suffix();
    if (!std::regex_search(input, m, Regexp::WORD)){
        throw std::invalid_argument("Wrong input");
    }
    
    args.push_back(m[0]);
    return args;
}

Coord
SupportView::to_coord(const std::string &c) const
{
    std::string coord = c;
    std::smatch m;
    
    std::regex_search(coord, m, Regexp::I);
    int x = std::stoi(m[0]);
    
    coord = m.suffix();
    
    std::regex_search(coord, m, Regexp::I);
    int y = std::stoi(m[0]);
    
    return Coord(x, y);
}

void
SupportView::info() const
{
    const Game &game = engine.game();
    const ResourcesHolder &bank = game.field().bank();
    
    clear();
    window({"Current Game Information"});
    
    for (uint i = 0; i < game.num_players(); i++) {
        Player &p = game.player(i);
        window({p.name(),
            "GRAIN: " + std::to_string(p.bank().resources(Resource::GRAIN)),
            "CLAY: " + std::to_string(p.bank().resources(Resource::CLAY)),
            "ORE: " + std::to_string(p.bank().resources(Resource::ORE)),
            "WOOL: " + std::to_string(p.bank().resources(Resource::WOOL)),
            "WOOD: " + std::to_string(p.bank().resources(Resource::WOOD)), "",
            "SCORES: " + std::to_string(engine.score(p.name()))
        });
    }
    window({"     Game Bank     ",
        "GRAIN: " + std::to_string(bank.resources(Resource::GRAIN)),
        "CLAY: " + std::to_string(bank.resources(Resource::CLAY)),
        "ORE: " + std::to_string(bank.resources(Resource::ORE)),
        "WOOL: " + std::to_string(bank.resources(Resource::WOOL)),
        "WOOD: " + std::to_string(bank.resources(Resource::WOOD))
    });
}
