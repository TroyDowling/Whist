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
  Card *tempCard;
  int index = 0;
  Card* unsortedCards[13];
  Card *clubs[13], *hearts[13], *spades[13], *diamonds[13];
  deck.shuffle();
  for(int i = 0; i < 52; ++i){
    cards[i] = deck.getCard(i);
  }
  for(int i = 0; i < 13; ++i)
    {
      hands[0]->addCard(cards[i]);
      /*unsortedCards[i] = cards[i];
	clubs[i] = 0; hearts[i] = 0; spades[i] = 0; diamonds[i] = 0;*/
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

  /*/sort user hand
  //find clubs
  index = 0;
  for(int i = 0; i < 13; ++i){
    if(unsortedCards[i]->get_suit() == 1){
      clubs[index] = unsortedCards[i];
      cout << "c:" << clubs[index]->get_val();
      ++index;
    }
  }
  index = 0;
  //find hearts
  for(int i = 0; i < 13; ++i){
    if(unsortedCards[i]->get_suit() == 2){
      hearts[index] = unsortedCards[i];
      cout << "h:" << hearts[index]->get_val();
      ++index;
    }
  }
  index = 0;
  //find spades
  for(int i = 0; i < 13; ++i){
    if(unsortedCards[i]->get_suit() == 3){
      spades[index] = unsortedCards[i];
      cout << "s:" << spades[index]->get_val();
      ++index;
    }
  }
  index = 0;
  //find diamonds
  for(int i = 0; i < 13; ++i){
    if(unsortedCards[i]->get_suit() == 4){
      diamonds[index] = unsortedCards[i];
      cout << "d:" << diamonds[index]->get_val();
      ++index;
    }
  }
  index = 0;
  cout << " found all cards" << endl;
  //sort clubs
  for(int i = 0; i <= 13; ++i){
    for(int j = 0; j <= 13; ++j){
      if(clubs[j] != 0){
	if(clubs[j] > clubs[j+1]){
	  tempCard = clubs[j];
	  clubs[j] = clubs[j+1];
	  clubs[j+1] = tempCard;
	}
      }
    }
  }
  cout << "sorted clubs" << endl;
  //sort hearts
  for(int i = 0; i <= 13; ++i){
    for(int j = 0; j <= 13; ++j){
      if(hearts[j] != 0 && hearts[j] > hearts[j+1]){
	tempCard = hearts[j];
        hearts[j] = hearts[j+1];
        hearts[j+1] = tempCard;
      }
    }
  }
  cout << "sorted hearts" << endl;
  //sort spades
  for(int i = 0; i <= 13; ++i){
    for(int j = 0; j <= 13; ++j){
      if(spades[j] != 0 && spades[j] > spades[j+1]){
	tempCard = spades[j];
        spades[j] = spades[j+1];
        spades[j+1] = tempCard;
      }
    }
  }
  cout << "sorted spades" << endl;
  //sort diamonds
  for(int i = 0; i <= 13; ++i){
    for(int j = 0; j <= 13; ++j){
      if(diamonds[j] != 0 && diamonds[j] > diamonds[j+1]){
	tempCard = diamonds[j];
        diamonds[j] = diamonds[j+1];
        diamonds[j+1] = tempCard;
      }
    }
  }
  cout << "sorted diamonds" << endl;
  //add all cards to user hand
  for(int i = 0; i <= 13; ++i){
    if(clubs[i] != 0) {hands[0]->addCard(clubs[i]); cout << "AC";}
  }
  cout << "added clubs" << endl;
  for(int i = 0; i <= 13; ++i){
    if(hearts[i] != 0) {hands[0]->addCard(hearts[i]); cout << "AH";}
  }
  cout << "added hearts" << endl;
  for(int i = 0; i <= 13; ++i){
    if(spades[i] != 0) {hands[0]->addCard(spades[i]); cout << "AS";}
  }
  cout << "added spades" << endl;
  for(int i = 0; i <= 13; ++i){
    if(diamonds[i] != 0) {hands[0]->addCard(diamonds[i]); cout << "AD";}
  }
  cout << "added diamonds" << endl;*/
  
}

void Gamestate::chkWinner(){
  int ledSuit = cards_played[0]->get_suit();
  //cout << ledSuit << ": led suit" << endl;
  int highVal = 0;
  int highPlayer = 0;
  cout << "players: " << endl;
  for(int i = 0; i < 4; ++i) cout << who_played[i] <<" ";
  cout << endl << "suit:val " << endl;
  for(int i = 0; i < 4; ++i) cout << cards_played[i]->get_suit() <<":" << cards_played[i]->get_val() << " ";
  cout << endl;
  for(int i = 0; i < 4; i++){
    if(cards_played[i]->get_suit() == ledSuit){
      if(cards_played[i]->get_val() > highVal){
	highVal = cards_played[i]->get_val();
	//cout << highVal <<": winning number" << endl;
	highPlayer = who_played[i];
	//cout << highPlayer <<": high player here" << endl;
      }
    }
  }
  if(highPlayer == 0 || highPlayer == 2){
    score[0]++;
    cout << "Team PLAYER takes the trick! Their score: " << score[0] << endl;
    if(tricksPlayed < 13) tricksPlayed++;
    else tricksPlayed = 1;
  }
  else{
    score[1]++;
    cout << "Team AI takes the trick! Their score: " << score[1] << endl;
    if(tricksPlayed < 13) tricksPlayed++;
    else tricksPlayed = 1;
  }
  for(int i = 0; i < 4; ++i){
    //cout << who_played[i]<<" ";
    who_played[i] = -1;
    cards_played[i] = 0;
  }
  turn = highPlayer;
  //cout << "turn: " << turn << endl;
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
  //deck.shuffle();
  //cout << "deck shuffled" << endl;
  deal();
  //cout << "deck dealt" << endl;
}

bool Gamestate::isLegal(Card * c, int s, int h){
  bool hasSuit = false;
  for(int i = 0; i < get_handLen(h); ++i){
    if(get_card(h, i)->get_suit() == s) hasSuit = true;
  }
  if(c->get_suit() == s) return true;
  else if(hasSuit == false)
    return true;
  else return false;
}
