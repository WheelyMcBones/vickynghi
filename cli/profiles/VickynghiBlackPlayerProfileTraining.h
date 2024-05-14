#ifndef OSARRACINO_VICKYNGHIBLACKPLAYERTRAININGPROFILE_H
#define OSARRACINO_VICKYNGHIBLACKPLAYERTRAININGPROFILE_H

#include <evaluator/VickynghiBlackEvaluatorTraining.h>
#include <evaluator/VickynghiBlackEvaluator.h>
#include <movegenerator/HeisenbergMoveGenerator.h>
#include <search/FSMSearchEngine.h>
#include "ParametrizedPlayerProfile.h"

class VickynghiBlackPlayerProfileTraining : public ParametrizedPlayerProfile<
        FSMSearchEngine,
        VickynghiBlackEvaluatorTraining,
        HeisenbergMoveGenerator>{
public:
    std::string get_profile_name() override {
        return "VickynghiBlackPlayerProfileTraining";
    }
};

#endif // OSARRACINO_VICKYNGHIBLACKPLAYERTRAININGPROFILE_H
