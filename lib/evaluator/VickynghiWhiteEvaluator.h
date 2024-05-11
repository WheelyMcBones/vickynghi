//
// Created by freddy on 13/05/19.
//

#ifndef OSARRACINO_VICKYNGHIWHITEEVALUATOR_H
#define OSARRACINO_VICKYNGHIWHITEEVALUATOR_H

#include "Evaluator.h"

const int VICKYNGHI_EVALUATOR_MAX_DEPTH = 2;
const int VICKYNGHI_EVALUATOR_SEARCH_WIN_POTENTIAL_MULTIPLIER = 10000;
const int VICKYNGHI_EVALUATOR_SEARCH_WIN_MULTIPLIER = 200000;
const int VICKYNGHI_EVALUATOR_SEARCH_LOSE_MULTIPLIER = -200000;
const int VICKYNGHI_EVALUATOR_FREE_WINPOINT_MULTIPLIER = 100;
const int VICKYNGHI_EVALUATOR_WHITE_WINPOINT_MULTIPLIER = 200;
const int VICKYNGHI_EVALUATOR_BLACK_WINPOINT_MULTIPLIER = -300;
const int VICKYNGHI_EVALUATOR_WHITE_PAWN_MULTIPLIER = 200;
const int VICKYNGHI_EVALUATOR_BLACK_PAWN_MULTIPLIER = -500;
const int VICKYNGHI_EVALUATOR_BLACK_HIGH_RISK_MULTIPLIER = -300;
const int VICKYNGHI_EVALUATOR_BLACK_RISK_MULTIPLIER = -300;
const int VICKYNGHI_EVALUATOR_BLACK_SURROUNDED_MULTIPLIER = -1000;

class VickynghiWhiteEvaluator : public Evaluator<VickynghiWhiteEvaluator> {
public:
    int evaluate(const Board &b) const;

    std::string get_name() const {
        return "VickynghiWhiteEvaluator";
    }

    int perform_search(const uint16_t *cols, const uint16_t *rows, int depth, int king_col, int king_row,
                       bool horizontal) const;

    int calculate_surrounded_penality(const uint16_t *cols, const uint16_t *rows,
                                      int king_col, int king_row) const;

    int calculate_white_winpoints(const Board &b) const;
    int calculate_black_winpoints(const Board &b) const;
    int geometry_points(const Board &b) const;

    int calculate_black_count_mask(const Board &b, const uint16_t *mask) const;

    int attacking_quadrant(const Board &b) const;
    std::vector<int> diagonals_attacking_quadrant(const Board &b) const;
    std::vector<int> num_blacks_for_quadrant(const Board &b) const;
    std::vector<int> num_free_escapes_for_quadrant(const Board &b) const;

    int empty_rows(const Board &b) const;
    int half_empty_rows(const Board &b) const;
    int empty_cols(const Board &b) const;
    int half_empty_cols(const Board &b) const;

    static const uint8_t BWG = 0;
    static const uint8_t BHW = 10; // Hot area
    static const uint8_t BMW = 5; // Mild area
    static const int8_t BCW = -1; // Cold area
    static const uint8_t PWG = 5;
    static const uint8_t GWG = 5;
    static const uint8_t MWG = GWG + 5;
    static const uint8_t empty_row_col_weight = 2;

    // matrix standard of weights for each cell
    int8_t color_matrix[9][9] = {
            {BWG, BWG, BWG, BWG, BWG, BWG, BWG, BWG, BWG},
            {BWG, BWG,  BWG,  BWG,  BWG,  BWG,  BWG,  BWG,  BWG},
            {BWG, BWG,  BWG,  PWG,  BWG,  PWG,  BWG,  BWG,  BWG},
            {BWG, BWG,  PWG,  BWG,  PWG,  BWG,  PWG,  BWG,  BWG},
            {BWG, BWG,  BWG,  PWG,  BWG,  PWG,  BWG,  BWG,  BWG},
            {BWG, BWG,  PWG,  BWG,  PWG,  BWG,  PWG,  BWG,  BWG},
            {BWG, BWG,  BWG,  PWG,  BWG,  PWG,  BWG,  BWG,  BWG},
            {BWG, BWG,  BWG,  BWG,  BWG,  BWG,  BWG,  BWG,  BWG},
            {BWG, BWG,  BWG,  BWG,  BWG,  BWG,  BWG,  BWG,  BWG},
    };

