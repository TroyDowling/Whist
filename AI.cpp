#include "AI.h"

AI::AI(const Gamestate & game, int handid, short diff)
{
  id = handid;
  if(handid == 1) partner = 3; //left and right
  else if(handid == 2) partner = 0; //top and user
  else if(handid == 3) partner = 1; //right and left
  difficulty = diff;
}

Card * AI::makePlay(Gamestate & game)
{
  int play_suit = 5, max_val = 0, handlen = 0;
  handlen = game.get_handLen(id);
  /* 
   * Using the reference to our Gamestate
   * makes this part a lot easier.
   *
   * Gamestate has:
   * - int score[2]
   * - Card * allCardPlayed[52]
   * - int allWhoPlayed[52]
   * - Card * handCardsPlayed[4]
   * - int handWhoPlayed[4]
   * - Hand * hands[4]
   *
   *Reference these with game.function()
   *
   * These variables will come in handy when
   * deciding which card to play.
   *
   */


  /* EASY DIFFICULTY */
  if(difficulty == 0){
    //This AI goes first
    if(game.who_played[0] == -1){
      game.set_who_played(0,id);
      //If I have not invited, I will do so.
      if(!invited){
	invited = true;
	return game.get_card(id,0);
      }

      //Check for an invite from partner
      //(i%4 == 0 returns the first card from each trick played so far)
      for(int i = 0; i < 52; ++i){
	if(game.allWhoPlayed[i] == partner && i%4 == 0){
	  //My partner has invited, I will play as such
	  play_suit = game.allCardsPlayed[i]->get_suit();
	  for(int cardplay = 0; cardplay < handlen; ++cardplay){
	    if(game.get_card(id,cardplay)->get_suit() == play_suit){
	      return game.get_card(id,cardplay);
	    }
	  }
	}
      }
      //Looks like my partner has not invited yet, let's do this!
      for(int hand_card = 0; hand_card < handlen; ++hand_card){
	//I am going to find the highest card in my hand, and play that one
	if(max_val <= game.get_card(id,hand_card)->get_val()){
	  max_val = game.get_card(id,hand_card)->get_val();
	}
      }
      for(int i = 0; i < handlen; ++i){
	if(game.get_card(id,i)->get_val() == max_val){
	  return game.get_card(id,i);
	}
      }
    }
    //This AI is not going first this round
    else{
      play_suit = game.cards_played[0]->get_suit();
      for(int i = 0; i < handlen; ++i){
	if(game.get_card(id,i)->get_suit() == play_suit){
	  return game.get_card(id,i);
	}
      }
    }
  }

  /* INTERMEDIATE DIFFICULTY */
  if(difficulty == 1){

  }

  /* HARD DIFFICULTY */
  if(difficulty == 2){

  }

  /* IMPOSSIBLE DIFFICULTY */
  if(difficulty == 3){

  }
}
