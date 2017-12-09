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
  int play_suit = 5;
  
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

      //Check for an invite from partner
      //(i%4 == 0 returns the first card from each trick played so far)
      for(int i = 0; i < 52; ++i){
	if(game.allWhoPlayed[i] == partner && i%4 == 0){
	  play_suit = game.allCardsPlayed[i]->get_suit();
	}
	else{
	  //My parter has not led yet, have I?
	  if(game.allWhoPlayed[i] == id && i%4 == 0){
	    //I have led, so no need to invite.
	    for(int hand_card = 0; hand_card < game.get_handLen(id); ++hand_card){

	    }
	  }
	  //else
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
