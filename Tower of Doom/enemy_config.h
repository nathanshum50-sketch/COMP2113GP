#ifndef ENEMY_CONFIG_H
#define ENEMY_CONFIG_H

#include <string>
#include <vector>
#include <map>

using namespace std;

const map<char, float> difficultyMultipliers = {
    {'E', 0.9},  // Easy
    {'M', 1.0},  // Medium  
    {'H', 1.2}   // Hard
};

// based on actual gameplay, the amplifiers can be modified later
const map<string, vector<float>> enemyStatBias = {
    // Format: [STR, CHA, WIS] 
    {"Goblin",    {1.3, 0.7, 0.8}},  // High STR, low CHA
    {"Orc",       {0.6, 1.4, 0.8}},  // High CHA, low WIS
    {"Skeleton",  {0.9, 0.9, 0.9}},  // Balanced
    {"Zombie",    {0.5, 1.1, 1.2}},  // High CHA, low STR
    {"Ghost",     {1.1, 0.8, 1.1}},  // High STR & WIS
    {"Vampire",   {1.0, 1.0, 1.0}},  // All-around
    {"Dragon",    {0.8, 1.3, 0.9}},  // High CHA
    {"Wizard",    {1.0, 0.7, 1.3}},  // High WIS
    {"Knight",    {0.8, 1.1, 1.1}},  // Physical fighter
    {"Archer",    {1.4, 0.8, 1.0}},  // High STR

    {"Skeleton King", {1.6, 1.0, 0.8}}, // High STR, low WIS
    {"Archer Queen",  {1.0, 1.6, 1.2}}, // High CHA, low STR
    {"Dark Lord",     {1.3, 1.3, 1.3}}  // Genrally high stats 
};

const vector<string> regularEnemySet={
	"Goblin", "Orc", "Skeleton", "Zombie", "Ghost", "Vampire", "Dragon",
"Wizard", "Knight", "Archer"
};

const vector<string> bossEnemySet={
	"Skeleton King", "Archer Queen", "Dark Lord" 
};

const map<string, string> enemyText= {

    {"Goblin", "A sneaky goblin approaches with a mischievous grin, clutching a rusty dagger!"},
    {"Orc", "A brutish orc charges forward, roaring with rage and swinging a massive club!"},
    {"Skeleton", "Bones rattle as an armored skeleton emerges from the shadows, sword drawn!"},
    {"Zombie", "A decaying zombie shambles toward you, moaning hungrily with outstretched arms!"},
    {"Ghost", "A spectral form materializes, chilling the air around it with ethereal presence!"},
    {"Vampire", "The vampire glides gracefully from the darkness, eyes glowing with crimson power!"},
    {"Dragon", "Wings spread wide, the ancient dragon unleashes a terrifying roar that shakes the ground!"},
    {"Wizard", "Arcane energy crackles around the powerful wizard as he prepares a devastating spell!"},
    {"Knight", "Armor clanking, the honorable knight stands ready with shield raised and sword steady!"},
    {"Archer", "Eyes sharp and bow taut, the elven archer nocks an arrow with deadly precision!"},
    {"Skeleton King", "The ancient Skeleton King awakens, wielding his mace around it!"},
    {"Archer Queen", "The Archer Queen appears from nowhere, using her bow to take aim!"},
    {"Dark Lord", "The Dark Lord emerges from the shadows, dark energy crackling around his terrifying form!"}

};

#endif