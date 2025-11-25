#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>
using namespace std;

char startPage(string difficulty, string round, string level, int highScore, bool printContinue);
char chooseDifficulty();
char chooseCard(string cardOne, string cardTwo, string cardThree);
char chooseStat(int firstStat, int secondStat, int thirdStat, string cardName);
void contest(int firstStatPlayer, int secondStatPlayer, int thirdStatPlayer, int firstStatEnemy, int secondStatEnemy, int thirdStatEnemy, int health, int damage, bool win, int level, int round, string enemyName);
void lose();
char completeLevel();
char completeAllLevel();

#endif