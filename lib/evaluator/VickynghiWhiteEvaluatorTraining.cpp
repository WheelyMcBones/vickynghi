//
// Created by freddy on 13/05/19.
//


#include "VickynghiWhiteEvaluatorTraining.h"

#include <set>
#include <bitset>
#include <algorithm>
#include <util/BoardUtils.h>
#include <util/BitUtils.h>
#include <unistd.h>
#include <fstream>
#include <stdio.h>
#include <string.h>

// Bonus or penality for the given king position
const int position_weight[9][9] = {
        {   0, 1000, 1000,   0,    0,   0, 1000, 1000,    0},
        {1000,  300,  200, 100,    0, 100,  200,  300, 1000},
        {1000,  200,  200, 200,  200, 200,  200,  200, 1000},
        {   0,  100,  200,   0,    0,   0,  200,  100,    0},
        {   0,    0,  200,   0,-9000,   0,  200,    0,    0},
        {   0,  100,  200,   0,    0,   0,  200,  100,    0},
        {1000,  300,  200, 200,  200, 200,  200,  300, 1000},
        {1000,  100,  200, 100,    0, 100,  200,  100, 1000},
        {   0, 1000, 1000,   0,    0,   0, 1000, 1000,    0},
};

const uint16_t black_risk_mask[9] = {
        0b0000000'011000110,
        0b0000000'111000111,
        0b0000000'110000011,
        0b0000000'000000000,
        0b0000000'000000000,
        0b0000000'000000000,
        0b0000000'110000011,
        0b0000000'111000111,
        0b0000000'011000110,
};

const uint16_t black_high_risk_mask[9] = {
        0b0000000'011000110,
        0b0000000'100000001,
        0b0000000'100000001,
        0b0000000'000000000,
        0b0000000'000000000,
        0b0000000'000000000,
        0b0000000'100000001,
        0b0000000'100000001,
        0b0000000'011000110,
};

int VickynghiWhiteEvaluatorTraining::evaluate(const Board &b) const {
    // TODO: check if obstacle rows/cols must not include king

    // Check if the board is a winning board
    if (b.is_white_win()) {
        return VICKYNGHI_EVALUATOR_SEARCH_WIN_MULTIPLIER;
    }else if (b.is_black_win()) {
        return VICKYNGHI_EVALUATOR_SEARCH_LOSE_MULTIPLIER;
    }

    // Calculate the best next move
    int horizontal_score = perform_search(b.obstacle_cols, b.obstacle_rows, VICKYNGHI_EVALUATOR_MAX_DEPTH, b.king_pos.col, b.king_pos.row, true);
    int vertical_score = perform_search(b.obstacle_cols, b.obstacle_rows, VICKYNGHI_EVALUATOR_MAX_DEPTH, b.king_pos.col, b.king_pos.row, false);

    int score = std::max(horizontal_score, vertical_score);

    int white_winpoints = calculate_white_winpoints(b);
    int black_winpoints = calculate_black_winpoints(b);
    int black_high_risk = calculate_black_count_mask(b, black_high_risk_mask);
    int black_risk = calculate_black_count_mask(b, black_risk_mask);

    // Consider also the number of free win points, the number
    // of white pawns and the number of black pawns.
    score += b.free_winpoints * VICKYNGHI_EVALUATOR_FREE_WINPOINT_MULTIPLIER +
             b.white_count * VICKYNGHI_EVALUATOR_WHITE_PAWN_MULTIPLIER +
             b.black_count * VICKYNGHI_EVALUATOR_BLACK_PAWN_MULTIPLIER +
             white_winpoints * VICKYNGHI_EVALUATOR_WHITE_WINPOINT_MULTIPLIER +
             black_winpoints * VICKYNGHI_EVALUATOR_BLACK_WINPOINT_MULTIPLIER +
             black_high_risk * VICKYNGHI_EVALUATOR_BLACK_HIGH_RISK_MULTIPLIER +
             black_risk * VICKYNGHI_EVALUATOR_BLACK_RISK_MULTIPLIER;


    // Consider the amount of cells that surround the king
    score += calculate_surrounded_penality(b.black_cols, b.black_rows, b.king_pos.col, b.king_pos.row);

    // Consider the position weight
    score += position_weight[b.king_pos.col][b.king_pos.row];
    score += empty_row_col_weight*empty_rows(b) + half_empty_cols(b) + half_empty_rows(b) + empty_row_col_weight*empty_cols(b);
    score += geometry_points(b);
    return score;
}

