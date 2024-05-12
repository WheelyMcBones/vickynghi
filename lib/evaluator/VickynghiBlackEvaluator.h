//
// Created by freddy on 15/04/19.
//

#ifndef OSARRACINO_VICKYNGHIBLACKEVALUATOR_H
#define OSARRACINO_VICKYNGHIBLACKEVALUATOR_H

#include "Evaluator.h"
#include <vector>
#include <tuple>
#include <array>
#include <unordered_map>
#include <functional>


class VickynghiBlackEvaluator : public Evaluator<VickynghiBlackEvaluator> {
private:
    enum Direction {
        Up = 1, Down = 2, Right = 3, Left = 4, None = false
    };
    const std::array<int, 4> win_rows_cols = {1, 2, 6, 7};

public:
    std::string get_name() const {
        return "VickynghiBlackEvaluator";
    }

    VickynghiBlackEvaluator();
    int evaluate(const Board &b) const;
    int black_block_king(const Board &b) const;
    int pawn_differences(const Board &b) const;
    int geometry_points(const Board &b) const;
    int get_empty_row_down(const Board &b) const;
    int get_number_empty_factor(const Board &b) const;
    int get_number_empty_col(const Board &b) const;
    int get_empty_row_up(const Board &b) const;
    int get_empty_col_right(const Board &b) const;
    int get_empty_col_left(const Board &b) const;
    int avoid_same_row_or_col(const Board &b) const;
    int is_in_corner(const Board &b) const;
    int black_superiority(const Board &b) const;
    std::vector <Direction> get_direction_of_move_check(const Board &b) const;
    std::function<int(const Board &b, const int8_t (&matrix)[9][9])> geometry_calculator;
    int apply_no_transit_zone(const Board &b) const;
    std::vector<int> no_transit_zone(const Board &b) const;

//     HUMAN 
//     static const uint8_t BLANK_WG = 0;
//     static const uint8_t BLANK_HW = 10; // Hot area
//     static const uint8_t BLANK_MW = 5; // Mild area
//     static const int8_t BLANK_CW = -1; // Cold area
//     static const int8_t PENALTY_FACTOR = -7;
//     static const uint8_t CYAN_WG = 1;
//     static const uint8_t PURPLE_WG = 0;
//     static const uint8_t YELLOW_WG = 1;
//     static const int STRONG_MULT = 40;
//     static const int LIGHT_MULT = 20;
//     static const int EZPZ = 200000;
//     static const int PREVENT_CHECKMATE = -1000;

//     GALGO 
    static const uint8_t BLANK_WG = 0;
    static const uint8_t BLANK_HW = 2; // Hot area
    static const uint8_t BLANK_MW = 11; // Mild area
    static const int8_t BLANK_CW = -8; // Cold area
    static const int8_t PENALTY_FACTOR = -20;
    static const uint8_t CYAN_WG = 1;
    static const uint8_t PURPLE_WG = 0;
    static const uint8_t YELLOW_WG = 1;
    static const int STRONG_MULT = 49;
    static const int LIGHT_MULT = 1;
    static const int EZPZ = 200000;
    static const int PREVENT_CHECKMATE = -EZPZ;

    static const int PENALTY_NO_TRANSIT_ZONE = -25;


    int8_t color_matrix[9][9] = {
            {BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG},
            {BLANK_WG, BLANK_WG,  PURPLE_WG, BLANK_WG, CYAN_WG, BLANK_WG, PURPLE_WG},
            {BLANK_WG, PURPLE_WG, BLANK_WG, CYAN_WG * STRONG_MULT, BLANK_WG, CYAN_WG * STRONG_MULT, BLANK_WG, PURPLE_WG, BLANK_WG },
            {BLANK_WG, BLANK_WG, CYAN_WG * STRONG_MULT, BLANK_WG, BLANK_WG, BLANK_WG, CYAN_WG * STRONG_MULT, BLANK_WG, BLANK_WG},
            {BLANK_WG, CYAN_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, CYAN_WG, BLANK_WG},
            {BLANK_WG, BLANK_WG, CYAN_WG * STRONG_MULT, BLANK_WG, BLANK_WG, BLANK_WG, CYAN_WG * STRONG_MULT, BLANK_WG, BLANK_WG},
            {BLANK_WG, PURPLE_WG, BLANK_WG, CYAN_WG * STRONG_MULT, BLANK_WG, CYAN_WG * STRONG_MULT, BLANK_WG, PURPLE_WG, BLANK_WG},
            {BLANK_WG, BLANK_WG, PURPLE_WG, BLANK_WG, CYAN_WG, BLANK_WG, PURPLE_WG},
            {BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG},

    };

