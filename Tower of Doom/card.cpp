#include <iostream>
#include <fstream>
#include "header.h"
using namespace std;

//use in Card* Load_cards()
//adding card to link list
void add_card(Card * & head, Card * & tail, int card_number,int card_rarity, int card_STR, int card_CHA, int card_WIS, string card_name){
    Card * c = new Card;
    c->card_number = card_number;
    c->card_rarity = card_rarity;
    c->card_STR = card_STR;
    c->card_CHA = card_CHA;
    c->card_WIS = card_WIS;
    c->card_name = card_name;
    c->next = NULL;

    if (head == NULL){
        head = c;
        tail = c;
    }
    else{
        tail->next = c;
        tail = c;
    }
}

//loading card info from "cards.txt"
//create a link list to store all cards
//return head of link list
//Oliver: I debugged the function below so that I can test my card drawing algorithm.
Card* Load_cards(){
    Card * head = NULL, * tail = NULL;
    ifstream cards;
    cards.open("cards.txt");
    string line;
    while (getline(cards,line)){  
        int number = stoi(line.substr(0,3));
        int rarity = stoi(line.substr(4,1));
        int STR = stoi(line.substr(6,2));
        int CHA = stoi(line.substr(9,2));
        int WIS = stoi(line.substr(12,2));
        string name = line.substr(15);
        add_card(head, tail, number, rarity, STR, CHA, WIS, name);
    }

    return head;
}

//Oliver: The framework below was made by Wyman
void printCard(Card card) {
    cout << "\n=== YOUR CARD ===\n";
    cout << "ID     : " << card.card_number << endl;
    cout << "Name   : " << card.card_name << endl;
    cout << "Rarity : " << card.card_rarity << " ";
    string stars = string(card.card_rarity + 1, '*');
    cout << stars << endl;
    cout << "STR    : " << card.card_STR << endl;
    cout << "CHA    : " << card.card_CHA << endl;
    cout << "WIS    : " << card.card_WIS << endl;
    cout << "=================\n\n";
}

void print(Card* head){
	Card*pos=head;
	int i=1;
	while (pos!=NULL){
		printCard(*pos);
		i++;
		pos=pos->next;
	}
}