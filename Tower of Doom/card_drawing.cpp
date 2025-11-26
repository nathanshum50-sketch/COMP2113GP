#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include "header.h"
using namespace std;

//I intend to augment the probability of cards in different difficulties.

//Poisson distribution here. I am not introducing a whole new package just for a minor calculation.
double qual_prob(int x,int difficulty){
	int i,j=1;
	float lambda;
	for (i=1;i<=x;i++) j*=i;
	//idk, may tweak lambda later
	switch (difficulty){
		case 1:
			lambda=1.5;
			break;
		case 2:
			lambda=1;
			break;
		case 3:

			lambda=0.5;
			break;
		default:
			cout<<"Critical error on lambda encountered. For further question, please consult Oliver."<<endl;
			return 0;
	}
	double result=pow(lambda,x)*exp(-lambda)/j;
	return (x==0)?result:result+qual_prob(x-1,difficulty);
}

//Remember to set a seed. `time(NULL+j)` can be a good one. Please check main.cpp for reference.
//Please be noted that seeds must be different every time. If the seed is the same, you will get the same card.

Card drawncard(int difficulty,Card* fulldeck,int seed){
	srand(seed);
	int qual,no,dice;
	Card* pos=fulldeck;
	dice=rand()%10000;
	for (qual=0;qual<6;qual++) if (dice<qual_prob(qual,difficulty)*10000) break;
	switch (qual){
		case 0:
			no=rand()%20+1;
			break;
		case 1:
			no=rand()%20+21;
			break;
		case 2:
			no=rand()%20+41;
			break;
		case 3:
			no=rand()%20+61;
			break;
		case 4:
			no=rand()%20+81;
			break;
		case 5:
			no=0;
			break;
		default:
			cout<<qual<<"\nCritical error encountered on card gen. Please consult the person responsible for this part."<<endl;
	}
	//I will adjust the variable `no` according to future works of Wyman. Feel free to add whatever amount of cards in each class, Wyman.
	while (pos!=NULL){
		if (pos->card_number==no) break;
		pos=pos->next;
	}
	if (pos->card_number!=no){
		cout<<"Card no. "<<no<<" not found"<<endl;
		return *(fulldeck->next);
	}
	return *pos;
}

//I assume putting card into players/enemies hands is part of my job.
void addcard(Card* &handcardhead,Card newcard){
	Card* drawncard=new Card;
	*drawncard=newcard;
	if (handcardhead==NULL){
		drawncard->next=NULL;
		handcardhead=drawncard;
		return;
	}else if (handcardhead->card_number>drawncard->card_number){
		drawncard->next=handcardhead;
		handcardhead=drawncard;
		return;
	}
	Card* pos=handcardhead;
	while (pos->next!=NULL){
		if (pos->next->card_number>drawncard->card_number) break;
		pos=pos->next;
	}
	drawncard->next=pos->next;
	pos->next=drawncard;
	return;
}

void deleteList(Card* head) {
    while (head) {
        Card* tmp = head;
        head = head->next;
        delete tmp;
    }
}