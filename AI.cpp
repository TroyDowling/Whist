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
  int play_suit = 0, max_val = 0, min_val = 0, handlen = 0;
  handlen = game.get_handLen(id);
  Card * play_card;
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


  /* EASY DIFFICULTY 
  *
  * Doesn't take value into consideration
  * or what has already been played.
  * Plays the first matching card it can
  * find each time.
  *
  */
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
	  //I cannot play back my partner's invite
	  return game.get_card(id,0);
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
      return game.get_card(id,0);
    }
  }

  /* INTERMEDIATE DIFFICULTY
   *
   * This difficulty has very similar logic
   * when compared to the Easy. It makes
   * slightly better value judgements.
   *
   */
  if(difficulty == 1){
    //This AI goes first
    if(game.who_played[0] == -1){
      game.set_who_played(0,id);
      //If I have not invited, I will do so.
      if(!invited){
	invited = true;
	//What is the highest valued card I have?
	for(int i = 0; i < handlen; ++i){
	  if(max_val <= game.get_card(id,i)->get_val()){
	    max_val = game.get_card(id,i)->get_val();
	  }
	}
	//What suit is it?
	for(int i = 0; i < handlen; ++i){
	  if(game.get_card(id,i)->get_val() == max_val){
	    play_suit = game.get_card(id,i)->get_suit();
	  }
	}
	//I'm going to find the lowest card in this suit
	for(int i = 0; i < handlen; ++i){
	  if(min_val >= game.get_card(id,i)->get_val() && game.get_card(id,i)->get_suit() == play_suit){
	    min_val = game.get_card(id,i)->get_val();
	  }
	}
	//Now I'm going to play that card
	for(int i = 0; i < handlen; ++i){
	  if(game.get_card(id,i)->get_val == min_val && game.get(id,i)->get_suit() == play_suit){
	    return game.get_card(id,i);
	  }
	}
      }

      //Check for an invite from partner
      //(i%4 == 0 returns the first card from each trick played so far)
      for(int i = 0; i < 52; ++i){
	if(game.allWhoPlayed[i] == partner && i%4 == 0){
	  //My partner has invited, I will play as such
	  play_suit = game.allCardsPlayed[i]->get_suit();
	  //What is the lowest card of this suit that I have?
	  for(int cardplay = 0; cardplay < handlen; ++cardplay){
	    if(game.get_card(id,cardplay)->get_val() <= min_val){
	      min_val = game.get_card(id,cardplay);
	    }
	  }
	  //Play the lowest card I have in the suit my partner invited in
	  for(int cardplay = 0; cardplay < handlen; ++cardplay){
	    play_card = game.get_card(id,0);
	    if(play_card->get_suit == play_suit && play_card->get_val() == min_val){
	      return play_card;
	    }
	  }
	}
      }
      //Looks like my partner has not invited yet, or I can't play that suit let's do this!
      for(int hand_card = 0; hand_card < handlen; ++hand_card){

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

  /* HARD DIFFICULTY 
   *
   * Ideally this difficulty level will be quite
   * the step up from the previous two. It will
   * look back at what has been played, and will
   * make its decision based upon this data.
   *
   */
  if(difficulty == 2){
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

  /* IMPOSSIBLE DIFFICULTY */
  if(difficulty == 3){
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
}