int VickynghiWhiteEvaluatorTraining::evaluate(const Board &b, bool print) const {
    int quad = attacking_quadrant(b);
    std::vector<int> blocked_diagonals = formed_black_diagonals_for_quadrant(b);
    std::cout << "[value] alto dx " + std::to_string(blocked_diagonals[0]) << std::endl;
    std::cout << "[value] alto sx " + std::to_string(blocked_diagonals[1]) << std::endl;
    std::cout << "[value] basso dx " + std::to_string(blocked_diagonals[2]) << std::endl;
    std::cout << "[value] basso sx " + std::to_string(blocked_diagonals[3]) << std::endl;

    switch(quad){
        case 0:
            std::cout << "[info] alto dx" << std::endl;
            break;
        case 1:
            std::cout << "[info] alto sx" << std::endl;
            break;
        case 2:
            std::cout << "[info] basso dx" << std::endl;
            break;
        case 3:
            std::cout << "[info] basso sx" << std::endl;
            break;
        default:
            std::cout << "[info] no choice" << std::endl;
            break;
    }
    return evaluate(b);
}

int
VickynghiWhiteEvaluatorTraining::perform_search(const uint16_t *cols, const uint16_t *rows, int depth, int king_col, int king_row,
                                      bool horizontal) const {
    if (depth == 0) {
        return 0;  // TODO: return a value based on the distance from the nearest win point
    }

    int high_score = 0;
    int low_score = 0;

    if (horizontal) {
        int high_moves = BitUtils::get_high_moves(rows[king_row], king_col);
        int low_moves = BitUtils::get_low_moves(rows[king_row], king_col);

        // Check if the king is in a win position
        if (king_col - low_moves == 0 && king_col + high_moves == 8) {  // Double side winning
            return VICKYNGHI_EVALUATOR_SEARCH_WIN_POTENTIAL_MULTIPLIER * depth * 2;
        } else if (king_col - low_moves == 0 || king_col + high_moves == 8) {  // Single side winning
            return VICKYNGHI_EVALUATOR_SEARCH_WIN_POTENTIAL_MULTIPLIER * depth;
        }

        for (int i = (king_col + 1); i <= (king_col + high_moves); i++) {
            high_score = std::max(perform_search(cols, rows, depth - 1, i, king_row, false), high_score);
        }
        for (int i = (king_col - 1); i >= (king_col - low_moves); i--) {
            low_score = std::max(perform_search(cols, rows, depth - 1, i, king_row, false), low_score);
        }
    } else {
        int high_moves = BitUtils::get_high_moves(cols[king_col], king_row);
        int low_moves = BitUtils::get_low_moves(cols[king_col], king_row);

        // Check if the king is in a win position
        if (king_row - low_moves == 0 && king_row + high_moves == 8) {  // Double side winning
            return VICKYNGHI_EVALUATOR_SEARCH_WIN_POTENTIAL_MULTIPLIER * depth * 2;
        } else if (king_row - low_moves == 0 || king_row + high_moves == 8) {  // Single side winning
            return VICKYNGHI_EVALUATOR_SEARCH_WIN_POTENTIAL_MULTIPLIER * depth;
        }

        for (int i = (king_row + 1); i <= (king_row + high_moves); i++) {
            high_score = std::max(perform_search(cols, rows, depth - 1, king_col, i, true), high_score);
        }
        for (int i = (king_row - 1); i >= (king_row - low_moves); i--) {
            low_score = std::max(perform_search(cols, rows, depth - 1, king_col, i, true), low_score);
        }
    }

    return std::max(low_score, high_score);
}

int VickynghiWhiteEvaluatorTraining::geometry_points(const Board &b) const {

    // TODO: fare un'unica mappa per ogni sezione
    int quadrant = attacking_quadrant(b);
    switch(quadrant){
        case 0:
            return geometry_calculator(b, top_right_color_matrix);
        case 1:
            return geometry_calculator(b, bottom_right_color_matrix);
        case 2:
            return geometry_calculator(b, bottom_left_color_matrix);
        case 3:
            return geometry_calculator(b, top_left_color_matrix);
        default:
            return geometry_calculator(b, color_matrix);
    }
}

