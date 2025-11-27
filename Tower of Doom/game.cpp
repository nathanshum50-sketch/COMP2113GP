#include "game.h"
#include <ctime>
#include <iostream>
//the game class
Game::Game() {
}

//clear and initalize variables for the game
void Game::init_game() {
    this->state = GameState();
    this->enemy.clear();
    deleteList(this->player_cards);
    this->player_cards = nullptr;
    deleteList(this->enemy_cards);
    this->enemy_cards = nullptr;
    deleteList(this->all_cards);
    this->all_cards = nullptr;
    this->state.loadPlayer("player.txt");
    this->all_cards = Load_cards();
    main_menu();
}

//give the interface, select difficulty
void Game::main_menu() {
	//take score
    int score = loadHighScore("highscore.txt");
    string round, level, difficulty;
	//take round and level
    round = to_string(this->state.round);
    level = to_string(this->state.level);
	//convert to readable format
    if(this->state.difficulty == 'E' || this->state.difficulty == 'e') {
        difficulty = "Easy";
    } else if(this->state.difficulty == 'H' || this->state.difficulty == 'h') {
        difficulty = "Hard";
    } else {
        difficulty = "Medium";
    }
    bool printContinue;
	//print continue if not medium round 1
    (this->state.score > 1 || (this->state.difficulty != 'M' && this->state.difficulty != 'm')) ? printContinue = true : printContinue = false;
    char output = startPage(difficulty, round, level, score, printContinue);
    if(output == 's') {
        this->state = GameState();
        select_diff();
    }
    init_level();
}

//function to select difficulty
void Game::select_diff() {
    this->state.difficulty = chooseDifficulty();
}

//initialize level
void Game::init_level() {
    while(state.round < 11 && state.hp > 0) {
		//initalize round below round component in state variable being 11 or losing
        init_round(true);
    }
    if(state.hp <= 0) {
		//losing lost the game
        lost();
        return;
    } else if(state.level == 3) {
		//update score and win
        this->state.score += state.levelBonus();
        won();
        return;
    }
	
	//update score, level and round at end of level
    this->state.score += state.levelBonus();
    this->state.level += 1;
    this->state.round = 1;

	//complete level interface
	char result = completeLevel();
	
	//choose between initializing next level, returning to main menu, or saving player
    while(true) {
        if(result == 'n') {
            init_level();
            return;
        } else if(result == 'm') {
            main_menu();
            return;
        } else {
            state.savePlayer("player.txt");
            result = completeLevel();
        }
    }
}

//initalize round combat
void Game::init_round(bool newEnemy) {
	//if there is a boss
    bool isBossRound = (this->state.round == 10);
	//if enemy changes
    if(newEnemy) this->enemy = generateRandomEnemy(this->state.level, isBossRound);
	//generate and add enemy and player cards to sections
    Card enemyCard = generateEnemyCard(this->enemy, this->all_cards, this->state.difficulty);
    addcard(this->enemy_cards, enemyCard);
    Card drawn[3];
    int diffInt;
    if (this->state.difficulty == 'E' || this->state.difficulty == 'e') diffInt = 1;
    else if (this->state.difficulty == 'H' || this->state.difficulty == 'h') diffInt = 3;
    else diffInt = 2;
    for (int i=0;i<3;i++){
		//draw the cards for the player
		drawn[i] = drawncard(diffInt,this->all_cards,time(NULL)+i);
	}
	//choose the player card and add it to list
	int j = chooseCard(drawn[0].card_name, drawn[1].card_name,drawn[2].card_name) - '0';
	addcard(this->player_cards,drawn[j-1]);
	Card playerCard = drawn[j-1];
	
	//player choose stat
	char stat = chooseStat(playerCard.card_STR, playerCard.card_CHA, playerCard.card_WIS, playerCard.card_name);
	string compete;
	if(stat == '1') {
	    compete = "STR";
	} else if(stat == '2') {
	    compete = "CHA";
	} else {
	    compete = "WIS";
	}
	// Update score ("VICTORY", "DEFEAT", "DRAW")
    string outcome = battlePlayer(playerCard, enemyCard, compete);
    int damageIfDefeat = computeDamage(playerCard, enemyCard, compete, this->state.difficulty);
	
    //show outcome
    state.applyBattleResult(outcome, damageIfDefeat);
    if(outcome == "DRAW") {
		//draw gives flavor and same enemy
        cout << this->enemy << " clutches their weapon tighter." << endl;
        init_round(false);
        return;
    } else if(outcome == "VICTORY") {
        this->state.round += 1;
    }
    contest(playerCard.card_STR, playerCard.card_CHA, playerCard.card_WIS, enemyCard.card_STR, enemyCard.card_CHA, enemyCard.card_WIS, this->state.hp, damageIfDefeat, (outcome == "VICTORY"), this->state.level, this->state.round, this->enemy);
    if(outcome == "DEFEAT") {
        if(this->state.hp <= 0) {
            return;
        }
		//loss gives flavor and same enemy
        cout << this->enemy << " gives a broad grin." << endl;
        init_round(false);
    }
}

//lose the game
void Game::lost() {
	//update high score
    state.updateHighScore("highscore.txt");
    lose();
    init_game();
}

//win the game
void Game::won() {
	//update high score
    state.updateHighScore("highscore.txt");
	//give screen and init game and print card commands
    char instruction = completeAllLevel();
    while(true) {
        if(instruction == 'm' || instruction == 'M') {
            init_game();
            return;
        } else if(instruction == 'c' || instruction == 'C') {
            print(this->player_cards);
        } else if(instruction == 'e' || instruction == 'E') {
            print(this->enemy_cards);
        }
        instruction = completeAllLevel();
    }
}

//main game loop (thin for additions)
void Game::main_game() {
    init_game();
}
