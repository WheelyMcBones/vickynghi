//
// Created by freddy on 15/04/19.
//

#ifndef OSARRACINO_BLACKEVALUATOR_H
#define OSARRACINO_BLACKEVALUATOR_H

#include "Evaluator.h"
#include <vector>
#include <tuple>
#include <array>
#include <unordered_map>
#include <functional>

enum Direction {Up=1, Down=2, Right=3, Left=4, None=false};
const std::array<int, 4> win_rows_cols = {1, 2, 6, 7};

class BlackEvaluator : public Evaluator<BlackEvaluator>{
public:
    std::string get_name() const {
        return "BlackEvaluator";
    }

    BlackEvaluator();
    int evaluate(const Board &b) const;
    int black_block_king(const Board &b) const;
    int pawn_differences(const Board &b) const;
    int geometry_points(const Board &b) const;
    int get_empty_row_down(const Board &b) const;
    int get_empty_row_up(const Board &b) const;
    int get_empty_col_right(const Board &b) const;
    int get_empty_col_left(const Board &b) const;
    int avoid_same_row_or_col(const Board &b) const;
    std::vector<Direction> get_direction_of_move_check(const Board &b)const;
    std::function<int(const Board &b, const uint8_t (&matrix)[9][9])> geometry_calculator;

    static const uint8_t BLANK_WG = 0;
    static const uint8_t CYAN_WG = 1;
    static const uint8_t PURPLE_WG = 0;
    static const int EZPZ = 200000;
    static const int PREVENT_CHECKMATE = -1000;

    uint8_t color_matrix[9][9] = {
            {BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG},
            {BLANK_WG, BLANK_WG, PURPLE_WG, BLANK_WG, CYAN_WG, BLANK_WG, PURPLE_WG},
            {BLANK_WG, PURPLE_WG, BLANK_WG, CYAN_WG, BLANK_WG, CYAN_WG, BLANK_WG, PURPLE_WG, BLANK_WG },
            {BLANK_WG, BLANK_WG, CYAN_WG, BLANK_WG, BLANK_WG, BLANK_WG, CYAN_WG, BLANK_WG, BLANK_WG},
            {BLANK_WG, CYAN_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, CYAN_WG, BLANK_WG},
            {BLANK_WG, BLANK_WG, CYAN_WG, BLANK_WG, BLANK_WG, BLANK_WG, CYAN_WG, BLANK_WG, BLANK_WG},
            {BLANK_WG, PURPLE_WG, BLANK_WG, CYAN_WG, BLANK_WG, CYAN_WG, BLANK_WG, PURPLE_WG, BLANK_WG},
            {BLANK_WG, BLANK_WG, PURPLE_WG, BLANK_WG, CYAN_WG, BLANK_WG, PURPLE_WG},
            {BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG},

    };