    int8_t top_color_matrix[9][9] = {
            {BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW},
            {BLANK_MW, BLANK_MW, PURPLE_WG, BLANK_MW, CYAN_WG*STRONG_MULT, BLANK_MW, PURPLE_WG},
            {BLANK_MW, PURPLE_WG, BLANK_MW, CYAN_WG*STRONG_MULT, BLANK_MW, CYAN_WG*STRONG_MULT, BLANK_MW, PURPLE_WG, BLANK_MW },
            {BLANK_MW, BLANK_MW, CYAN_WG*STRONG_MULT, BLANK_MW, BLANK_MW, BLANK_MW, STRONG_MULT*CYAN_WG, BLANK_MW, BLANK_MW},
            {BLANK_CW, CYAN_WG*STRONG_MULT, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, STRONG_MULT*CYAN_WG, BLANK_CW},
            {BLANK_CW, BLANK_CW, CYAN_WG, BLANK_CW, BLANK_CW, BLANK_CW, CYAN_WG, BLANK_CW, BLANK_CW},
            {BLANK_CW, PURPLE_WG, BLANK_CW, CYAN_WG, BLANK_CW, CYAN_WG, BLANK_CW, PURPLE_WG, BLANK_CW},
            {BLANK_CW, BLANK_CW, PURPLE_WG, BLANK_CW, CYAN_WG, BLANK_CW, PURPLE_WG},
            {BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW},

    };
    int8_t bottom_color_matrix[9][9] = {
            {BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW},
            {BLANK_CW, BLANK_CW, PURPLE_WG, BLANK_CW, CYAN_WG, BLANK_CW, PURPLE_WG, BLANK_CW, BLANK_CW},
            {BLANK_CW, PURPLE_WG, BLANK_CW, CYAN_WG, BLANK_CW, CYAN_WG, BLANK_CW, PURPLE_WG, BLANK_CW },
            {BLANK_CW, BLANK_CW, CYAN_WG, BLANK_CW, BLANK_CW, BLANK_CW, CYAN_WG, BLANK_CW, BLANK_CW},
            {BLANK_CW, CYAN_WG*STRONG_MULT, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, STRONG_MULT*CYAN_WG, BLANK_CW},
            {BLANK_MW, BLANK_MW, CYAN_WG*STRONG_MULT, BLANK_MW, BLANK_MW, BLANK_MW, STRONG_MULT*CYAN_WG, BLANK_MW, BLANK_MW},
            {BLANK_MW, PURPLE_WG, BLANK_MW, STRONG_MULT*CYAN_WG, BLANK_MW, STRONG_MULT*CYAN_WG, BLANK_MW, PURPLE_WG, BLANK_MW},
            {BLANK_MW, BLANK_MW, PURPLE_WG, BLANK_MW, STRONG_MULT*CYAN_WG, BLANK_MW, PURPLE_WG, BLANK_MW, BLANK_MW},
            {BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW},
    };
    int8_t right_color_matrix[9][9] = {
            {BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW},
            {BLANK_CW, BLANK_CW, PURPLE_WG, BLANK_CW, STRONG_MULT*CYAN_WG, BLANK_MW, PURPLE_WG},
            {BLANK_CW, PURPLE_WG, BLANK_CW, CYAN_WG, BLANK_CW, STRONG_MULT*CYAN_WG, BLANK_MW, PURPLE_WG, BLANK_MW },
            {BLANK_CW, BLANK_CW, CYAN_WG, BLANK_CW, BLANK_CW, BLANK_MW, STRONG_MULT*CYAN_WG, BLANK_MW, BLANK_MW},
            {BLANK_CW, CYAN_WG, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_MW, BLANK_MW, STRONG_MULT*CYAN_WG, BLANK_MW},
            {BLANK_CW, BLANK_CW, CYAN_WG, BLANK_CW, BLANK_CW, BLANK_MW, STRONG_MULT*CYAN_WG, BLANK_MW, BLANK_MW},
            {BLANK_CW, PURPLE_WG, BLANK_CW, CYAN_WG, BLANK_CW, STRONG_MULT*CYAN_WG, BLANK_MW, PURPLE_WG, BLANK_MW},
            {BLANK_CW, BLANK_CW, PURPLE_WG, BLANK_CW, STRONG_MULT*CYAN_WG, BLANK_MW, PURPLE_WG},
            {BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW},

    };
    int8_t left_color_matrix[9][9] = {
            {BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW},
            {BLANK_MW, BLANK_MW, PURPLE_WG, BLANK_MW, STRONG_MULT*CYAN_WG, BLANK_CW, PURPLE_WG},
            {BLANK_MW, PURPLE_WG, BLANK_MW, STRONG_MULT*CYAN_WG, BLANK_CW, CYAN_WG, BLANK_CW, PURPLE_WG, BLANK_CW },
            {BLANK_MW, BLANK_MW, STRONG_MULT*CYAN_WG, BLANK_CW, BLANK_CW, BLANK_CW, CYAN_WG, BLANK_CW, BLANK_CW},
            {BLANK_MW, STRONG_MULT*CYAN_WG, BLANK_MW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, CYAN_WG, BLANK_CW},
            {BLANK_MW, BLANK_MW, STRONG_MULT*CYAN_WG, BLANK_CW, BLANK_CW, BLANK_CW, CYAN_WG, BLANK_CW, BLANK_CW},
            {BLANK_MW, PURPLE_WG, BLANK_MW, STRONG_MULT*CYAN_WG, BLANK_CW, CYAN_WG, BLANK_CW, PURPLE_WG, BLANK_CW},
            {BLANK_MW, BLANK_MW, PURPLE_WG, BLANK_MW, STRONG_MULT*CYAN_WG, BLANK_CW, PURPLE_WG},
            {BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW},

    };

