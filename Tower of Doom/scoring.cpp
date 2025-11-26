#include "scoring.h"
#include <fstream>
#include <cmath>
#include <iostream>

using namespace std;

int computeDamage(const Card &player, const Card &enemy, const string &chosenStat, char difficulty)
{
    int p = 0, e = 0;

    if (chosenStat == "STR") {
        p = player.card_STR;
        e = enemy.card_STR;
    } else if (chosenStat == "CHA") {
        p = player.card_CHA;
        e = enemy.card_CHA;
    } else if (chosenStat == "WIS") {
        p = player.card_WIS;
        e = enemy.card_WIS;
    } else {
        return 0;
    }

    int diff = e - p;
    if (diff < 0) diff = 0;   // player stronger, treat as 0 base
    if (diff < 5) diff = 5;   // minimum base damage

    float mult = getDifficultyMultiplier(difficulty);
    int dmg = static_cast<int>(std::round(diff * mult));
    if (dmg < 1) dmg = 1;

    return dmg;
}

void GameState::applyBattleResult(const string &battleResult, int damageIfDefeat)
{
    float mult = getDifficultyMultiplier(this->difficulty);

    if (battleResult == "VICTORY") {
        int base = 1;
        int pts = int(base * mult + 0.5);
        if (pts < 1) pts = 1;
        this->score += pts;
    } 
    else if (battleResult == "DEFEAT") {
        this->hp -= damageIfDefeat;
        if (this->hp < 0) this->hp = 0;
    }
    // DRAW: no changes
}


int GameState::levelBonus()
{
    float mult = getDifficultyMultiplier(this->difficulty);
    int base = 10;
    int bonus = int(base * mult + 0.5);
    if (bonus < 1) 
        bonus = 1;
    return bonus;
}

void GameState::updateHighScore(const string &filename)
{
    int previousHighScore;
    int currentScore = this->score;
    ifstream fin(filename.c_str());
    if (fin) {
        fin >> previousHighScore;
        fin.close();
    } else {
        previousHighScore = 0;
    }

    if (currentScore > previousHighScore) {
        ofstream fout(filename.c_str());
        if (!fout) {
            cerr << "Error: cannot write high score file.\n";
            return;
        }
        fout << currentScore << endl;
        fout.close();
        return;
    }
    return;
}

void GameState::savePlayer(const string &filename) {
    updateHighScore("highscore.txt");
    ofstream fout(filename.c_str());
    if (!fout) {
        cerr << "Error: cannot save player.\n";
        return;
    }
    fout << this->hp << endl;
    fout << this->level << endl;
    fout << this->round << endl;
    fout << this->difficulty << endl;
    fout << this->score << endl;
    fout.close();
    cout << "Successfully saved player.\n";
}

void GameState::loadPlayer(const string &filename) {
    updateHighScore("highscore.txt");
    ifstream fin(filename.c_str());
    if (!fin) {
        // File doesn't exist, reset to defaults using the constructor
        *this = GameState();
        cout << "Resetting to defaults." << endl;
        return;
    }
    
    // Try to read all values
    if (!(fin >> this->hp >> this->level >> this->round >> this->difficulty >> this->score)) {
        // Failed to read data, reset to defaults
        *this = GameState();
        fin.close();
        cout << "Resetting to defaults." << endl;
        return;
    }
    
    // Successfully read data, update member variables
    cout << "Successfully loaded player stats." << endl;
}

int loadHighScore(const string &filename) {
    ifstream fin(filename);
    if (!fin) {
        return 0;  // Return 0 if file doesn't exist or can't be opened
        cout << "High score file not found. Returning 0." << endl;
    }
    
    int highScore;
    if (!(fin >> highScore)) {
        // If reading fails (e.g., file contains non-numeric data)
        cout << "Error reading high score. Returning 0." << endl;
        return 0;
    }
    
    return highScore;
}