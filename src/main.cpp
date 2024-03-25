#include <Geode/modify/GJDifficultySprite.hpp>
#include <fmt/format.h>

using namespace geode::prelude;

class $modify(GJDifficultySprite) {
    void updateFeatureStateFromLevel(GJGameLevel* level) {
        updateCustomDifficultyFrame(level->m_stars);
        GJDifficultySprite::updateFeatureStateFromLevel(level);
    }

    void updateDifficultyFrame(int frame, GJDifficultyName name) {
        // Workaround for positions being updated.
        if (!m_fields->m_customDifficultyFrame) {
            GJDifficultySprite::updateDifficultyFrame(frame, name);
        }
    }

    void updateCustomDifficultyFrame(int stars) {
        auto* spriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
        bool legacyIcons = Mod::get()->getSettingValue<bool>("legacy-icons");

        m_fields->m_customDifficultyFrame = false;
        
        std::string suffix = legacyIcons ? "_Legacy" : "";
        std::string spriteFrameName = fmt::format(
            "MD_Difficulty{:02}{}.png"_spr,
            stars,
            suffix
        );

        auto* spriteFrame = spriteFrameCache->spriteFrameByName(
            spriteFrameName.c_str()
        );

        if (spriteFrame != nullptr) {
            m_fields->m_customDifficultyFrame = true;
            setDisplayFrame(spriteFrame);
        }
    }

    bool m_customDifficultyFrame;
};
