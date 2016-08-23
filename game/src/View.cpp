#include "View.h"

View::View(IGameEngine &engine): SupportView(engine)
{
    start_view.reset(new StartView(engine));
}

void
View::update()
{
    GameStage stage = engine.stage();
    
    /* StartView */
    if (start_view && stage != GameStage::STAGE1_DICE) {
        start_view->update();
        
    /* FirstView */
    } else if (start_view && stage == GameStage::STAGE1_DICE) {
        info();
        first_view.reset(new FirstView(engine));
        delete start_view.release();
        first_view->update();
    
    } else if (first_view && stage != GameStage::STAGE2) {
        first_view->update();
        
    /* SecondView */
    } else if (first_view && engine.stage() == GameStage::STAGE2){
        second_view.reset(new SecondView(engine));
        delete first_view.release();
        second_view->update();
        
    } else if (second_view && stage != GameStage::STAGE3) {
        second_view->update();
    /* ThirdView */
    } else if (second_view && engine.stage() == GameStage::STAGE3){
        third_view.reset(new ThirdView(engine));
        delete second_view.release();
        third_view->update();
        
    } else if (third_view && stage != GameStage::STAGE1_DICE) {
        third_view->update();
        
    } else if (third_view && engine.stage() == GameStage::STAGE1_DICE) {
        first_view.reset(new FirstView(engine));
        delete third_view.release();
        first_view->update();
    }
}