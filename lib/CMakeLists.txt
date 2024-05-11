find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES} pthread)


add_library(libosarracino STATIC
        util/BitUtils.h util/BoardUtils.cpp util/BoardUtils.h
        network/Connector.cpp network/Connector.h

        model/Board.cpp model/Board.h
        model/Position.cpp model/Position.h
        model/DTranspositionTable.cpp model/DTranspositionTable.h
        model/ZobristHash.cpp model/ZobristHash.h

        evaluator/Evaluator.h

        evaluator/TorettoWhiteEvaluator.cpp evaluator/TorettoWhiteEvaluator.h
        evaluator/TheRockWhiteEvaluator.cpp evaluator/TheRockWhiteEvaluator.h
        evaluator/VickynghiWhiteEvaluator.cpp evaluator/VickynghiWhiteEvaluator.h

        evaluator/BlackEvaluator.cpp evaluator/BlackEvaluator.h
        evaluator/ReverseTorettoBlackEvaluator.cpp evaluator/ReverseTorettoBlackEvaluator.h
        evaluator/VickynghiBlackEvaluator.cpp evaluator/VickynghiBlackEvaluator.h
        evaluator/VickynghiBlackEvaluatorTraining.cpp evaluator/VickynghiBlackEvaluatorTraining.h

        movegenerator/MoveGenerator.h
        movegenerator/ThetaMoveGenerator.cpp movegenerator/ThetaMoveGenerator.h
        movegenerator/ArnoldMoveGenerator.cpp movegenerator/ArnoldMoveGenerator.h
        movegenerator/HeisenbergMoveGenerator.cpp movegenerator/HeisenbergMoveGenerator.h

        search/SearchEngine.h search/RamboSearchEngine.h util/Timer.h
        search/CollisionSearchEngine.h search/CarloSearchEngine.h
        search/ThanosSearchEngine.h
        search/FSMSearchEngine.h)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
if(APPLE)
        add_compile_options("-I/usr/local/Cellar/jsoncpp/1.9.5/include")
        add_compile_options("-L/usr/local/Cellar/jsoncpp/1.9.5/lib")
        add_compile_options("-ljsoncpp")
endif()


set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native")
target_link_libraries(libosarracino "-I/usr/local/Cellar/jsoncpp/1.9.5/include" "-L/usr/local/Cellar/jsoncpp/1.9.5/lib" jsoncpp pthread)

target_include_directories (libosarracino PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