    int8_t top_right_color_matrix[9][9] = {
            {BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_HW, BLANK_HW, BLANK_HW, BLANK_HW},
            {BLANK_MW, BLANK_MW, PURPLE_WG, BLANK_MW, CYAN_WG*STRONG_MULT, BLANK_HW, PURPLE_WG},
            {BLANK_MW, PURPLE_WG, BLANK_MW, CYAN_WG, BLANK_MW, STRONG_MULT*CYAN_WG, BLANK_HW, PURPLE_WG, BLANK_HW },
            {BLANK_MW, BLANK_MW, CYAN_WG, BLANK_MW, BLANK_MW, BLANK_HW, STRONG_MULT*CYAN_WG, BLANK_HW, BLANK_HW},
            {BLANK_CW, CYAN_WG, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_MW, BLANK_MW, STRONG_MULT*CYAN_WG, BLANK_MW},
            {BLANK_CW, BLANK_CW, CYAN_WG, BLANK_CW, BLANK_CW, BLANK_MW, CYAN_WG, BLANK_MW, BLANK_MW},
            {BLANK_CW, PURPLE_WG, BLANK_CW, CYAN_WG, BLANK_CW, CYAN_WG, BLANK_MW, PURPLE_WG, BLANK_MW},
            {BLANK_CW, BLANK_CW, PURPLE_WG, BLANK_CW, CYAN_WG, BLANK_MW, PURPLE_WG},
            {BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW},

    };
    int8_t top_left_color_matrix[9][9] = {
            {BLANK_HW, BLANK_HW, BLANK_HW, BLANK_HW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW},
            {BLANK_HW, BLANK_HW, PURPLE_WG, BLANK_HW, CYAN_WG*STRONG_MULT, BLANK_MW, PURPLE_WG},
            {BLANK_HW, PURPLE_WG, BLANK_HW, CYAN_WG*STRONG_MULT, BLANK_MW, CYAN_WG, BLANK_MW, PURPLE_WG, BLANK_MW },
            {BLANK_HW, BLANK_HW, CYAN_WG*STRONG_MULT, BLANK_CW, BLANK_CW, BLANK_CW, CYAN_WG, BLANK_CW, BLANK_CW},
            {BLANK_MW, CYAN_WG*STRONG_MULT, BLANK_MW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, CYAN_WG, BLANK_CW},
            {BLANK_MW, BLANK_MW, CYAN_WG, BLANK_MW, BLANK_CW, BLANK_CW, CYAN_WG, BLANK_CW, BLANK_CW},
            {BLANK_MW, PURPLE_WG, BLANK_MW, CYAN_WG, BLANK_CW, CYAN_WG, BLANK_CW, PURPLE_WG, BLANK_CW},
            {BLANK_MW, BLANK_MW, PURPLE_WG, BLANK_MW, CYAN_WG, BLANK_CW, PURPLE_WG},
            {BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW},

    };
    int8_t bottom_right_color_matrix[9][9] = {
            {BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW},
            {BLANK_CW, BLANK_CW, PURPLE_WG, BLANK_CW, CYAN_WG, BLANK_MW, PURPLE_WG},
            {BLANK_CW, PURPLE_WG, BLANK_CW, CYAN_WG, BLANK_CW, CYAN_WG, BLANK_MW, PURPLE_WG, BLANK_MW },
            {BLANK_CW, BLANK_CW, CYAN_WG, BLANK_CW, BLANK_CW, BLANK_MW, CYAN_WG, BLANK_MW, BLANK_MW},
            {BLANK_CW, CYAN_WG, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_MW, BLANK_MW, STRONG_MULT*CYAN_WG, BLANK_MW},
            {BLANK_MW, BLANK_MW, CYAN_WG, BLANK_MW, BLANK_MW, BLANK_HW, CYAN_WG*STRONG_MULT, BLANK_HW, BLANK_HW},
            {BLANK_MW, PURPLE_WG, BLANK_MW, CYAN_WG, BLANK_MW, CYAN_WG*STRONG_MULT, BLANK_HW, PURPLE_WG, BLANK_HW},
            {BLANK_MW, BLANK_MW, PURPLE_WG, BLANK_MW, CYAN_WG*STRONG_MULT, BLANK_HW, PURPLE_WG},
            {BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_HW, BLANK_HW, BLANK_HW, BLANK_HW},

    };
    int8_t bottom_left_color_matrix[9][9] = {
            {BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW},
            {BLANK_MW, BLANK_MW, PURPLE_WG, BLANK_MW, CYAN_WG, BLANK_CW, PURPLE_WG},
            {BLANK_MW, PURPLE_WG, BLANK_MW, CYAN_WG, BLANK_CW, CYAN_WG, BLANK_CW, PURPLE_WG, BLANK_CW },
            {BLANK_MW, BLANK_MW, CYAN_WG, BLANK_MW, BLANK_CW, BLANK_CW, CYAN_WG, BLANK_CW, BLANK_CW},
            {BLANK_MW, CYAN_WG*STRONG_MULT, BLANK_MW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, CYAN_WG, BLANK_CW},
            {BLANK_HW, BLANK_HW, CYAN_WG*STRONG_MULT, BLANK_MW, BLANK_MW, BLANK_MW, CYAN_WG, BLANK_MW, BLANK_MW},
            {BLANK_HW, PURPLE_WG, BLANK_HW, CYAN_WG*STRONG_MULT, BLANK_MW, CYAN_WG, BLANK_MW, PURPLE_WG, BLANK_MW},
            {BLANK_HW, BLANK_HW, PURPLE_WG, BLANK_HW, CYAN_WG*STRONG_MULT, BLANK_MW, PURPLE_WG},
            {BLANK_HW, BLANK_HW, BLANK_HW, BLANK_HW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW},

    };

