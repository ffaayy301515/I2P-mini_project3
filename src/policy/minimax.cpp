#include<cstdlib>
#include<fstream>
#include<algorithm>
#include<unordered_map>

#include "../state/state.hpp"
#include "./minimax.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Minimax::get_move(State *state, int depth){
    if(!state->legal_actions.size())
        state->get_legal_actions();
    auto actions = state->legal_actions;

    int best_val = INT32_MIN;
    Move best_move;

    std::unordered_map<State*, int> table;

    for(auto act: actions){
        State* next_state = state->next_state(act);
        int val = minimax(next_state, depth-1, 0, table);
        // delete next_state;
        if(val > best_val){
            best_move = act;
            best_val = val;
        }
    }
    return best_move;
}

int Minimax::minimax(State *state, int depth, int turn, std::unordered_map<State*, int> table){
    // if(depth <= 0) return state->evaluate(turn);
    if(!state->legal_actions.size())
        state->get_legal_actions();
    auto actions = state->legal_actions;

    if(depth <= 0 || (state->game_state == WIN || state->game_state == DRAW) || actions.empty()) 
        return state->evaluate(turn);

    if(table.find(state) != table.end()) return table[state];

    if(!turn){
        int max_val = INT32_MIN;
        for(auto act: actions){
            State* next_state = state->next_state(act);
            int val = minimax(next_state, depth-1, 1, table);
            max_val = std::max(max_val, val);
            table[next_state] = val;
        }
        return max_val;
    }
    
    int min_val = INT32_MAX;
    for(auto act: actions){
        State* next_state = state->next_state(act);
        int val = minimax(next_state, depth-1, 0, table);
        min_val = std::min(min_val, val);
        table[next_state] = val;
    }
    return min_val;
}