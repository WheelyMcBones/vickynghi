#ifndef OSARRACINO_VICKYNGHIWHITEPLAYERPROFILE_H
#define OSARRACINO_VICKYNGHIWHITEPLAYERPROFILE_H


#include <evaluator/TorettoWhiteEvaluator.h>
#include <movegenerator/HeisenbergMoveGenerator.h>
#include <search/FSMSearchEngine.h>
#include "ParametrizedPlayerProfile.h"

class VickynghiWhitePlayerProfile : public ParametrizedPlayerProfile<
        FSMSearchEngine,
        TorettoWhiteEvaluator,
        HeisenbergMoveGenerator>{
public:
    std::string get_profile_name() override {
        return "VickynghiWhitePlayerProfile";
    }
};

#endif //OSARRACINO_VICKYNGHIWHITEPLAYERPROFILE_H
