#include<cstdlib>
#include<fstream>
#include<algorithm>
#include<unordered_map>

#include "../state/state.hpp"
#include "./alphabeta.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Alphabeta::get_move(State *state, int depth){
    if(!state->legal_actions.size())
        state->get_legal_actions();
    auto actions = state->legal_actions;

    int best_val = INT32_MIN;
    Move best_move = actions[0];

    // std::unordered_map<std::string, int> table;

    for(auto act: actions){
        State* next_state = state->next_state(act);
        int val = alphabeta(next_state, INT32_MIN, INT32_MAX, depth-1, 0);
        // delete next_state;
        if(val > best_val){
            best_move = act;
            best_val = val;
        }
    }
    return best_move;
}

int Alphabeta::alphabeta(State *state, int alpha, int beta, int depth, int my_turn){
    // if(depth <= 0) return state->evaluate(turn);
    if(!state->legal_actions.size())
        state->get_legal_actions();
    auto actions = state->legal_actions;

    if(depth <= 0|| actions.empty()) 
        return my_turn ? state->evaluate() : -state->evaluate();

    if(state->game_state == WIN) return my_turn ? INT32_MAX : INT32_MIN;
    if(state->game_state == DRAW) return 0;

    // if(table.find(state->encode_state()) != table.end()) return table[state->encode_state()];

    if(my_turn){
        int max_val = INT32_MIN;
        for(auto act: actions){
            State* next_state = state->next_state(act);
            int val = alphabeta(next_state, alpha, beta, depth-1, 0);
            max_val = std::max(max_val, val);
            alpha = std::max(max_val, alpha);
            if(alpha >= beta) break;
        }
        // table[state->encode_state()] = max_val;
        return max_val;
    }
    
    int min_val = INT32_MAX;
    for(auto act: actions){
        State* next_state = state->next_state(act);
        int val = alphabeta(next_state, alpha, beta, depth-1, 1);
        min_val = std::min(min_val, val);
        beta = std::min(min_val, beta);
        if(alpha >= beta) break;
    }
    // table[state->encode_state()] = min_val;
    return min_val;
}