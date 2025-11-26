#ifndef ENEMY_H
#define ENEMY_H

#include <string>

using namespace std;

struct Card;

string generateRandomEnemy(int level, bool isBossRound);
Card generateEnemyCard(string enemy, Card* cardPoolHead, char difficulty);
string battlePlayer(Card playerCard, Card enemyCard, string chosenStat);

#endif