#ifndef OSARRACINO_VICKYNGHIBLACKPLAYERPROFILE_H
#define OSARRACINO_VICKYNGHIBLACKPLAYERPROFILE_H

#include <evaluator/VickynghiBlackEvaluator.h>
#include <movegenerator/HeisenbergMoveGenerator.h>
#include <search/FSMSearchEngine.h>
#include "ParametrizedPlayerProfile.h"

class VickynghiBlackPlayerProfile : public ParametrizedPlayerProfile<
        FSMSearchEngine,
        VickynghiBlackEvaluator,
        HeisenbergMoveGenerator>{
public:
    std::string get_profile_name() override {
        return "VickynghiBlackPlayerProfile";
    }
};

#endif // OSARRACINO_VICKYNGHIBLACKPLAYERPROFILE_H
