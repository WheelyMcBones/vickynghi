//
// Created by max on 25/04/19.
//

#include "DTranspositionTable.h"

void DTranspositionTable::clean_table() {

}

void DTranspositionTable::add_entry(const Board &b, int score, const std::pair<Position, Position> &best_move, Flag flag,
                                     int depth) {

    //Now we use always replace as replacement schema.
    auto hash_value = zobrist_hash.hash(b);
    int index = hash_value % DIMENSION;

    if (transposition_table.find(index) != transposition_table.end()) {
        transposition_table[index] = {score, best_move, flag, hash_value, depth};
    } else {
        if (transposition_table[index].depth < depth) {
            transposition_table[index] = {score, best_move, flag, hash_value, depth};
        }
    }

}

BoardEvaluation DTranspositionTable::get_entry(const Board &b) const {
    auto hash_value = zobrist_hash.hash(b);
    return transposition_table.at(hash_value % DIMENSION);
}

bool DTranspositionTable::has_entry(const Board &b) {
    auto hash_value = zobrist_hash.hash(b);
    int index = hash_value % DIMENSION;

    return transposition_table.find(index) != transposition_table.end();
}
