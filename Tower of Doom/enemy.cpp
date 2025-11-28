#include "enemy.h"
#include "enemy_config.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "header.h" //Oliver's parts' header, as I used his qual_prob function

using namespace std;

bool randomInitialized = false;

// Creates a random enemy and prints flavor text
string generateRandomEnemy(int level, bool isBossRound) {
    if (!randomInitialized) {
        srand(time(0));
        randomInitialized = true;
    }
    
    string enemyType;
    
    if (isBossRound) {
        switch(level) {
            case 1: enemyType = "Skeleton King"; break;
            case 2: enemyType = "Archer Queen"; break;
            case 3: enemyType = "Dark Lord"; break;
            default: enemyType = "Skeleton King";
        }
    } else {
        int enemyIndex = rand() % regularEnemySet.size();
        enemyType = regularEnemySet[enemyIndex];
    }
    
    cout << "\n" << enemyText.at(enemyType) << "\n" << endl;
    return enemyType;
}

//  Generates enemy card 
Card generateEnemyCard(string enemy, Card* cardPoolHead, char difficulty) {
    if (!randomInitialized) {
        srand(time(0));
        randomInitialized = true;
    }
    
    // Convert char difficulty to int, or to be changed if difficulty is an int
    int diffInt;
    if(difficulty == 'E' || difficulty == 'e') {
        diffInt = 1;
    } else if(difficulty == 'H' || difficulty == 'h') {
        diffInt = 3;
    } else {
        diffInt = 2;
    }
    
    // Determine target rarity based on enemy type
    int targetRarity;
    if (enemy == "Skeleton King" || enemy == "Archer Queen" || enemy == "Dark Lord") {
        if(enemy == "Skeleton King") {
            targetRarity = 2;
        } else if(enemy == "Archer Queen") {
            targetRarity = 3;
        } else {
            targetRarity = 4;
        }
    } else {
        targetRarity = diffInt - 1; 
    }
    
    // Use the same quality selection as player drawing as in Oliver's program
    int selectedRarity;
    for (selectedRarity = 0; selectedRarity < 5; selectedRarity++) {
        if (rand() % 1000 < qual_prob(selectedRarity, diffInt) * 1000) break;
    }
    
    if (enemy == "Skeleton King" || enemy == "Archer Queen" || enemy == "Dark Lord") {
        selectedRarity = targetRarity;
    }
    
    // exact card numbers are to be ammended, this part is just for reference
    int cardno;
    switch (selectedRarity) {
        case 0:
            cardno = rand() % 33 + 1;
            break;      // Cards 001-033 (Rarity 0)
        case 1:
            cardno = rand() % 29 + 34;
            break;     // Cards 034-062 (Rarity 1)  
        case 2:
            cardno = rand() % 19 + 63;
            break;     // Cards 063-081 (Rarity 2)
        case 3:
            cardno = rand() % 15 + 82;
            break;     // Cards 082-096 (Rarity 3)
        case 4:
            cardno = rand() % 3 + 97;
            break;     // Cards 097-099 (Rarity 4)
        default:
            cardno = rand() % 33 + 1;
            break;
    }
    // I assumed Card 000 (rarity 5) is for players only - enemies can't draw it

    Card* current = cardPoolHead;
    Card* selectedCard = nullptr;
    
    while (current != nullptr) {
        if (current->card_number == cardno) {
            selectedCard = current;
            break;
        }
        current = current->next;
    }
    
    // If card not found, get first card
    if (selectedCard == nullptr) {
        selectedCard = cardPoolHead;
        if (selectedCard != nullptr && selectedCard->card_number == 0) {
            selectedCard = selectedCard->next;
            if (selectedCard == nullptr) {
                selectedCard = cardPoolHead;
            }
        }
    }
    
    // Create a new enemyCard with modified stats
    Card* enemyCard = new Card;
    enemyCard->card_number = selectedCard->card_number;
    enemyCard->card_rarity = selectedCard->card_rarity;
    enemyCard->card_name = enemy + "'s " + selectedCard->card_name; //or, if we prefer not to adjust the name of the card drawn, I'll change later
    
    // Apply stat biases [STR, CHA, WIS]
    vector<float> biases = enemyStatBias.at(enemy);
    enemyCard->card_STR = static_cast<int>(selectedCard->card_STR * biases[0]);
    enemyCard->card_CHA = static_cast<int>(selectedCard->card_CHA * biases[1]);
    enemyCard->card_WIS = static_cast<int>(selectedCard->card_WIS * biases[2]);
    
    float roll = static_cast<float>(rand()) / RAND_MAX;
    bool event = (roll > (2 - diffInt)/(targetRarity+1)); // depends on difficulty and target rarity

    if(event) {
        // Determine event based on enemy type
        vector<float> probs = eventProb.at(enemy);
        int eventIndex = 0;
        roll = static_cast<float>(rand()) / RAND_MAX;
        for (size_t i = 0; i < probs.size(); i++) {
            if (roll <= probs[i]) {
                eventIndex = i;
                break;
            }
        }
        
        string eventName = eventNames.at(eventIndex)[rand() % eventNames.at(eventIndex).size()];
        vector<float> effects = eventEffects.at(eventName);
        
        cout << enemy << eventFlavorText.at(eventName) << endl;
        
        enemyCard->card_STR += static_cast<int>(selectedCard->card_STR * effects[0]);
        enemyCard->card_CHA += static_cast<int>(selectedCard->card_CHA * effects[1]);
        enemyCard->card_WIS += static_cast<int>(selectedCard->card_WIS * effects[2]);
        // Apply event effects to enemy stats later during card generation
        // This part will be handled after selecting the base card
    }

    // Ensure minimum stats of 1
    if (enemyCard->card_STR < 1) enemyCard->card_STR = 1;
    if (enemyCard->card_CHA < 1) enemyCard->card_CHA = 1;
    if (enemyCard->card_WIS < 1) enemyCard->card_WIS = 1;
    
    enemyCard->next = nullptr;
    
    return *enemyCard;
}

// Compares player and enemy stats
string battlePlayer(Card playerCard, Card enemyCard, string chosenStat) {

    int playerStat, enemyStat;
    
    if (chosenStat == "STR") {
        playerStat = playerCard.card_STR;
        enemyStat = enemyCard.card_STR;
    } else if (chosenStat == "CHA") {
        playerStat = playerCard.card_CHA;
        enemyStat = enemyCard.card_CHA;
    } else if (chosenStat == "WIS") {
        playerStat = playerCard.card_WIS;
        enemyStat = enemyCard.card_WIS;
    } else {
        return "INVALID";
    }
    
    cout << "Your " << chosenStat << ": " << playerStat << " vs "; //If message is not prefered, this part is to be deleted
    cout << "Enemy " << chosenStat << ": " << enemyStat << endl;
    
    if (playerStat > enemyStat) return "VICTORY";
    if (playerStat < enemyStat) return "DEFEAT";
    return "DRAW";

}


