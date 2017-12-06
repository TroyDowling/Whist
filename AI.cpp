#include "AI.h"

AI::AI (Card ** h, short diff)
{
	difficulty = diff;
	for(len = 0; h[len] != 0; ++len)
	for(int i = 0; i < len; ++i)
	{
		handarr[i] = h[i];
	}
}

AI::AI(Hand h, short diff)
{
  difficulty = diff;
  len = h.getLen();
  for(int i = 0; i < len; ++i)
    handarr[i] = h.getCard(i);
}

AI::AI(const Gamestate & game, int handid, short diff)
{
  difficulty = diff;
  for(int i = 0; i < game.get_handlen(handid); ++i)
    handarr[i] = game.get_card(handid, i);
}

Card * AI::makePlay(const Gamestate & game)
{
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
    if(game.handWhoPlayed[0] == -1){

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