std::vector<int> VickynghiWhiteEvaluatorTraining::diagonals_attacking_quadrant(const Board &b) const {
    // diagonale formata
    std::vector<int> quadrants(4, 0);
    quadrants[0] = b.has_white(2,3)+b.has_white(3,4)+b.has_white(4,5)+b.has_white(5,6);
    quadrants[1] = b.has_white(3,6)+b.has_white(4,5)+b.has_white(5,4)+b.has_white(6,3);
    quadrants[2] = b.has_white(2,5)+b.has_white(3,4)+b.has_white(4,3)+b.has_white(5,2);
    quadrants[3] = b.has_white(3,2)+b.has_white(4,3)+b.has_white(5,4)+b.has_white(6,5);
    return quadrants;
}

std::vector<int> VickynghiWhiteEvaluatorTraining::num_blacks_for_quadrant(const Board &b) const{

    std::vector<int> result = std::vector<int>(4,0);
    for(int i = 0; i < 9; i++){
        if(i <= 4){ // top
            result[1] += BitUtils::popcount(b.black_rows[i] >> 4); // left
            result[0] += BitUtils::popcount(b.black_rows[i] << 4); // right
        }
        if(i >= 4){ // bottom
            result[3] += BitUtils::popcount(b.black_rows[i] >> 4); // left
            result[2] += BitUtils::popcount(b.black_rows[i] << 4); // right
        }
    }

    return result;
}

std::vector<int> VickynghiWhiteEvaluatorTraining::num_free_escapes_for_quadrant(const Board &b, const uint16_t *mask) const {

    std::vector<int> result = std::vector<int>(4,0);
    for (int i = 0; i<9; i++) {
        if(i <= 4){
            result[1] += BitUtils::popcount((b.black_rows[i] >> 4) & mask[i]);
            result[0] += BitUtils::popcount((b.black_rows[i] << 4) & mask[i]);
        }
        if(i >= 4){
            result[3] += BitUtils::popcount((b.black_rows[i] >> 4) & mask[i]);
            result[2] += BitUtils::popcount((b.black_rows[i] << 4) & mask[i]);
        }
    }
    return result;
}

int VickynghiWhiteEvaluatorTraining::attacking_quadrant(const Board &b) const {

    std::vector<int> vect_result = std::vector<int>(4,0);
    std::vector<int> diagonals = diagonals_attacking_quadrant(b);
    std::vector<int> blacks = num_blacks_for_quadrant(b);
    std::vector<int> free_escapes = num_free_escapes_for_quadrant(b, black_high_risk_mask);
    std::vector<int> blocked_diagonals = formed_black_diagonals_for_quadrant(b);
    vect_result[0] = diagonals[0] - (4 - free_escapes[0]) + (16 - blacks[0]) + (blocked_diagonals[0] * PENALTY);
    vect_result[1] = diagonals[1] - (4 - free_escapes[1]) + (16 - blacks[1]) + (blocked_diagonals[1] * PENALTY);;
    vect_result[2] = diagonals[2] - (4 - free_escapes[2]) + (16 - blacks[2]) + (blocked_diagonals[2] * PENALTY);;
    vect_result[3] = diagonals[3] - (4 - free_escapes[3]) + (16 - blacks[3]) + (blocked_diagonals[3] * PENALTY);;
    return std::max_element(vect_result.begin(), vect_result.end()) - vect_result.begin();
}

std::vector<int> VickynghiWhiteEvaluatorTraining::formed_black_diagonals_for_quadrant(const Board &b) const {

    std::vector<int> result = std::vector<int>(4,0);

    if((b.has_black(5,2) && b.has_black(6,3)) || (b.has_black(5,1) && b.has_black(6,2) && b.has_black(7,3)) || (b.has_black(6,1) && (b.has_black(7,2)))){
        result[0]++;
    }

    if((b.has_black(3,2) && b.has_black(2,3)) || (b.has_black(3,1) && b.has_black(2,2) && b.has_black(1,3)) || (b.has_black(2,1) && (b.has_black(1,2)))){
        result[1]++;
    }

    if((b.has_black(5,6) && b.has_black(6,5)) || (b.has_black(5,7) && b.has_black(6,6) && b.has_black(7,5)) || (b.has_black(6,7) && (b.has_black(7,6)))){
        result[2]++;
    }

    if((b.has_black(3,6) && b.has_black(2,5)) || (b.has_black(3,7) && b.has_black(2,6) && b.has_black(1,5)) || (b.has_black(2,7) && (b.has_black(1,6)))){
        result[3]++;
    }

    return result;
}

