#include "StartView.h"

StartView::StartView(IGameEngine &engine): SupportView(engine)
{}

void
StartView::update()
{
    GameStage stage = engine.stage();
    
    if (stage == GameStage::PLAYERS_REGISTRATION){
        while (!std::cin.eof() && players_registration_view() == FAILURE);
        
    } else if (stage == GameStage::INFRASTRUCTURES_REGISTRATION){
        while (!std::cin.eof() && infrastructures_registration_view() == FAILURE);
        
    } else if (stage == GameStage::PUT_INITIAL_INFRASTRUCTURES){
        while (!std::cin.eof() && initial_infrastructures_view() == FAILURE);
    }
}

int
StartView::join_player_view()
{
    std::string input = get_line("Player name (Format: WORD)");
    std::smatch m;
    
    if (!std::regex_search(input, m, Regexp::WORD)){
        std::cout << "Wrong Input" << std::endl;
        return FAILURE;
    }
    try{
        engine.join_player(m[0]);
    }
    catch (std::invalid_argument &e){
        std::cout << e.what() << std::endl;
        return FAILURE;
    }
    return SUCCESS;
}

int
StartView::players_registration_view()
{
    const Game &game = engine.game();
    size_t num_players = game.num_players();
    std::vector<const std::string> lines = {"Players Registration", ""};
    
    for (uint i = 0; i < num_players; i++){
        lines.push_back(game.player(i).name());
    }
    for (uint i = 0; i < MAX_PLAYERS - num_players; i++){
        lines.push_back("------");
    }
    lines.push_back("");
    
    int i = 0;
    if (num_players < MAX_PLAYERS){
        lines.push_back(std::to_string(i) + " - new player");
        i++;
    }
    if (num_players >= MIN_PLAYERS){
        lines.push_back(std::to_string(i) + " - start game");
        i++;
    }
    lines.push_back(std::to_string(i) + " - quit");
    
    clear();
    window(lines);
    
    std::string input = get_line("Choice");
    std::smatch m;
    
    if (!std::regex_search(input, m, std::regex ("\\b[012]\\b"))){
        std::cout << "Wrong Input" << std::endl;
        return FAILURE;
    }
    
    switch (std::stoi(m[0].str())){
    case 0:
        if (num_players < MAX_PLAYERS){
            while (join_player_view() == FAILURE);
        } else {
            engine.start_game();
        }
        return SUCCESS;
    case 1:
        if (num_players < MAX_PLAYERS &&
            num_players >= MIN_PLAYERS){
            engine.start_game();
        } else {
            exit(SUCCESS);
        }
        return SUCCESS;
    case 2:
        exit(SUCCESS);
    }
    return FAILURE;
}

int
StartView::infrastructures_registration_view()
{
    const Game &game = engine.game();
    
    clear();
    window({"Infrastructures Registration"});
    
    int player_num = -1;
    
    for (uint i =0; i < game.num_players(); i++){
        if (game.player(i).num_roads() != INIT_ROAD_NUMBER ||
            game.player(i).num_towns() != INIT_TOWN_NUMBER ||
            game.player(i).num_cities() != INIT_CITY_NUMBER){
            player_num = i;
            break;
        }
    }
    
    Player &player = game.player(player_num);
    
    if (player.num_roads() < INIT_ROAD_NUMBER){
        window({player.name() + " registers a road"});
    
    } else if (player.num_towns() < INIT_TOWN_NUMBER){
       window({player.name() + " registers a town"});
        
    } else if (player.num_cities() < INIT_CITY_NUMBER){
        window({player.name() + " registers a city"});
    }
    
    std::string input = get_line("Infrastructure Name (Format: WORD)");
    std::smatch m;
    
    if (!std::regex_search(input, m, Regexp::WORD)){
        std::cout << "Wrong Input" << std::endl;
        return FAILURE;
    }
    try {
        if (player.num_roads() < INIT_ROAD_NUMBER){
            engine.register_road(player.name(), m[0]);

        } else if (player.num_towns() < INIT_TOWN_NUMBER){
            engine.register_town(player.name(), m[0]);
        
        } else if (player.num_cities() < INIT_CITY_NUMBER){
            engine.register_city(player.name(), m[0]);
        }
    }
    catch (std::invalid_argument &e){
        std::cout << e.what() << std::endl;
        return FAILURE;
    }
    return SUCCESS;
}

int
StartView::initial_infrastructures_view()
{
    const Player &player = engine.current_player();
    
    clear();
    window({"Put Initial Infrastructures", "", player.name()});
    
    try {
        std::vector<std::string> args = get_build_args("TownName (x, y) CrossCorner");
        
        const std::string town_name = args[0];
        Coord town_coord = to_coord(args[1]);
        CrossCorner corner = to_corner(args[2]);
        
        args = get_build_args("RoadName (x, y) RoadSide");
        
        const std::string road_name = args[0];
        Coord road_coord = to_coord(args[1]);
        RoadSide side = to_side(args[2]);
        
        engine.put_initial_infrastructure(player.name(), town_name, town_coord, corner,
                                          road_name, road_coord, side);
    }
    catch (std::invalid_argument &e){
        std::cout << e.what() << std::endl;
        return FAILURE;
    }
    return SUCCESS;
}




