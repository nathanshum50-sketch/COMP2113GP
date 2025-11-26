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

const map<string, vector<float>> eventProb = {
    // Format: [Event1_prob, Event2_prob, Event3_prob, Event4_prob] (cumulative)
    {"Goblin",    {0.5, 0.8, 1.0}},  
    {"Orc",       {0.4, 0.8, 1.0}},  
    {"Skeleton",  {0.3, 0.7, 1.0}},  
    {"Zombie",    {0.2, 0.7, 1.0}},  
    {"Ghost",     {0.3, 0.6, 1.0}},  
    {"Vampire",   {0.4, 0.7, 1.0}},  
    {"Dragon",    {0.2, 0.6, 1.0}},  
    {"Wizard",    {0.3, 0.5, 1.0}},  
    {"Knight",    {0.4, 0.8, 1.0}},  
    {"Archer",    {0.5, 0.7, 1.0}},  

    {"Skeleton King", {0.3, 0.6, 0.8, 1.0}}, 
    {"Archer Queen",  {0.2, 0.5, 0.8, 1.0}}, 
    {"Dark Lord",     {0.2, 0.45, 0.75, 1.0}}
};

const map<int, vector<string>> eventNames = {
    {0, {"Minor Ambush", "Lost Treasure", "Hidden Trap", "Wandering Merchant"}},
    {1, {"Bandit Raid", "Ancient Relic", "Cursed Ground", "Traveling Bard"}},
    {2, {"Elite Guard Attack", "Legendary Artifact", "Haunted Ruins", "Mysterious Stranger"}},
    {3, {"Dragon's Wrath", "Mythical Treasure", "Demonic Portal", "Enigmatic Sage"}}
};

const map<string, vector<float>> eventEffects = {
    // Format: [STR_mod, CHA_mod, WIS_mod] 
    {"Minor Ambush",      {0.1, 0.0, 0.0}},
    {"Lost Treasure",     {0.0, 0.1, 0.0}},
    {"Hidden Trap",       {0.2, 0.0, 0.0}},
    {"Wandering Merchant",{0.0, 0.2, 0.0}},

    {"Bandit Raid",       {0.15, 0.0, 0.0}},
    {"Ancient Relic",    {0.0, 0.15, 0.0}},
    {"Cursed Ground",    {0.25, 0.0, 0.0}},
    {"Traveling Bard",   {0.0, 0.25, 0.0}},

    {"Elite Guard Attack",{0.2, 0.0, 0.0}},
    {"Legendary Artifact",{0.0, 0.2, 0.1}},
    {"Haunted Ruins",    {0.3, 0.0, 0.1}},
    {"Mysterious Stranger",{0.0, 0.3, 0.1}},

    {"Dragon's Wrath",   {0.3, 0.0, 0.2}},
    {"Mythical Treasure", {0.1, 0.3, 0.2}},
    {"Demonic Portal",   {0.4, 0.0, 0.2}},
    {"Enigmatic Sage",   {0.0, 0.4, 0.3}}
};

const map<string, string> eventFlavorText = {
    {"Minor Ambush", " sets a minor ambush."},
    {"Lost Treasure", " finds lost treasure."},
    {"Hidden Trap", " positions a hidden trap."},
    {"Wandering Merchant", " receives support from a wandering merchant."},

    {"Bandit Raid", " raids with bandits."},
    {"Ancient Relic", " discovers an ancient relic."},
    {"Cursed Ground", " curses the ground."},
    {"Traveling Bard", " is entertained by a traveling bard."},

    {"Elite Guard Attack", " attacks with elite guards."},
    {"Legendary Artifact", " acquires a legendary artifact."},
    {"Haunted Ruins", " feigns retreat towards haunted ruins."},
    {"Mysterious Stranger", " is aided by a mysterious stranger."},

    {"Dragon's Wrath", " unleashes the wrath of a dragon."},
    {"Mythical Treasure", " uncovers mythical treasure."},
    {"Demonic Portal", " opens a demonic portal."},
    {"Enigmatic Sage", " is imparted wisdom by an enigmatic sage."}
};
#endif