    int8_t larger_diagonal_color_matrix[9][9] = {
            {BLANK_WG, BLANK_WG, BLANK_WG, YELLOW_WG, BLANK_WG, YELLOW_WG, BLANK_WG, BLANK_WG, BLANK_WG},
            {BLANK_WG, BLANK_WG, YELLOW_WG, BLANK_WG, BLANK_WG, BLANK_WG, YELLOW_WG, BLANK_WG, BLANK_WG,},
            {BLANK_WG, YELLOW_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, YELLOW_WG, BLANK_WG },
            {YELLOW_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, YELLOW_WG},
            {BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG},
            {YELLOW_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, YELLOW_WG},
            {BLANK_WG, YELLOW_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, BLANK_WG, YELLOW_WG, BLANK_WG},
            {BLANK_WG, BLANK_WG, YELLOW_WG, BLANK_WG, BLANK_WG, BLANK_WG, YELLOW_WG, BLANK_WG, BLANK_WG},
            {BLANK_WG, BLANK_WG, BLANK_WG, YELLOW_WG, BLANK_WG, YELLOW_WG, BLANK_WG, BLANK_WG, BLANK_WG},

    };

    int8_t bottom_left_larger_diagonal_color_matrix[9][9] = {
            {BLANK_MW, BLANK_MW, BLANK_MW, YELLOW_WG, BLANK_CW, YELLOW_WG, BLANK_CW, BLANK_CW, BLANK_CW},
            {BLANK_MW, BLANK_MW, YELLOW_WG, BLANK_MW, BLANK_CW, BLANK_CW, YELLOW_WG, BLANK_CW, BLANK_CW,},
            {BLANK_MW, YELLOW_WG, BLANK_MW, BLANK_MW, BLANK_CW, BLANK_CW, BLANK_CW, YELLOW_WG, BLANK_CW },
            {YELLOW_WG, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, YELLOW_WG},
            {BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW},
            {YELLOW_WG*LIGHT_MULT, BLANK_HW, BLANK_HW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, YELLOW_WG},
            {BLANK_HW, YELLOW_WG*LIGHT_MULT, BLANK_HW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, YELLOW_WG, BLANK_MW},
            {BLANK_HW, BLANK_HW, YELLOW_WG*LIGHT_MULT, BLANK_MW, BLANK_MW, BLANK_MW, YELLOW_WG, BLANK_MW, BLANK_MW},
            {BLANK_HW, BLANK_HW, BLANK_HW, YELLOW_WG*LIGHT_MULT, BLANK_MW, YELLOW_WG, BLANK_MW, BLANK_MW, BLANK_MW},

    };

