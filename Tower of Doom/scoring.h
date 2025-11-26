#ifndef SCORING_H
#define SCORING_H

#include <string>
#include "header.h"   // Card

using namespace std;

struct GameState {
    int hp;
    int level;
    int round;
    char difficulty;
    int score;

    GameState() : hp(100), level(1), round(1), difficulty('M'), score(0) {}
    void savePlayer(const string &filename);
    void loadPlayer(const string &filename);
    // Update score ("VICTORY", "DEFEAT", "DRAW")
    void updateHighScore(const string &filename);
    void applyBattleResult(const string &battleResult, int damageIfDefeat);
    int levelBonus();
};

inline float getDifficultyMultiplier(char diff) {
    if(diff == 'E' || diff == 'e') return 0.9f;
    if(diff == 'H' || diff == 'h') return 1.2f;
    return 1.0f;
}

int computeDamage(const Card &player, const Card &enemy, const string &chosenStat, char difficulty);

int loadHighScore(const string &filename);
#endif