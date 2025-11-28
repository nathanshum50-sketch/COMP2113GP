//interface.cpp
#include "interface.h"
#include <iostream>
#include <sstream>

/*
Here are my notes for developing my script that may be useful during script integration:
It is expected that ...
- all card names are composed of a maximum of 4 words, and each word is composed of a maximum of 16 letters.
- each card name is composed of a maximum of 30 characters (spaces included).
- all enemy names are composed of a maximum of 3 words, and each word is composed of a maximum of 16 letters.
- all arguments are valid and have been verified before being passed.

And ...
- All program return only after user has submitted a valid input. 

*/

string spaceBetween(string, int);
string spaceLeft(string, int);


/*
1. Starting page

char startPage(string difficulty, string round, string level, int highScore, bool printContinue);

return 's' to start from beginning, 'c' to continue the game
the 'Press "c" ...' statement is printed only if [printContinue] is true

##########################################################################################
#                                                                                        #
#                                    Highscore: [score]                                  #
#                                                                                        #
#                                   ###################                                  #
#                                   #  Tower Of Doom  #                                  #
#                                   ###################                                  #
#                                                                                        #
#                           COMP2113 - Programming Technologies                          #
#                                                                                        #
#                                     Course Project                                     #
#                                                                                        #
#                                                                                        #
#                         (Press "s" to start from the beginning)                        #
#                                                                                        #
#                 (Press "c" to continue in [difficulty] - round [round])                #
#                                                                                        #
#                                                                                        #
##########################################################################################
*/

char startPage(string difficulty, string round, string level, int highScore, bool printContinue){
    cout << "##########################################################################################" << endl;
    string highScoreLine = "Highscore: " + to_string(highScore);
    cout << "#" << spaceBetween(highScoreLine,88) << "#" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                                   ###################                                  #" << endl;
    cout << "#                                   #  Tower Of Doom  #                                  #" << endl;
    cout << "#                                   ###################                                  #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                           COMP2113 - Programming Technologies                          #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                                     Course Project                                     #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                         (Press \"s\" to start from the beginning)                        #" << endl;
    cout << "#                                                                                        #" << endl;
    if(printContinue){
        cout << "#";

        string continueSentence = "(Press \"c\" to continue in " + difficulty + " - level " + level + " - round " + round + ")";
        cout << spaceBetween(continueSentence, 88);

        cout << "#" << endl;
    }else{
        cout << "#                                                                                        #" << endl;     
    }
    cout << "#                                                                                        #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "##########################################################################################" << endl;

    string inputValue;
    do {
        getline(cin, inputValue);
        if(inputValue.length() == 1){
            // Convert capital letter to small letter
            if(inputValue[0] >= 'A' && inputValue[0] <= 'Z'){
                inputValue[0] += ('a' - 'A');
            }
            if(inputValue[0] == 's' || (printContinue && inputValue[0] == 'c')){
                return inputValue[0];
            }
        }
    }while(true);
}


/*
2. Choosing difficulty

char chooseDifficulty(); 

return 'e' for easy, 'm' for medium, 'h' for hard

##########################################################################################
#                                                                                        #
#                                                                                        #
#     Please choose your difficulty:                                                     #
#                                                                                        #
#                                                                                        #
#          ################          ################          ################          #
#          #              #          #              #          #              #          #
#          #              #          #              #          #              #          #
#          #    (Easy)    #          #   (Medium)   #          #    (Hard)    #          #
#          #              #          #              #          #              #          #
#          #              #          #              #          #              #          #
#          ################          ################          ################          #
#                                                                                        #
#            (Press "e")                (Press "m")              (Press "h")             #
#                                                                                        #
#                                                                                        #
#                                                                                        #
##########################################################################################

*/

char chooseDifficulty(){
    cout << "##########################################################################################" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#     Please choose your difficulty:                                                     #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#          ################          ################          ################          #" << endl;
    cout << "#          #              #          #              #          #              #          #" << endl;
    cout << "#          #              #          #              #          #              #          #" << endl;
    cout << "#          #    (Easy)    #          #   (Medium)   #          #    (Hard)    #          #" << endl;
    cout << "#          #              #          #              #          #              #          #" << endl;
    cout << "#          #              #          #              #          #              #          #" << endl;
    cout << "#          ################          ################          ################          #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#            (Press \"e\")                (Press \"m\")              (Press \"h\")             #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "##########################################################################################" << endl;
    
    string inputValue;
    do {
        getline(cin, inputValue);
        if(inputValue.length() == 1){
            // Convert capital letter to small letter
            if(inputValue[0] >= 'A' && inputValue[0] <= 'Z'){
                inputValue[0] += ('a' - 'A');
            }
            if(inputValue[0] == 'e' || inputValue[0] == 'm' || inputValue[0] == 'h'){
                return inputValue[0];
            }
        }
    }while(true);
}


