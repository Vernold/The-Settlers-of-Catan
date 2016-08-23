#include "FirstView.h"

FirstView::FirstView(IGameEngine &engine): SupportView(engine)
{}

void
FirstView::update()
{
    GameStage stage = engine.stage();
    
    if (stage == GameStage::STAGE1_DICE){
        while (!std::cin.eof() && make_dice_view() == FAILURE);
        
    } else if (stage == GameStage::STAGE1_DROP_RESOURCES){
        while (!std::cin.eof() && drop_resources_view() == FAILURE);
        
    } else if (stage == GameStage::STAGE1_MOVE_ROBBER){
        while (!std::cin.eof() && move_robber_view() == FAILURE);
    
    } else if (stage == GameStage::STAGE1_ROBBING){
        while (!std::cin.eof() && rob_view() == FAILURE);
    }
}

int
FirstView::make_dice_view()
{
    const Player &player = engine.current_player();
    std::smatch m;
    
    clear();
    window({player.name() + " makes dice!"});
    
    std::string input = get_line("Dice (Format: Number in [2, 12])");
    
    if (!std::regex_search(input, m, std::regex("\\b1?[0-9]\\b"))){
        std::cout << "Wrong Input" << std::endl;
        return FAILURE;
    }
    
    try {
        engine.make_dice(player.name(), std::stoi(m[0]));
    }
    catch (std::invalid_argument &e){
        std::cout << e.what() << std::endl;
        return FAILURE;
    }
    return SUCCESS;
}

int
FirstView::drop_resources_view()
{
    const Player &player = engine.current_player();
    std::string name, resource;
    std::smatch m;
    
    clear();
    info();
    window({player.name() + " made seven!"});
    window({"Drop resources"});
    
    std::string input = get_line("Name & resource to drop (Format: WORD WORD)");
    
    if (!std::regex_search(input, m, Regexp::WORD)){
        std::cout << "Wrong Input" << std::endl;
        return FAILURE;
    }
    name = m[0];
    input = m.suffix();
    
    if (!std::regex_search(input, m, Regexp::WORD)){
        std::cout << "Wrong Input" << std::endl;
        return FAILURE;
    }
    resource = m[0];
    
    try{
        engine.drop_resource(name, to_resource(resource));
    }
    catch (std::invalid_argument &e){
        std::cout << e.what() << std::endl;
        return FAILURE;
    }
    return SUCCESS;
}

int
FirstView::move_robber_view()
{
    const Player &player = engine.current_player();
    std::smatch m;
    
    clear();
    window({player.name() + " made seven!"});
    window({player.name() + " moves the robber"});
    
    std::string input = get_line("Coord (Format: (x, y) )");
    
    if (!std::regex_search(input, m, Regexp::COORD)){
        std::cout << "Wrong Input" << std::endl;
        return FAILURE;
    }
    try {
        engine.move_robber(player.name(), to_coord(m[0].str()));
    }
    catch (std::invalid_argument &e){
        std::cout << e.what() << std::endl;
        return FAILURE;
    }
    return SUCCESS;
}

int
FirstView::rob_view()
{
    const Player &player = engine.current_player();
    std::smatch m;
    
    clear();
    window({player.name() + " made seven!"});
    window({player.name() + " is going to rob"});
 
    std::string input = get_line("Victim Name (Format: WORD)");
    
    if (!std::regex_search(input, m, Regexp::WORD)){
        std::cout << "Wrong Input" << std::endl;
        return FAILURE;
    }
    try {
        engine.rob(player.name(), m[0].str());
    }
    catch (std::invalid_argument &e){
        std::cout << e.what() << std::endl;
        return FAILURE;
    }
    return SUCCESS;
}

