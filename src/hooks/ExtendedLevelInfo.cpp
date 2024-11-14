#include <Geode/Geode.hpp>
#include <Geode/modify/FLAlertLayer.hpp>
#include <Geode/modify/InfoLayer.hpp>

using namespace geode::prelude;

GJGameLevel* level;

class ExtendedLevelInfo : public geode::Popup<> {};

class $modify (InfoLayer) {
    bool init(GJGameLevel* p0, GJUserScore* p1, GJLevelList* p2) {
        if (!InfoLayer::init(p0, p1, p2)) return false;

        if (p0) {
            level = p0;
        }

        return true;
    }
};

class $modify (ExtendedLevelInfoExt, FLAlertLayer) {
    virtual void show() {
        FLAlertLayer::show();

        if (auto popup = typeinfo_cast<ExtendedLevelInfo*>(this)) {
            auto useLegacyIcons = Mod::get()->getSettingValue<bool>("legacy-difficulties");
            auto buttonMenu = as<CCMenu*>(popup->getChildByIDRecursive("cvolton.betterinfo/button-menu"));

            CCSprite* difficultySpr = as<CCSprite*>(popup->getChildByIDRecursive("cvolton.betterinfo/difficulty-sprite"));

            log::debug("{}", popup);
            log::debug("{}", difficultySpr);

            switch (level->m_starsRequested) {
                case 4:
                    difficultySpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty04_Legacy.png"_spr : "MD_Difficulty04.png"_spr);
                    difficultySpr->setPositionX(difficultySpr->getPositionX() + 0.5);
                    difficultySpr->setPositionY(difficultySpr->getPositionY() + 0.3);
                    break;
                case 7:
                    difficultySpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty07_Legacy.png"_spr : "MD_Difficulty07.png"_spr);
                    difficultySpr->setPositionX(difficultySpr->getPositionX() + 0.2);
                    difficultySpr->setPositionY(difficultySpr->getPositionY() + 0.3);
                    break;
                case 9:
                    difficultySpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty09_Legacy.png"_spr : "MD_Difficulty09.png"_spr);
                    break;
                default:
                    break;
            }
        }
    }
};