/*
3. Choosing card

char chooseCard(string cardOne, string cardTwo, string cardThree);

return '1' for first card picked, '2' for second card picked, '3' for third card picked

##########################################################################################
#                                                                                        #
#                                                                                        #
#     Please choose your card:                                                           #
#                                                                                        #
#                                                                                        #
#         ##################        ##################        ##################         #
#         #                #        #                #        #                #         #
#         #   [cardOne]    #        #   [cardTwo]    #        #  [cardThree]   #         #
#         #                #        #                #        #                #         #
#         #                #        #                #        #                #         #
#         #                #        #                #        #                #         #
#         ##################        ##################        ##################         #
#                                                                                        #
#            (Press "1")               (Press "2")                (Press "3")            #
#                                                                                        #
#                                                                                        #
#                                                                                        #
##########################################################################################

*/

char chooseCard(string cardOne, string cardTwo, string cardThree){
    cout << "##########################################################################################" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#     Please choose your card:                                                           #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#         ##################        ##################        ##################         #" << endl;
    cout << "#         #                #        #                #        #                #         #" << endl;

    string cardOneString[40];
    string cardTwoString[40];
    string cardThreeString[40];

    istringstream streamOne(cardOne);
    istringstream streamTwo(cardTwo);
    istringstream streamThree(cardThree);

    for(int i = 0; i < 4; i++){
        streamOne >> cardOneString[i];
        streamTwo >> cardTwoString[i];
        streamThree >> cardThreeString[i];
    }


    cout << "#         #" << spaceBetween(cardOneString[0], 16) << "#        #" << spaceBetween(cardTwoString[0], 16) << "#        #" << spaceBetween(cardThreeString[0], 16) << "#         #" << endl;
    cout << "#         #" << spaceBetween(cardOneString[1], 16) << "#        #" << spaceBetween(cardTwoString[1], 16) << "#        #" << spaceBetween(cardThreeString[1], 16) << "#         #" << endl;
    cout << "#         #" << spaceBetween(cardOneString[2], 16) << "#        #" << spaceBetween(cardTwoString[2], 16) << "#        #" << spaceBetween(cardThreeString[2], 16) << "#         #" << endl;
    cout << "#         #" << spaceBetween(cardOneString[3], 16) << "#        #" << spaceBetween(cardTwoString[3], 16) << "#        #" << spaceBetween(cardThreeString[3], 16) << "#         #" << endl;

    cout << "#         ##################        ##################        ##################         #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#            (Press \"1\")               (Press \"2\")                (Press \"3\")            #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "##########################################################################################" << endl;
    
    string inputValue;
    do {
        getline(cin, inputValue);
        if(inputValue.length() == 1 && (inputValue[0] == '1' || inputValue[0] == '2' || inputValue[0] == '3')){
            return inputValue[0];
        }
    }while(true);
}


/*
4. Choosing stat

char chooseStat(int firstStat, int secondStat, int thirdStat, string cardName);

return '1' for first stat picked, '2' for second stat picked, '3' for third stat picked

##########################################################################################
#                                                                                        #
#                                                                                        #
#     Please choose your stat:                                                           #
#                                                                                        #
#      ################################                                                  #
#      #                              #                                                  #
#      #                              #    Strength: [firstStat]      (Press "1")        #
#      #                              #                                                  #
#      #                              #                                                  #
#      #         [cardName]           #    Charisma: [secondStat]     (Press "2")        #
#      #                              #                                                  #
#      #                              #                                                  #
#      #                              #    Wisdom:   [thirdStat]      (Press "3")        #
#      #                              #                                                  #
#      ################################                                                  #
#                                                                                        #
#                                                                                        #
##########################################################################################

*/

char chooseStat(int firstStat, int secondStat, int thirdStat, string cardName){
    cout << "##########################################################################################" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#     Please choose your stat:                                                           #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#      ################################                                                  #" << endl;
    cout << "#      #                              #                                                  #" << endl;

    cout << "#      #                              #    Strength: " << firstStat << "     ";
    if(firstStat <= 9){
        cout << " ";
    }
    cout << "(Press \"1\")                  #" << endl;


    cout << "#      #                              #                                                  #" << endl;
    cout << "#      #                              #                                                  #" << endl;

    cout << "#      #" << spaceBetween(cardName, 30) << "#    Charisma: " << secondStat << "     ";
    if(secondStat <= 9){
        cout << " ";
    }
    cout << "(Press \"2\")                  #" << endl;


    cout << "#      #                              #                                                  #" << endl;
    cout << "#      #                              #                                                  #" << endl;
    cout << "#      #                              #    Wisdom:   " << thirdStat << "     ";
    if(thirdStat <= 9){
        cout << " ";
    }
    cout << "(Press \"3\")                  #" << endl;


    cout << "#      #                              #                                                  #" << endl;
    cout << "#      ################################                                                  #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "##########################################################################################" << endl;
    
    string inputValue;
    do {
        getline(cin, inputValue);
        if(inputValue.length() == 1 && (inputValue[0] == '1' || inputValue[0] == '2' || inputValue[0] == '3')){
            return inputValue[0];
        }
    }while(true);
}


