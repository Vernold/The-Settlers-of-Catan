#include "ThirdView.h"

ThirdView::ThirdView(IGameEngine &engine): SupportView(engine)
{}

void
ThirdView::update()
{
    if (engine.stage() == GameStage::STAGE3){
        while (!std::cin.eof() && menu() == FAILURE);
    } else {
        winner_view();
    }
}

int
ThirdView::menu()
{
    const Player &player = engine.current_player();
    std::smatch m;
    
    clear();
    window({player.name() + " builds something", ""});
    window({"", "0 - build a road",
            "1 - build a town",
            "2 - build a city",
            "3 - Game Information",
            "4 - next player"});
    
    std::string input = get_line("Choice (Format: digit [0-4])");
    if (!std::regex_search(input, m, std::regex("\\b[0-4]\\b"))){
        std::cout<< "Wrong input" << std::endl;
        return FAILURE;
    }
    
    switch(std::stoi(m[0].str()))
    {
        case 0:
            return build_view("road");
        case 1:
            return build_view("town");
        case 2:
            return build_view("city");
        case 3:
            info();
            return FAILURE;
        case 4:
            engine.next_player(player.name());
            return SUCCESS;
    }
    return FAILURE;
}

int
ThirdView::build_view(const std::string &type) const
{
    const Player &player = engine.current_player();
    
    clear();
    window({player.name() + " builds a " + type});
    
    try {
        if (type == "town") {
            auto args = get_build_args("TownName (x, y) CrossCorner");
            
            engine.build_town(player.name(), args[0],
                              to_coord(args[1]), to_corner(args[2]));
        } else if (type == "road"){
            auto args = get_build_args("RoadName (x, y) RoadSide");
            
            engine.build_road(player.name(), args[0],
                              to_coord(args[1]), to_side(args[2]));
        } else if (type =="city"){
            auto args = get_build_args("CityName (x, y) CrossCorner");
            
            engine.build_city(player.name(), args[0],
                              to_coord(args[1]), to_corner(args[2]));
        } else {
            throw std::invalid_argument("Wrong type");
        }
    }
    catch (std::invalid_argument &e){
        std::cout << e.what() << std::endl;
        return FAILURE;
    }
    return SUCCESS;
}

void
ThirdView::winner_view() const
{
    const Player &player = engine.winner();
    clear();
    window({player.name() + " WINS!!!", "CONGRADUATIONS!!!"});
    
    while (get_line("Please push ENTER to quit") != "");
    exit(SUCCESS);
}




