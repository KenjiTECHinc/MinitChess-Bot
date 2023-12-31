#include <cstdlib>

#include "../state/state.hpp"
#include "./minimax.hpp"
using namespace std;

/**
 * @brief Get a legal action
 *
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move
 */

int minimax(State *state, int depth, bool maximizingPlayer){
  if(depth==3){
    int score = state->evaluate();
    delete state;
    return score;
  }
  int best;
  if(maximizingPlayer){
    best = -1000000;
    for(auto move: state->legal_actions){
    int score = minimax(state->next_state(move), depth+1,false);
    if (score>=best)
      best = score;
    }
  }
  else{
    best = 1000000;
    for(auto move: state->legal_actions){
    int score = minimax(state->next_state(move), depth+1,true);
    if (score<=best)
      best = score;
    }
  }
  return best;
};

Move Minimax::get_move(State *state, int depth){
  Move best_move = state->legal_actions[state->legal_actions.size() - 1];
  int best_score = -1000000;

  for(Move move: state->legal_actions){
    int score = minimax(state->next_state(move), depth, false);
    //if(score > best_score){ // <-- originally this one.
    if(score>best_score){ //this part can cause the opening move to be the same. find a new opening move. 
      best_move = move;
      best_score = score;
    }
  }
  //Debug.
  //std::cout << best_move.first.first << " " << best_move.first.second << " " << best_move.second.first << " " << best_move.second.second << std::endl;
  return best_move;
};

