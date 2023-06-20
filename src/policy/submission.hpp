#pragma once
#include<unordered_map>
#include "../state/state.hpp"


/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
class Alphabeta{
private:
    
    static int alphabeta(State *state, int alpha, int beta, int depth, int my_turn);
public:
    static Move get_move(State *state, int depth);
};