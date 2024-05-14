#ifndef OSARRACINO_VICKYNGHIWHITEPLAYERPROFILETRAINING_H
#define OSARRACINO_VICKYNGHIWHITEPLAYERPROFILETRAINING_H

#include <evaluator/VickynghiWhiteEvaluatorTraining.h>
#include <movegenerator/HeisenbergMoveGenerator.h>
#include <search/FSMSearchEngine.h>
#include "ParametrizedPlayerProfile.h"

class VickynghiWhitePlayerProfileTraining : public ParametrizedPlayerProfile<
        FSMSearchEngine,
        VickynghiWhiteEvaluatorTraining,
        HeisenbergMoveGenerator>{
public:
    std::string get_profile_name() override {
        return "VickynghiWhitePlayerProfileTraining";
    }
};

#endif //OSARRACINO_VICKYNGHIWHITEPLAYERPROFILETRAINING_H
