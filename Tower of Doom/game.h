#ifndef GAME_H
#define GAME_H

using namespace std;

#include "enemy.h"
#include "scoring.h"
#include "interface.h"
#include "header.h"
#include <string>

class Game
{
public:
    GameState state;
    Card* player_cards;
    Card* enemy_cards;
    Card* all_cards;
    string enemy;
public:
    Game();
    void init_game();
    void main_menu();
    void select_diff();
    void init_level();
    void init_round(bool newEnemy);
    void lost();
    void won();
    void main_game();
};

#endif