    int8_t bottom_right_larger_diagonal_color_matrix[9][9] = {
            {BLANK_CW, BLANK_CW, BLANK_CW, YELLOW_WG, BLANK_CW, YELLOW_WG, BLANK_MW, BLANK_MW, BLANK_MW},
            {BLANK_CW, BLANK_CW, YELLOW_WG, BLANK_CW, BLANK_CW, BLANK_MW, YELLOW_WG, BLANK_MW, BLANK_MW,},
            {BLANK_CW, YELLOW_WG, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_MW, BLANK_MW, YELLOW_WG, BLANK_MW },
            {YELLOW_WG, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_MW, BLANK_MW, BLANK_MW, YELLOW_WG},
            {BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW},
            {YELLOW_WG, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_MW, BLANK_MW, BLANK_MW, YELLOW_WG*LIGHT_MULT},
            {BLANK_MW, YELLOW_WG, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_HW, BLANK_HW, YELLOW_WG*LIGHT_MULT, BLANK_HW},
            {BLANK_MW, BLANK_MW, YELLOW_WG, BLANK_MW, BLANK_MW, BLANK_HW, YELLOW_WG*LIGHT_MULT, BLANK_HW, BLANK_HW},
            {BLANK_MW, BLANK_MW, BLANK_MW, YELLOW_WG, BLANK_MW, YELLOW_WG*LIGHT_MULT, BLANK_HW, BLANK_HW, BLANK_HW},

    };

    int8_t top_left_larger_diagonal_color_matrix[9][9] = {
            {BLANK_HW, BLANK_HW, BLANK_HW,BLANK_HW + YELLOW_WG*LIGHT_MULT, BLANK_MW, BLANK_MW+YELLOW_WG, BLANK_MW, BLANK_MW, BLANK_MW},
            {BLANK_HW, BLANK_HW, BLANK_HW+YELLOW_WG*LIGHT_MULT, BLANK_HW, BLANK_MW, BLANK_MW, BLANK_MW+YELLOW_WG, BLANK_MW, BLANK_MW,},
            {BLANK_HW, BLANK_HW+YELLOW_WG*LIGHT_MULT, BLANK_HW, BLANK_HW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW+YELLOW_WG, BLANK_MW },
            {BLANK_HW+YELLOW_WG*LIGHT_MULT, BLANK_HW, BLANK_HW, BLANK_MW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_MW+YELLOW_WG},
            {BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW},
            {BLANK_MW+YELLOW_WG, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW+YELLOW_WG},
            {BLANK_MW, BLANK_MW+YELLOW_WG, BLANK_MW, BLANK_MW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW+YELLOW_WG, BLANK_CW},
            {BLANK_MW, BLANK_MW, BLANK_MW+YELLOW_WG, BLANK_MW, BLANK_CW, BLANK_CW, BLANK_CW+YELLOW_WG, BLANK_CW, BLANK_CW},
            {BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW+YELLOW_WG, BLANK_CW, BLANK_CW+YELLOW_WG, BLANK_CW, BLANK_CW, BLANK_CW},
    };

