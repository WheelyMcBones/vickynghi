add_executable (osarracino main.cpp
    GameManager.cpp GameManager.h
    Player.h
    util/ConfigSet.h
    util/MemoryManager.h
    util/MemoryManager.cpp
    util/ArgParser.h
    util/ArgParser.cpp
    profiles/ProfileManager.h
    profiles/ProfileManager.cpp
    profiles/PlayerProfile.h
    profiles/ParametrizedPlayerProfile.h
    profiles/SimpleWhitePlayerProfile.h
    profiles/SimpleBlackPlayerProfile.h
    profiles/FallbackWhitePlayerProfile.h
    profiles/FallbackBlackPlayerProfile.h
    profiles/AggressiveWhitePlayerProfile.h
    profiles/VickynghiBlackPlayerProfile.h
    profiles/VickynghiWhitePlayerProfile.h)

target_link_libraries (osarracino libosarracino)
