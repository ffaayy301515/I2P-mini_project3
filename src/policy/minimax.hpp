#pragma once
#include<unordered_map>
#include "../state/state.hpp"


/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
class Minimax{
private:
    
    static int minimax(State *state, int depth, int turn);
public:
    static Move get_move(State *state, int depth);
};