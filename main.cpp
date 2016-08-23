#include "ObservableGameEngine.h"
#include "GameEngine.h"
#include "Factory.h"
#include "View.h"

int main()
{
    Factory creator;
    std::unique_ptr<IGameEngine> engine(creator.make_game_engine());
    View view(*engine);

    dynamic_cast<ObservableGameEngine &>(*engine).observer().register_receiver(view);
    
    view.update();
    return 0;
}