/*
5. Contest

void contest(int firstStatPlayer, int secondStatPlayer, int thirdStatPlayer, int firstStatEnemy, int secondStatEnemy, int thirdStatEnemy, int health, int damage, bool win, int level, int round, string enemyName);

##########################################################################################
#                                                                                        #
#     Contest(level[level]-round[round]):                                                #
#                                                                                        #
#       You                                  Enemy                 ##################    #
#                                                                  #                #    #
#     Strength: [firstStatPlayer]         [firstStatEnemy]         #                #    #
#                                                                  #   [enemyName]  #    #
#     Charisma: [secondStatPlayer]        [secondStatEnemy]        #                #    #
#                                                                  #                #    #
#     Wisdom:   [thirdStatPlayer]         [thirdStatEnemy]         ##################    #
#                                                                                        #
#                                                                                        #
#     You [win/lose]! Deal [damage] Damage               (o)     (o)      (o)    (o)     #
#     (Press "n" to go to the next round)                                                #
#                                                        *         *        *  *  *      #
#     Health: [health]                                     *  *  *        *         *    #
#                                                                                        #
##########################################################################################

*/

void contest(int firstStatPlayer, int secondStatPlayer, int thirdStatPlayer, int firstStatEnemy, int secondStatEnemy, int thirdStatEnemy, int health, int damage, bool win, int level, int round, string enemyName){

    string enemyNameString[40];

    istringstream stream(enemyName);

    for(int i = 0; i < 4; i++){
        stream >> enemyNameString[i];
    }

    cout << "##########################################################################################" << endl;
    cout << "#                                                                                        #" << endl;
    string topicSentence =  "Contest(level " + to_string(level) + " - round " + to_string(round) + "):";
    cout << "#     " << spaceLeft(topicSentence, 83) << "#" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#       You                              Enemy                     ##################    #" << endl;
    cout << "#                                                                  #                #    #" << endl;
    cout << "#     Strength: " << spaceLeft(to_string(firstStatPlayer), 26) << spaceLeft(to_string(firstStatEnemy), 25) << "#" << spaceBetween(enemyNameString[0], 16) << "#    #" << endl;
    cout << "#                                                                  #" << spaceBetween(enemyNameString[1], 16) << "#    #" << endl;
    cout << "#     Charisma: " << spaceLeft(to_string(secondStatPlayer), 26) << spaceLeft(to_string(secondStatEnemy), 25) << "#" << spaceBetween(enemyNameString[2], 16) << "#    #" << endl;
    cout << "#                                                                  #                #    #" << endl;
    cout << "#     Wisdom:   " << spaceLeft(to_string(thirdStatPlayer), 26) << spaceLeft(to_string(thirdStatEnemy), 25) << "##################    #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                                                                                        #" << endl;

    if(win){
        string damageSentence = "You win! " + enemyName + " retreats.";
        cout << "#     " << spaceLeft(damageSentence, 50) << "(o)     (o)                      #" << endl;
        cout << "#                                                                                        #" << endl;
        cout << "#     (Press \"n\" to go to the next round)               *         *                      #" << endl;
        string healthSentence = "Health: " + to_string(health) + "/100";
        cout << "#     " << spaceLeft(healthSentence, 50) << "  *  *  * " << "                       #" << endl;
    }else{
        string damageSentence = "You lose! Deal " + to_string(damage) + " Damage";
        cout << "#     " << spaceLeft(damageSentence, 50) << "(o)     (o)                      #" << endl;
        cout << "#                                                                                        #" << endl;
        cout << "#     (Press \"n\" to go to the next round)                 *  *  *                        #" << endl;
        string healthSentence = "Health: " + to_string(health) + "/100";
        cout << "#     " << spaceLeft(healthSentence, 50) << "*         *" << "                      #" << endl;
    }
    
    cout << "#                                                                                        #" << endl;
    cout << "##########################################################################################" << endl;

    string inputValue;
    do {
        getline(cin, inputValue);
        if(inputValue.length() == 1 && (inputValue[0] == 'n' || inputValue[0] == 'N')){
            return;
        }
    }while(true);
    
}