    uint8_t top_color_matrix[9][9] = {
            {BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG},
            {BLANK_WG, BLANK_WG, PURPLE_WG*2, BLANK_WG, CYAN_WG*2, BLANK_WG, 2*PURPLE_WG},
            {BLANK_WG, PURPLE_WG*2, BLANK_WG, CYAN_WG*2, BLANK_WG, CYAN_WG*2, BLANK_WG, 2*PURPLE_WG, BLANK_WG },
            {BLANK_WG, BLANK_WG, CYAN_WG*2, BLANK_WG, BLANK_WG, BLANK_WG, 2*CYAN_WG, BLANK_WG, BLANK_WG},
            {BLANK_WG, CYAN_WG*2, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, 2*CYAN_WG, BLANK_WG},
            {BLANK_WG, BLANK_WG, CYAN_WG, BLANK_WG, BLANK_WG, BLANK_WG, CYAN_WG, BLANK_WG, BLANK_WG},
            {BLANK_WG, PURPLE_WG, BLANK_WG, CYAN_WG, BLANK_WG, CYAN_WG, BLANK_WG, PURPLE_WG, BLANK_WG},
            {BLANK_WG, BLANK_WG, PURPLE_WG, BLANK_WG, CYAN_WG, BLANK_WG, PURPLE_WG},
            {BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG},

    };
    uint8_t bottom_color_matrix[9][9] = {
            {BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG},
            {BLANK_WG, BLANK_WG, PURPLE_WG, BLANK_WG, CYAN_WG, BLANK_WG, PURPLE_WG},
            {BLANK_WG, PURPLE_WG, BLANK_WG, CYAN_WG, BLANK_WG, CYAN_WG, BLANK_WG, PURPLE_WG, BLANK_WG },
            {BLANK_WG, BLANK_WG, CYAN_WG, BLANK_WG, BLANK_WG, BLANK_WG, CYAN_WG, BLANK_WG, BLANK_WG},
            {BLANK_WG, CYAN_WG*2, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, 2*CYAN_WG, BLANK_WG},
            {BLANK_WG, BLANK_WG, CYAN_WG*2, BLANK_WG, BLANK_WG, BLANK_WG, 2*CYAN_WG, BLANK_WG, BLANK_WG},
            {BLANK_WG, PURPLE_WG*2, BLANK_WG, 2*CYAN_WG, BLANK_WG, 2*CYAN_WG, BLANK_WG, 2*PURPLE_WG, BLANK_WG},
            {BLANK_WG, BLANK_WG, PURPLE_WG*2, BLANK_WG, 2*CYAN_WG, BLANK_WG, 2*PURPLE_WG},
            {BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG},

    };
    uint8_t right_color_matrix[9][9] = {
            {BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG},
            {BLANK_WG, BLANK_WG, PURPLE_WG, BLANK_WG, 2*CYAN_WG, BLANK_WG, PURPLE_WG},
            {BLANK_WG, PURPLE_WG, BLANK_WG, CYAN_WG, BLANK_WG, 2*CYAN_WG, BLANK_WG, PURPLE_WG, BLANK_WG },
            {BLANK_WG, BLANK_WG, CYAN_WG, BLANK_WG, BLANK_WG, BLANK_WG, 2*CYAN_WG, BLANK_WG, BLANK_WG},
            {BLANK_WG, CYAN_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, 2*CYAN_WG, BLANK_WG},
            {BLANK_WG, BLANK_WG, CYAN_WG, BLANK_WG, BLANK_WG, BLANK_WG, 2*CYAN_WG, BLANK_WG, BLANK_WG},
            {BLANK_WG, PURPLE_WG, BLANK_WG, CYAN_WG, BLANK_WG, 2*CYAN_WG, BLANK_WG, 2*PURPLE_WG, BLANK_WG},
            {BLANK_WG, BLANK_WG, PURPLE_WG, BLANK_WG, 2*CYAN_WG, BLANK_WG, 2*PURPLE_WG},
            {BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG},

    };
    uint8_t left_color_matrix[9][9] = {
            {BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG},
            {BLANK_WG, BLANK_WG, PURPLE_WG, BLANK_WG, 2*CYAN_WG, BLANK_WG, PURPLE_WG},
            {BLANK_WG, PURPLE_WG, BLANK_WG, 2*CYAN_WG, BLANK_WG, CYAN_WG, BLANK_WG, PURPLE_WG, BLANK_WG },
            {BLANK_WG, BLANK_WG, 2*CYAN_WG, BLANK_WG, BLANK_WG, BLANK_WG, CYAN_WG, BLANK_WG, BLANK_WG},
            {BLANK_WG, 2*CYAN_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, CYAN_WG, BLANK_WG},
            {BLANK_WG, BLANK_WG, 2*CYAN_WG, BLANK_WG, BLANK_WG, BLANK_WG, CYAN_WG, BLANK_WG, BLANK_WG},
            {BLANK_WG, PURPLE_WG, BLANK_WG, 2*CYAN_WG, BLANK_WG, CYAN_WG, BLANK_WG, PURPLE_WG, BLANK_WG},
            {BLANK_WG, BLANK_WG, PURPLE_WG, BLANK_WG, 2*CYAN_WG, BLANK_WG, PURPLE_WG},
            {BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG},

    };