    int8_t top_right_larger_diagonal_color_matrix[9][9] = {
            {BLANK_MW, BLANK_MW, BLANK_MW, YELLOW_WG, BLANK_MW, YELLOW_WG*LIGHT_MULT, BLANK_HW, BLANK_HW, BLANK_HW},
            {BLANK_MW, BLANK_MW, YELLOW_WG, BLANK_MW, BLANK_MW, BLANK_HW, YELLOW_WG*LIGHT_MULT, BLANK_HW, BLANK_HW,},
            {BLANK_MW, YELLOW_WG, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_HW, BLANK_HW, YELLOW_WG*LIGHT_MULT, BLANK_HW },
            {YELLOW_WG, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, YELLOW_WG*LIGHT_MULT},
            {BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW},
            {YELLOW_WG, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_MW, BLANK_MW, BLANK_MW, YELLOW_WG},
            {BLANK_CW, YELLOW_WG, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_MW, BLANK_MW, YELLOW_WG, BLANK_MW},
            {BLANK_CW, BLANK_CW, YELLOW_WG, BLANK_CW, BLANK_CW, BLANK_MW, YELLOW_WG, BLANK_MW, BLANK_MW},
            {BLANK_CW, BLANK_CW, BLANK_CW, YELLOW_WG, BLANK_CW, YELLOW_WG, BLANK_MW, BLANK_MW, BLANK_MW},

    };

    int8_t right_larger_diagonal_color_matrix[9][9] = {
            {BLANK_CW, BLANK_CW, BLANK_CW, YELLOW_WG, BLANK_CW, YELLOW_WG*LIGHT_MULT, BLANK_MW, BLANK_MW, BLANK_MW},
            {BLANK_CW, BLANK_CW, YELLOW_WG, BLANK_CW, BLANK_MW, BLANK_MW, YELLOW_WG*LIGHT_MULT, BLANK_MW, BLANK_MW,},
            {BLANK_CW, YELLOW_WG, BLANK_CW, BLANK_CW, BLANK_MW, BLANK_MW, BLANK_MW, YELLOW_WG*LIGHT_MULT, BLANK_MW },
            {YELLOW_WG, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, YELLOW_WG*LIGHT_MULT},
            {BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW},
            {YELLOW_WG, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, YELLOW_WG*LIGHT_MULT},
            {BLANK_CW, YELLOW_WG, BLANK_CW, BLANK_CW, BLANK_MW, BLANK_MW, BLANK_MW, YELLOW_WG*LIGHT_MULT, BLANK_MW},
            {BLANK_CW, BLANK_CW, YELLOW_WG, BLANK_CW, BLANK_MW, BLANK_MW, YELLOW_WG*LIGHT_MULT, BLANK_MW, BLANK_MW},
            {BLANK_CW, BLANK_CW, BLANK_CW, YELLOW_WG, BLANK_CW, YELLOW_WG*LIGHT_MULT, BLANK_MW, BLANK_MW, BLANK_MW},

    };

    int8_t left_larger_diagonal_color_matrix[9][9] = {
            {BLANK_MW, BLANK_MW, BLANK_MW, YELLOW_WG*LIGHT_MULT, BLANK_CW, YELLOW_WG, BLANK_CW, BLANK_CW, BLANK_CW},
            {BLANK_MW, BLANK_MW, YELLOW_WG*LIGHT_MULT, BLANK_MW, BLANK_MW, BLANK_CW, YELLOW_WG, BLANK_CW, BLANK_CW,},
            {BLANK_MW, YELLOW_WG*LIGHT_MULT, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_CW, BLANK_CW, YELLOW_WG, BLANK_CW },
            {YELLOW_WG*LIGHT_MULT, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_CW, BLANK_CW, BLANK_CW, YELLOW_WG},
            {BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW},
            {YELLOW_WG*LIGHT_MULT, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_CW, BLANK_CW, BLANK_CW, YELLOW_WG},
            {BLANK_MW, YELLOW_WG*LIGHT_MULT, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_CW, BLANK_CW, YELLOW_WG, BLANK_CW},
            {BLANK_MW, BLANK_MW, YELLOW_WG*LIGHT_MULT, BLANK_MW, BLANK_MW, BLANK_CW, YELLOW_WG, BLANK_CW, BLANK_CW},
            {BLANK_MW, BLANK_MW, BLANK_MW, YELLOW_WG*LIGHT_MULT, BLANK_CW, YELLOW_WG, BLANK_CW, BLANK_CW, BLANK_CW},
    };


