#pragma once
#include <Geode/Geode.hpp>
using namespace geode::prelude;

class MoreDFSprite : public CCSprite {
    public:
        bool init();
        static MoreDFSprite* createWithStarCount(int starCount, bool smallSpr);
        static MoreDFSprite* createWithName(std::string name, bool smallSpr);
        static MoreDFSprite* createWithLevelID(int levelID, std::string name, bool smallSpr);
};