int VickynghiWhiteEvaluatorTraining::calculate_surrounded_penality(const uint16_t *cols, const uint16_t *rows, int king_col,
                                                         int king_row) const {

    int horizontal_surroundings = BitUtils::get_surrounded(rows[king_row] | citadels_mask[king_row], king_col);
    int vertical_surroundings = BitUtils::get_surrounded(cols[king_col] | citadels_mask[king_col], king_row);

    return horizontal_surroundings * VICKYNGHI_EVALUATOR_BLACK_SURROUNDED_MULTIPLIER +
           vertical_surroundings * VICKYNGHI_EVALUATOR_BLACK_SURROUNDED_MULTIPLIER;
}

int VickynghiWhiteEvaluatorTraining::calculate_white_winpoints(const Board &b) const {
    int count = 0;
    count += BitUtils::popcount(b.white_rows[0] & 0b0000000'011000110);
    count += BitUtils::popcount(b.white_rows[8] & 0b0000000'011000110);
    count += BitUtils::popcount(b.white_cols[0] & 0b0000000'011000110);
    count += BitUtils::popcount(b.white_cols[8] & 0b0000000'011000110);
    return count;
}

int VickynghiWhiteEvaluatorTraining::calculate_black_winpoints(const Board &b) const {
    int count = 0;
    count += BitUtils::popcount(b.black_rows[0] & 0b0000000'011000110);
    count += BitUtils::popcount(b.black_rows[8] & 0b0000000'011000110);
    count += BitUtils::popcount(b.black_cols[0] & 0b0000000'011000110);
    count += BitUtils::popcount(b.black_cols[8] & 0b0000000'011000110);
    return count;
}



int VickynghiWhiteEvaluatorTraining::calculate_black_count_mask(const Board &b, const uint16_t *mask) const {
    int count = 0;
    for (int i = 0; i<9; i++) {
        count += BitUtils::popcount(b.black_cols[i] & mask[i]);
    }
    return count;
}

int VickynghiWhiteEvaluatorTraining::empty_rows(const Board &b) const {
    int count = 0;
    for (int i = 0; i<9; i++) {
        if(BitUtils::popcount(b.black_rows[i] | b.white_rows[i]) == 0){
            count ++;
        }
    }
    return count;
}

int VickynghiWhiteEvaluatorTraining::half_empty_rows(const Board &b) const {
    int count = 0;
    for (int i = 0; i<9; i++) {
        int var = (b.black_rows[i] | b.white_rows[i]);
        if((BitUtils::popcount(var) == 1) && ((var < 4) || (var >= 64))){
            count++;
        }
    }
    return count;
}

int VickynghiWhiteEvaluatorTraining::empty_cols(const Board &b) const {
    int count = 0;
    for (int i = 0; i<9; i++) {
        if(BitUtils::popcount(b.black_cols[i] | b.white_cols[i]) == 0){
            count ++;
        }
    }
    return count;
}

int VickynghiWhiteEvaluatorTraining::half_empty_cols(const Board &b) const {
    int count = 0;
    for (int i = 0; i<9; i++) {
        int var = (b.black_cols[i] | b.white_cols[i]);
        if((BitUtils::popcount(var) == 1) && ((var < 4) || (var >= 64))){
            count++;
        }
    }
    return count;
}

VickynghiWhiteEvaluatorTraining::VickynghiWhiteEvaluatorTraining() {
    geometry_calculator = [](const Board &b, const int8_t (&matrix)[9][9]) ->int {
        int result {0};
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (b.board[i][j] == Pawn::White) {
                    result += matrix[i][j];
                }
            }
        }
        return result;
    };

    std::cout << "CARICO EURISICA" <<std::endl;
    int pid = 0;//getppid();
    char * temp;
    std::string mytext;
    std::ifstream MyReadFile("/tmp/tablut/playerHeuristicWhite"+std::to_string(pid));
     while(getline(MyReadFile, mytext)){
        std::cout << mytext <<std::endl;
        char *cstr = &mytext[0];

        temp = strtok(cstr,",");
        BHW = atoi(temp);

        temp = strtok(cstr,",");
        BMW = atoi(temp);

        temp = strtok(cstr,",");
        PWG = atoi(temp);

        temp = strtok(cstr,",");
        GWG = atoi(temp);

        temp = strtok(cstr,",");
        MWG = atoi(temp);
    }

    printf ("%d\n",BHW);
    std::cout << "Euristica caricata"<<std::endl;
}