/*
6. When the health bar reaches 0

void lose();

##########################################################################################
#                                                                                        #
#                                                                                        #
#                                                                                        #
#                               ##########################                               #
#                               #    You Lost  !!!!!!!   #                               #
#                               ##########################                               #
#                                                                                        #
#                                                                                        #
#                                      Health: 0/100                                     #
#                                                                                        #
#                                                                                        #
#                                                                                        #
#                         (Press "m" to return to the main page)                         #
#                                                                                        #
#                                                                                        #
#                                                                                        #
#                                                                                        #
##########################################################################################

*/

void lose(){
    cout << "##########################################################################################" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                               ##########################                               #" << endl;
    cout << "#                               #    You Lost  !!!!!!!   #                               #" << endl;
    cout << "#                               ##########################                               #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                                      Health: 0/100                                     #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                         (Press \"m\" to return to the main page)                         #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "##########################################################################################" << endl;
    
    string inputValue;
    do {
        getline(cin, inputValue);
        if(inputValue.length() == 1 && (inputValue[0] == 'm' || inputValue[0] == 'M')){
            return;
        }
    }while(true);
}


/*
7. After completing a level

char completeLevel();

return 'n' to go to next level, 's' to save, or 'm' to return to main menu

##########################################################################################
#                                                                                        #
#                                                                                        #
#                                                                                        #
#                            ###############################                             #
#                            #    Level Completed  !!!!!!  #                             #
#                            ###############################                             #
#                                                                                        #
#                                                                                        #
#                                                                                        #
#                                                                                        #
#                          (Press "n" to go to the next level)                           #
#                                                                                        #
#                                  (Press "s" to save)                                   #
#                                                                                        #
#                           (Press "m" to return to main menu)                           #
#                                                                                        #
#                                                                                        #
##########################################################################################

*/

char completeLevel(){
    cout << "##########################################################################################" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                            ###############################                             #" << endl;
    cout << "#                            #    Level Completed  !!!!!!  #                             #" << endl;
    cout << "#                            ###############################                             #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                          (Press \"n\" to go to the next level)                           #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                                  (Press \"s\" to save)                                   #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                           (Press \"m\" to return to main menu)                           #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "##########################################################################################" << endl;

    string inputValue;
    do {
        getline(cin, inputValue);
        if(inputValue.length() == 1){
            // Convert capital letter to small letter
            if(inputValue[0] >= 'A' && inputValue[0] <= 'Z'){
                inputValue[0] += ('a' - 'A');
            }
            if(inputValue[0] == 'n' || inputValue[0] == 's' || inputValue[0] == 'm'){
                return inputValue[0];
            }
        }
    }while(true);
}


/*
8. After completing all levels

void completeAllLevel();

##########################################################################################
#                                                                                        #
#                                                                                        #
#                                                                                        #
#                            ###############################                             #
#                            #     Game Completed  !!!!!!  #                             #
#                            ###############################                             #
#                                                                                        #
#                                                                                        #
#                                                                                        #
#                                                                                        #
#                         (Press "m" to return to the main page)                         #
#                                                                                        #
#                            (Press "c" to check your cards)                             #
#                                                                                        #
#                           (Press "e" to check enemy cards)                             #
#                                                                                        #
#                                                                                        #
##########################################################################################

*/

char completeAllLevel(){
    cout << "##########################################################################################" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                            ###############################                             #" << endl;
    cout << "#                            #     Game Completed  !!!!!!  #                             #" << endl;
    cout << "#                            ###############################                             #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                         (Press \"m\" to return to the main page)                         #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                            (Press \"c\" to check your cards)                             #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                           (Press \"e\" to check enemy cards)                             #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "#                                                                                        #" << endl;
    cout << "##########################################################################################" << endl;

    string inputValue;
    do {
        getline(cin, inputValue);
        if(inputValue.length() == 1 && (inputValue[0] == 'm' || inputValue[0] == 'M'||inputValue[0] == 'c'||inputValue[0] == 'C'||inputValue[0] == 'e'||inputValue[0] == 'E')){
            return inputValue[0];
        }
    }while(true);
}

// Local functions

// Center the print statement
string spaceBetween(string word, int totalSpace){
    string outputString = "";

    totalSpace -= word.length();
    int startSpace, endSpace;

    if(totalSpace%2 == 1){
        startSpace = (totalSpace-1)/2+1;
        endSpace = (totalSpace-1)/2;
    }else{
        startSpace = totalSpace/2;
        endSpace = totalSpace/2;
    }

    for(int i = 0; i < startSpace; i++){
        outputString += " ";
    }
    outputString += word;
    for(int i = 0; i < endSpace; i++){
        outputString += " ";
    }
    return outputString;
}

// Move the print statement on the left side
string spaceLeft(string word, int totalSpace){
    totalSpace -= word.length();
    
    string outputString = word;

    for(int i = 0; i < totalSpace; i++){
        outputString += " ";
    }
    return outputString; 
}