    uint8_t top_right_color_matrix[9][9] = {
            {BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG},
            {BLANK_WG, BLANK_WG, PURPLE_WG, BLANK_WG, CYAN_WG*2, BLANK_WG, PURPLE_WG},
            {BLANK_WG, PURPLE_WG, BLANK_WG, CYAN_WG, BLANK_WG, 2*CYAN_WG, BLANK_WG, PURPLE_WG, BLANK_WG },
            {BLANK_WG, BLANK_WG, CYAN_WG, BLANK_WG, BLANK_WG, BLANK_WG, 2*CYAN_WG, BLANK_WG, BLANK_WG},
            {BLANK_WG, CYAN_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, 2*CYAN_WG, BLANK_WG},
            {BLANK_WG, BLANK_WG, CYAN_WG, BLANK_WG, BLANK_WG, BLANK_WG, 2*CYAN_WG, BLANK_WG, BLANK_WG},
            {BLANK_WG, PURPLE_WG, BLANK_WG, CYAN_WG, BLANK_WG, CYAN_WG, BLANK_WG, PURPLE_WG, BLANK_WG},
            {BLANK_WG, BLANK_WG, PURPLE_WG, BLANK_WG, CYAN_WG, BLANK_WG, PURPLE_WG},
            {BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG},

    };
    uint8_t top_left_color_matrix[9][9] = {
            {BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG},
            {BLANK_WG, BLANK_WG, PURPLE_WG, BLANK_WG, CYAN_WG*2, BLANK_WG, PURPLE_WG},
            {BLANK_WG, PURPLE_WG, BLANK_WG, CYAN_WG*2, BLANK_WG, CYAN_WG, BLANK_WG, PURPLE_WG, BLANK_WG },
            {BLANK_WG, BLANK_WG, CYAN_WG*2, BLANK_WG, BLANK_WG, BLANK_WG, CYAN_WG, BLANK_WG, BLANK_WG},
            {BLANK_WG, CYAN_WG*2, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, CYAN_WG, BLANK_WG},
            {BLANK_WG, BLANK_WG, CYAN_WG, BLANK_WG, BLANK_WG, BLANK_WG, CYAN_WG, BLANK_WG, BLANK_WG},
            {BLANK_WG, PURPLE_WG, BLANK_WG, CYAN_WG, BLANK_WG, CYAN_WG, BLANK_WG, PURPLE_WG, BLANK_WG},
            {BLANK_WG, BLANK_WG, PURPLE_WG, BLANK_WG, CYAN_WG, BLANK_WG, PURPLE_WG},
            {BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG},

    };
    uint8_t bottom_right_color_matrix[9][9] = {
            {BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG},
            {BLANK_WG, BLANK_WG, PURPLE_WG, BLANK_WG, CYAN_WG, BLANK_WG, PURPLE_WG},
            {BLANK_WG, PURPLE_WG, BLANK_WG, CYAN_WG, BLANK_WG, CYAN_WG, BLANK_WG, PURPLE_WG, BLANK_WG },
            {BLANK_WG, BLANK_WG, CYAN_WG, BLANK_WG, BLANK_WG, BLANK_WG, CYAN_WG, BLANK_WG, BLANK_WG},
            {BLANK_WG, CYAN_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, 2*CYAN_WG, BLANK_WG},
            {BLANK_WG, BLANK_WG, CYAN_WG, BLANK_WG, BLANK_WG, BLANK_WG, CYAN_WG*2, BLANK_WG, BLANK_WG},
            {BLANK_WG, PURPLE_WG, BLANK_WG, CYAN_WG, BLANK_WG, CYAN_WG*2, BLANK_WG, PURPLE_WG*2, BLANK_WG},
            {BLANK_WG, BLANK_WG, PURPLE_WG, BLANK_WG, CYAN_WG*2, BLANK_WG, PURPLE_WG*2},
            {BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG},

    };
    uint8_t bottom_left_color_matrix[9][9] = {
            {BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG},
            {BLANK_WG, BLANK_WG, PURPLE_WG, BLANK_WG, CYAN_WG, BLANK_WG, PURPLE_WG},
            {BLANK_WG, PURPLE_WG, BLANK_WG, CYAN_WG, BLANK_WG, CYAN_WG, BLANK_WG, PURPLE_WG, BLANK_WG },
            {BLANK_WG, BLANK_WG, CYAN_WG, BLANK_WG, BLANK_WG, BLANK_WG, CYAN_WG, BLANK_WG, BLANK_WG},
            {BLANK_WG, CYAN_WG*2, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, CYAN_WG, BLANK_WG},
            {BLANK_WG, BLANK_WG, CYAN_WG*2, BLANK_WG, BLANK_WG, BLANK_WG, CYAN_WG, BLANK_WG, BLANK_WG},
            {BLANK_WG, PURPLE_WG*2, BLANK_WG, CYAN_WG*2, BLANK_WG, CYAN_WG, BLANK_WG, PURPLE_WG, BLANK_WG},
            {BLANK_WG, BLANK_WG, PURPLE_WG*2, BLANK_WG, CYAN_WG*2, BLANK_WG, PURPLE_WG},
            {BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG},

    };
};


#endif //OSARRACINO_BLACKEVALUATOR_H
