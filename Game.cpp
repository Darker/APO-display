#include "Game.h"
#include "ShapeText.h"
#include "threading.h"
#include <mutex>
#include <random>

#include "defines.h"
Game::Game()
    : circle()
    , platform1(Color(255,0,0), GAME_HEIGHT/6, GAME_WIDTH/25, GAME_WIDTH/25, GAME_HEIGHT/2)
    , platform2(Color(0,0,255), GAME_HEIGHT/6, GAME_WIDTH/25, GAME_WIDTH-GAME_WIDTH/13,GAME_HEIGHT/2)
    , mt(rd())
{

    reset();
}


std::vector<Shape*> Game::getShapes()
{
    std::vector<Shape*> returnArray;
    // LOCK MUTEX!
    // copy every shape into new array and return that array
    shapeMutex.lock();
    returnArray.push_back(new ShapeText(pl1_str, Color::RED, GAME_WIDTH/2 - 30, 30, "diablo.ttf"));
    returnArray.push_back(new ShapeText(pl2_str, Color::RED, GAME_WIDTH/2 + 30, 30, "diablo.ttf"));
    returnArray.push_back(circle.cloneNew());
    returnArray.push_back(platform1.cloneNew());
    returnArray.push_back(platform2.cloneNew());
    shapeMutex.unlock();
    return returnArray;
}

bool Game::tick()
{
    shapeMutex.lock();

     pl1_str = std::to_string(player1_score);
     pl2_str = std::to_string(player2_score);

    double deltaT = sinceLastTick()/1000.0;
    const double rotations_per_second = 0.05;

    if(circle.isPlayable() == -1){
        std::uniform_real_distribution<double> speed(-100, 100);

        player2_score++;
        circle.x=GAME_WIDTH/2;
        circle.y = GAME_HEIGHT/2;
        circle.vx=speed(this->rd) ;//(speed(mt));
        circle.vy =speed(this->rd) ;//(speed(mt));
    }

    else if(circle.isPlayable() == 1){
        std::uniform_real_distribution<double> speed(0.0, 100);
            player1_score++;
            circle.x=GAME_WIDTH/2;
            circle.y = GAME_HEIGHT/2;
            circle.vx=speed(this->rd) ;//(speed(mt));
            circle.vy =speed(this->rd) ;//(speed(mt));
        }

    circle.move(deltaT);

    platform1.y += button1.moveDelta();
    platform2.y += button3.moveDelta();

    platform1.checky();
    platform2.checky();



    if(platform1.intersects_left(circle) || platform2.intersects_right(circle)){
        circle.bounce_platform();

    }

    if( platform2.intersects_up(circle) || platform2.intersects_bottom(circle) || platform1.intersects_up(circle) || platform1.intersects_bottom(circle)){
        circle.bounce_ceiling();
        //circle.bounce_platform();
    }
    shapeMutex.unlock();


    if(player1_score == 10 || player2_score == 10)
        return false;
    else if (button1.isClicked() && button2.isClicked() && button3.isClicked())
        return false;

    return true;
}

bool Game::render(std::vector<Color> &pixmap, int pixmapWidth, int pixmapHeight)
{
//    ShapeText pl1sc;
//    ShapeText pl2sc;
    // LOCK MUTEX!
    // copy every shape into new array and return that array
    shapeMutex.lock();
//    pl1sc = new ShapeText(pl1_str, Color::RED, GAME_WIDTH/2 - 30, 30, "diablo.ttf"));
//    pl2sc = new ShapeText(pl2_str, Color::RED, GAME_WIDTH/2 - 30, 30, "diablo.ttf"));
    ShapeText(pl1_str, Color::RED, GAME_WIDTH/2 - 30, 30, "diablo.ttf").render(pixmap, pixmapWidth, pixmapHeight);
    ShapeText(pl2_str, Color::RED, GAME_WIDTH/2 + 30, 30, "diablo.ttf").render(pixmap, pixmapWidth, pixmapHeight);

    circle.render(pixmap, pixmapWidth, pixmapHeight);
    platform1.render(pixmap, pixmapWidth, pixmapHeight);
    platform2.render(pixmap, pixmapWidth, pixmapHeight);
    shapeMutex.unlock();
    return true;
}

void Game::reset(){

    player1_score = 0;
    player2_score = 0;

    std::uniform_real_distribution<double> speed(0.0, 100);


    circle = Circle((double)(GAME_WIDTH/2), (double)(GAME_HEIGHT/2), (double)(speed(mt)), (double)(speed(mt)), (int)10);

}
