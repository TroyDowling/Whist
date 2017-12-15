#include "Gamestate.h"
using namespace std;

Gamestate::Gamestate()
{
  for(int i = 0; i < 52; ++i){
    allWhoPlayed[i] = -1;
    allCardsPlayed[i] = 0;
  }
  for(int i = 0; i < 4; ++i){
    who_played[i] = -1;
    cards_played[i] = 0;
  }
  score[0] = score[1] = 0;
  turn = 0;
  for(int i = 0; i < 52; ++i){
    cards[i] = 0;
  }
  for(int i = 0; i < 4; ++i){
    hands[i] = new Hand;
  }
}
/*
Number identifier of save game
Scores
turn
Hands (suit and value of cards separated by newlines)
*/

void Gamestate::save_game(int num_save_game)
{
	Card * cardInHand;
	ofstream savefile ("saves.txt", std::fstream::app);
	if (savefile.is_open())
	{
		//allocate an address (greater than 15)
		savefile << num_save_game << endl;
		//save scores
		savefile << score[0] <<" "<< score[1] << endl;
		//save whose turn
		savefile << turn << endl;
		int numCardsInHand;
		
		//save hands 
		//--- 
		//number of cards in hand
		//suit value
		//---
		for(int currenthand = 0; currenthand < 4; ++currenthand)
		{ 
			numCardsInHand = hands[currenthand]->getLen();
			savefile << numCardsInHand << endl;
			for(int currentcard = 0; currentcard < numCardsInHand; ++currentcard)
			{
				cardInHand = hands[currenthand]->getCard(currentcard);
				savefile << cardInHand->get_suit() <<" ";
				savefile << cardInHand->get_val() << endl;
			}
			savefile << endl;
		}
		savefile.close();		
	}
	else
	{
		cout << "Invalid save location." << endl;
		return;
	}
}

void Gamestate::load_game(int num_load_game)
{
  //opens a file
        bool loading = true;
	ifstream loadfile;
	int save_id, numCardsInHand, card_val, card_suit;
	char whosTurn;
	Card * newCard;
	loadfile.open("saves.txt");
	if(!loadfile)
	{
		cout << "Invalid load location." << endl;
		return;
	}
	//No idea if this will work on the first try.
	while(loading)
	{
		loadfile >> save_id;
		if(save_id == num_load_game)
		{
			//load scores
			loadfile >> score[0]; loadfile >> score[1];
			//load turn
			loadfile >> whosTurn;
			//load hands
			for(int currenthand = 0; currenthand < 4; currenthand++)
			{
				loadfile >> numCardsInHand;
				for(int currentcard = 0; currentcard < numCardsInHand; currentcard++)
				{
					loadfile >> card_suit;
					loadfile >> card_val;
					newCard = new Card(card_val, card_suit);
					hands[currenthand]->addCard(newCard);
					
				}
			}
			loadfile.close();
			loading = false;
		}
		else loadfile >> save_id;
	}
}

void Gamestate::deal()
{
        deck.shuffle();
	for(int i = 0; i < 52; ++i){
	  cards[i] = deck.getCard(i);
	}
	for(int i = 0; i < 13; ++i)
	{
		hands[0]->addCard(cards[i]);
	}
	for(int i = 13; i < 26; ++i)
	{
		hands[1]->addCard(cards[i]);
	}
	for(int i = 26; i < 39; ++i)
	{
	  hands[2]->addCard(cards[i]);
	}
	for(int i = 39; i < 52; ++i)
	{
	  hands[3]->addCard(cards[i]);
	}
}

void Gamestate::chkWinner(){
  int ledSuit = cards_played[0]->get_suit();
  int highVal = 0;
  int highPlayer = 0;
  for(int i = 0; i < 4; i++){
    if(cards_played[i]->get_suit() == ledSuit){
      if(cards_played[i]->get_val() >= highVal){
	highVal = cards_played[i]->get_val();
	highPlayer = i;
      }
    }
  }
  if(highPlayer == 0 || highPlayer == 2){
    score[0]++;
    cout << "Team PLAYER takes the trick! Their score: " << score[0] << endl;
    if(tricksPlayed < 13) tricksPlayed++;
    else tricksPlayed = 0;
  }
  else{
    score[1]++;
    cout << "Team AI takes the trick! Their score: " << score[1] << endl;
    if(tricksPlayed < 13) tricksPlayed++;
    else tricksPlayed = 0;
  }
  for(int i = 0; i < 4; ++i){
    //cout << who_played[i]<<" ";
    who_played[i] = -1;
    cards_played[i] = 0;
  }
  turn = highPlayer;
  cout << "turn: " << turn << endl;
}

void Gamestate::emptyHands(){
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 13; j++){
      hands[i]->hand[j] = 0;
    }
    hands[i]->setLen(13);
  }
}

void Gamestate::chkWinnerH(){
  if(overall_score[0] < playTo && overall_score[1] < playTo){
    if(score[0] < score[1]){
      overall_score[1]++;
      cout << "Team AI wins the hand! Congratulations!" << endl;
      cout << "Their overall score is now: " << overall_score[1] << endl;
      newRound();
    }
    else{
      overall_score[0]++;
      cout << "Team PLAYER wins the hand! Congratulations!" << endl;
      cout << "Their overall score is now: " << overall_score[0] << endl;
      newRound();
    }
  }
  else{
    if(overall_score[0] == 5){
      cout << "Team PLAYER wins the game! GG!" << endl;
    }
    else if(overall_score[1] == 5){
      cout << "Team AI wins the game! GG!" << endl;
    }
    cout << "Final score: " << endl;
    cout << "Team PLAYER: " << overall_score[0] << endl;
    cout << "Team AI: " << overall_score[1] << endl;
  }    
}
 
void Gamestate::nextTurn(){
  if(turn != 3){
    turn++;
    if(numTurns != 3) numTurns++;
    else numTurns = 0;
  }
  else{
    turn = 0;
    if(numTurns != 3) numTurns++;
    else numTurns = 0;
  }
}

void Gamestate::newRound(){
  for(int i = 0; i < 4; ++i){
    cards_played[i] = 0;
    who_played[i] = -1;
  }
  emptyHands();
  deck.shuffle();
  cout << "deck shuffled" << endl;
  deal();
  cout << "deck dealt" << endl;
}
