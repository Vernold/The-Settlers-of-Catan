#include "SecondView.h"

SecondView::SecondView(IGameEngine &engine): SupportView(engine)
{}

void
SecondView::update()
{
    while (!std::cin.eof() && menu() == FAILURE);
}

int
SecondView::menu()
{
    const Player &player = engine.current_player();
    std::smatch m;
    
    clear();
    window({player.name() + " makes exchanges"});
    window({"0 - exchange with field",
            "1 - request the exchange",
            "2 - Game Information",
            "3 - end exchanges"
    });
    
    std::string input = get_line("Choice (Format: digit [0-3])");
    if (!std::regex_search(input, m, std::regex("\\b[0-3]\\b"))){
        std::cout<< "Wrong input" << std::endl;
        return FAILURE;
    }
    
    switch(std::stoi(m[0]))
    {
        case 0:
            return exchange_with_field_view();
        case 1:
            return exchange_request_view();
        case 2:
            info();
            return FAILURE;
        case 3:
            engine.end_exchanges(player.name());
            return SUCCESS;
    }
    return FAILURE;
}

int
SecondView::exchange_with_field_view()
{
    const Player &player = engine.current_player();
    Resource source, target;
    std::smatch m;
    
    clear();
    window({player.name() + " exchanges with the field"});
    
    std::string input = get_line("Source and target (Format: WORD WORD)");
    
    if (!std::regex_search(input, m, Regexp::WORD)){
        std::cout << "Wrong input" << std::endl;
        return FAILURE;
    }
    
    source = to_resource(m[0]);
    
    input = m.suffix();
    
    if (!std::regex_search(input, m, Regexp::WORD)){
        std::cout << "Wrong input" << std::endl;
        return FAILURE;
    }
    
    target = to_resource(m[0]);
    
    try{
        engine.exchange_with_field(player.name(), source, target);
    }
    catch (std::invalid_argument &e){
        std::cout << e.what() << std::endl;
        return FAILURE;
    }
    return SUCCESS;
}

int
SecondView::exchange_request_view()
{
    const Player &player = engine.current_player();
    std::multiset<Resource> src, trgt;
    std::smatch m;
    int request;
    
    clear();
    window({player.name() + " exchanges with other player"});
    
    std::string name = get_line("Other player (Format: WORD)");
    
    if (!std::regex_search(name, m, Regexp::WORD)){
        std::cout << "Wrong input" << std::endl;
        return FAILURE;
    }
    name = m[0];
    
    std::string source = get_line("Source (Format: {WORD}+)");
    std::string target = get_line("Target (Format: {WORD}+)");
    
    if (!std::regex_search(source, m, Regexp::WORD) ||
        !std::regex_search(target, m, Regexp::WORD)){
        std::cout << "Wrong input" << std::endl;
        return FAILURE;
    }
    
    while (std::regex_search(source, m, Regexp::WORD)){
        src.insert(to_resource(m[0]));
        source = m.suffix();
    }
    
    while (std::regex_search(target, m, Regexp::WORD)){
        trgt.insert(to_resource(m[0]));
        target = m.suffix();
    }
    try{
        request = engine.exchange_players_request(player.name(), name, src, trgt);
    }
    catch (std::invalid_argument &e){
        std::cout << e.what() << std::endl;
        return FAILURE;
    }
    while (!std::cin.eof() && accept_request_view(name, request) == FAILURE);
    return SUCCESS;
}

int
SecondView::accept_request_view(const std::string &name, int request)
{
    std::string src = "Source: ";
    std::string target = "Target: ";
    std::string initiator = "Initiator: " + engine.initiator(request).name();
    std::smatch m;
    
    for (Resource res : engine.src(request)){
        src += to_string(res);
    }
    for (Resource res : engine.target(request)){
        target += to_string(res);
    }
    
    clear();
    window({name + " can accept or decline the request",
            "", initiator, src, target, "",
            "0 - Accept", "1 - Decline"});
    
    std::string input = get_line("Choice (Format: digit [0-1]");
    
    if (!std::regex_search(input, m, std::regex("\\b[01]\\b"))){
        std::cout<< "Wrong input" << std::endl;
        return FAILURE;
    }
    
    if (std::stoi(m[0]) == 0){
        try{
            engine.exchange_players_accept(name, request);
        }
        catch (std::invalid_argument &e){
            std::cout << e.what() << std::endl;
            return FAILURE;
        }
    } else {
        update();
    }
    return SUCCESS;

}


