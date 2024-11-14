#include <Geode/Geode.hpp>

#include "./MoreDFSprite.hpp"

/* bool MoreDFSprite::init() {
    return true;
}

MoreDFSprite* MoreDFSprite::createWithStarCount(int starCount, bool smallSpr) {
    auto ret = new MoreDFSprite();

    std::string extraStuff = "";

    if (smallSpr) {
        extraStuff = "Small";
    }

    if (Mod::get()->getSettingValue<bool>("legacy-difficulties")) {
        std::string extraStuffPre = extraStuff;
        extraStuff = fmt::format("{}_Legacy", extraStuffPre);
    }

    std::string spriteName = fmt::format("uproxide.more_difficulties/MD_Difficulty0{}{}.png", starCount, extraStuff);
    log::info("{}", spriteName);

    if (ret && ret->initWithSpriteFrameName(spriteName.c_str()) && ret->init()) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}; */