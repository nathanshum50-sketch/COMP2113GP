#ifndef HEADER_H
#define HEADER_H
#include <string>
using namespace std;

//structure a data type: Card
//storing a card no, rarity, str, cha, wis
struct Card{
    int card_number;
    int card_rarity;
    int card_STR;
    int card_CHA;
    int card_WIS;
    string card_name;

    Card* next;
};

void add_card(Card * & head, Card * & tail, int card_number,int card_rarity, int card_STR, int card_CHA, int card_WIS, string card_name);

Card* Load_cards();

void printCard(Card card);

double qual_prob(int x,int difficulty);

Card drawncard(int difficulty,Card* fulldeck,int seed);

void addcard(Card* &handcardhead,Card newcard);

void print(Card* head);

void deleteList(Card* head);

#endif