    int8_t top_right_color_matrix[9][9] = {
            {BWG, BWG,  BWG,  BWG,  BWG,  BWG,  MWG,  GWG,  BWG},
            {BWG, BWG,  BWG,  BWG,  BWG,  MWG,  BWG,  BWG,  GWG},
            {BWG, BWG,  BWG,  BWG,  BWG,  BWG,  BWG,  BWG,  MWG},
            {BWG, BWG,  PWG,  BWG,  BWG,  BWG,  BWG,  MWG,  BWG},
            {BWG, BWG,  BWG,  PWG,  BWG,  BWG,  BWG,  BWG,  BWG},
            {BWG, BWG,  BWG,  BWG,  PWG,  BWG,  BWG,  BWG,  BWG},
            {BWG, BWG,  BWG,  BWG,  BWG,  PWG,  BWG,  BWG,  BWG},
            {BWG, BWG,  BWG,  BWG,  BWG,  BWG,  BWG,  BWG,  BWG},
            {BWG, BWG,  BWG,  BWG,  BWG,  BWG,  BWG,  BWG,  BWG},
    };

    int8_t top_left_color_matrix[9][9] = {
            {BWG, GWG, MWG, BWG, BWG, BWG, BWG, BWG, BWG},
            {GWG, BWG,  BWG,  MWG,  BWG,  BWG,  BWG,  BWG,  BWG},
            {MWG, BWG,  BWG,  BWG,  BWG,  BWG,  BWG,  BWG,  BWG},
            {BWG, MWG,  BWG,  BWG,  BWG,  BWG,  PWG,  BWG,  BWG},
            {BWG, BWG,  BWG,  BWG,  BWG,  PWG,  BWG,  BWG,  BWG},
            {BWG, BWG,  BWG,  BWG,  PWG,  BWG,  BWG,  BWG,  BWG},
            {BWG, BWG,  BWG,  PWG,  BWG,  BWG,  BWG,  BWG,  BWG},
            {BWG, BWG,  BWG,  BWG,  BWG,  BWG,  BWG,  BWG,  BWG},
            {BWG, BWG,  BWG,  BWG,  BWG,  BWG,  BWG,  BWG,  BWG},
    };

    int8_t bottom_right_color_matrix[9][9] = {
            {BWG, BWG, BWG, BWG, BWG, BWG, BWG, BWG, BWG},
            {BWG, BWG,  BWG,  BWG,  BWG,  BWG,  BWG,  BWG,  BWG},
            {BWG, BWG,  BWG,  BWG,  BWG,  PWG,  BWG,  BWG,  BWG},
            {BWG, BWG,  BWG,  BWG,  PWG,  BWG,  BWG,  BWG,  BWG},
            {BWG, BWG,  BWG,  PWG,  BWG,  BWG,  BWG,  BWG,  BWG},
            {BWG, BWG,  PWG,  BWG,  BWG,  BWG,  BWG,  MWG,  BWG},
            {BWG, BWG,  BWG,  BWG,  BWG,  BWG,  BWG,  BWG,  MWG},
            {BWG, BWG,  BWG,  BWG,  BWG,  MWG,  BWG,  BWG,  GWG},
            {BWG, BWG,  BWG,  BWG,  BWG,  BWG,  MWG,  GWG,  BWG},
    };

    int8_t bottom_left_color_matrix[9][9] = {
            {BWG, BWG, BWG, BWG, BWG, BWG, BWG, BWG, BWG},
            {BWG, BWG,  BWG,  BWG,  BWG,  BWG,  BWG,  BWG,  BWG},
            {BWG, BWG,  BWG,  PWG,  BWG,  BWG,  BWG,  BWG,  BWG},
            {BWG, BWG,  BWG,  BWG,  PWG,  BWG,  BWG,  BWG,  BWG},
            {BWG, BWG,  BWG,  BWG,  BWG,  PWG,  BWG,  BWG,  BWG},
            {BWG, MWG,  BWG,  BWG,  BWG,  BWG,  PWG,  BWG,  BWG},
            {MWG, BWG,  BWG,  BWG,  BWG,  BWG,  BWG,  BWG,  BWG},
            {GWG, BWG,  BWG,  MWG,  BWG,  BWG,  BWG,  BWG,  BWG},
            {BWG, GWG,  MWG,  BWG,  BWG,  BWG,  BWG,  BWG,  BWG},
    };




};



#endif //OSARRACINO_VICKYNGHIWHITEEVALUATOR_H