    int8_t top_larger_diagonal_color_matrix[9][9] = {
        {BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW+YELLOW_WG*LIGHT_MULT, BLANK_MW, BLANK_MW+YELLOW_WG*LIGHT_MULT, BLANK_MW, BLANK_MW, BLANK_MW},
        {BLANK_MW, BLANK_MW, BLANK_MW+YELLOW_WG*LIGHT_MULT, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW+YELLOW_WG*LIGHT_MULT, BLANK_MW, BLANK_MW,},
        {BLANK_MW, BLANK_MW+YELLOW_WG*LIGHT_MULT, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW+YELLOW_WG*LIGHT_MULT, BLANK_MW },
        {BLANK_MW+YELLOW_WG*LIGHT_MULT, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_MW+YELLOW_WG*LIGHT_MULT},
        {BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW},
        {BLANK_CW+YELLOW_WG, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW+YELLOW_WG},
        {BLANK_CW, BLANK_CW+YELLOW_WG, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW+YELLOW_WG, BLANK_CW},
        {BLANK_CW, BLANK_CW, BLANK_CW+YELLOW_WG, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW+YELLOW_WG, BLANK_CW, BLANK_CW},
        {BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW+YELLOW_WG, BLANK_CW, BLANK_CW+YELLOW_WG, BLANK_CW, BLANK_CW, BLANK_CW},
        };

    int8_t bottom_larger_diagonal_color_matrix[9][9] = {
            {BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW+YELLOW_WG, BLANK_CW, BLANK_CW+YELLOW_WG, BLANK_CW, BLANK_CW, BLANK_CW},
            {BLANK_CW, BLANK_CW, BLANK_CW+YELLOW_WG, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW+YELLOW_WG, BLANK_CW, BLANK_CW,},
            {BLANK_CW, BLANK_CW+YELLOW_WG, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW+YELLOW_WG, BLANK_CW },
            {BLANK_CW+YELLOW_WG, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW+YELLOW_WG},
            {BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW, BLANK_CW},
            {BLANK_MW+YELLOW_WG*LIGHT_MULT, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW+YELLOW_WG*LIGHT_MULT},
            {BLANK_MW, BLANK_MW+YELLOW_WG*LIGHT_MULT, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW+YELLOW_WG*LIGHT_MULT, BLANK_MW},
            {BLANK_MW, BLANK_MW, BLANK_MW+YELLOW_WG*LIGHT_MULT, BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW+YELLOW_WG*LIGHT_MULT, BLANK_MW, BLANK_MW},
            {BLANK_MW, BLANK_MW, BLANK_MW, BLANK_MW+YELLOW_WG*LIGHT_MULT, BLANK_MW, BLANK_MW+YELLOW_WG*LIGHT_MULT, BLANK_MW, BLANK_MW, BLANK_MW},
    };


    int8_t top_right_transit_red_matrix[9][9] = {
//       0  1  2  3  4  5  6  7  8
            {0, 0, 0, 0, 0, 0, 1, 1, 1}, // 0
            {0, 0, 0, 0, 0, 1, 1, 1, 1}, // 1
            {0, 0, 0, 0, 0, 0, 1, 1, 1}, // 2
            {0, 0, 0, 0, 0, 0, 0, 1, 0}, // 3
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 4
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 5
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 6
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 7
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 8
    };
    int8_t top_right_transit_orange_matrix[9][9] = {
//       0  1  2  3  4  5  6  7  8
            {0, 0, 0, 0, 0, 0, 1, 1, 1}, // 0
            {0, 0, 0, 0, 0, 0, 1, 1, 1}, // 1
            {0, 0, 0, 0, 0, 0, 0, 1, 1}, // 2
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 3
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 4
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 5
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 6
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 7
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 8
    };
    int8_t top_right_transit_yellow_matrix[9][9] = {
//       0  1  2  3  4  5  6  7  8
            {0, 0, 0, 0, 0, 0, 1, 1, 1}, // 0
            {0, 0, 0, 0, 0, 0, 0, 1, 1}, // 1
            {0, 0, 0, 0, 0, 0, 0, 0, 1}, // 2
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 3
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 4
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 5
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 6
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 7
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 8
    };


    int8_t top_left_transit_red_matrix[9][9] = {
//       0  1  2  3  4  5  6  7  8
            {1, 1, 1, 0, 0, 0, 0, 0, 0}, // 0
            {1, 1, 1, 1, 0, 0, 0, 0, 0}, // 1
            {1, 1, 1, 0, 0, 0, 0, 0, 0}, // 2
            {0, 1, 0, 0, 0, 0, 0, 0, 0}, // 3
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 4
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 5
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 6
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 7
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 8
    };

    int8_t top_left_transit_orange_matrix[9][9] = {
//       0  1  2  3  4  5  6  7  8
            {1, 1, 1, 0, 0, 0, 0, 0, 0}, // 0
            {1, 1, 1, 0, 0, 0, 0, 0, 0}, // 1
            {1, 1, 0, 0, 0, 0, 0, 0, 0}, // 2
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 3
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 4
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 5
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 6
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 7
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 8
    };
    int8_t top_left_transit_yellow_matrix[9][9] = {
//       0  1  2  3  4  5  6  7  8
            {1, 1, 1, 0, 0, 0, 0, 0, 0}, // 0
            {1, 1, 0, 0, 0, 0, 0, 0, 0}, // 1
            {1, 0, 0, 0, 0, 0, 0, 0, 0}, // 2
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 3
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 4
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 5
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 6
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 7
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 8
    };

    int8_t bottom_right_transit_red_matrix[9][9] = {
//       0  1  2  3  4  5  6  7  8
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 0
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 1
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 2
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 3
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 4
            {0, 0, 0, 0, 0, 0, 0, 1, 0}, // 5
            {0, 0, 0, 0, 0, 0, 1, 1, 1}, // 6
            {0, 0, 0, 0, 0, 1, 1, 1, 1}, // 7
            {0, 0, 0, 0, 0, 0, 1, 1, 1}, // 8
    };

    int8_t bottom_right_transit_orange_matrix[9][9] = {
//       0  1  2  3  4  5  6  7  8
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 0
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 1
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 2
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 3
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 4
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 5
            {0, 0, 0, 0, 0, 0, 0, 1, 1}, // 6
            {0, 0, 0, 0, 0, 0, 1, 1, 1}, // 7
            {0, 0, 0, 0, 0, 0, 1, 1, 1}, // 8
    };
    int8_t bottom_right_transit_yellow_matrix[9][9] = {
//       0  1  2  3  4  5  6  7  8
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 0
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 1
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 2
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 3
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 4
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 5
            {0, 0, 0, 0, 0, 0, 0, 0, 1}, // 6
            {0, 0, 0, 0, 0, 0, 0, 1, 1}, // 7
            {0, 0, 0, 0, 0, 0, 1, 1, 1}, // 8
    };


    int8_t bottom_left_transit_red_matrix[9][9] = {
//       0  1  2  3  4  5  6  7  8
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 0
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 1
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 2
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 3
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 4
            {0, 1, 0, 0, 0, 0, 0, 0, 0}, // 5
            {1, 1, 1, 0, 0, 0, 0, 0, 0}, // 6
            {1, 1, 1, 1, 0, 0, 0, 0, 0}, // 7
            {1, 1, 1, 0, 0, 0, 0, 0, 0}, // 8
    };

    int8_t bottom_left_transit_orange_matrix[9][9] = {
//       0  1  2  3  4  5  6  7  8
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 0
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 1
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 2
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 3
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 4
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 5
            {1, 1, 0, 0, 0, 0, 0, 0, 0}, // 6
            {1, 1, 1, 0, 0, 0, 0, 0, 0}, // 7
            {1, 1, 1, 0, 0, 0, 0, 0, 0}, // 8
    };
    int8_t bottom_left_transit_yellow_matrix[9][9] = {
//       0  1  2  3  4  5  6  7  8
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 0
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 1
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 2
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 3
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 4
            {0, 0, 0, 0, 0, 0, 0, 0, 0}, // 5
            {1, 0, 0, 0, 0, 0, 0, 0, 0}, // 6
            {1, 1, 0, 0, 0, 0, 0, 0, 0}, // 7
            {1, 1, 1, 0, 0, 0, 0, 0, 0}, // 8

    };
};


#endif // OSARRACINO_VICKYNGHIBLACKEVALUATOR_H
