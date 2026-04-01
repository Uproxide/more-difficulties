#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/LevelPage.hpp>
#include "../managers/SaveThings.hpp"

class $modify(LevelPage) {
	static void onModify(auto& self) {
        if (!self.setHookPriority("LevelPage::updateDynamicPage", 100001)) {
            log::warn("uh oh");
        }
    }

	void updateDynamicPage(GJGameLevel* p0) {
		LevelPage::updateDynamicPage(p0);
		
		auto difficultySpr = static_cast<CCSprite*>(this->getChildByIDRecursive("difficulty-sprite"));

		if (difficultySpr) {
			auto useLegacyIcons = Mod::get()->getSettingValue<bool>("legacy-difficulties");
			cocos2d::CCPoint difficultyPos = difficultySpr->getPosition();
			int zOrder = difficultySpr->getZOrder();
			float difficultySize = difficultySpr->getScale();

			if (auto spr = static_cast<CCSprite*>(this->getChildByIDRecursive("more-difficulties-spr"_spr))) {
				spr->removeMeAndCleanup();
			}

			auto mdSpr = CCSprite::createWithSpriteFrameName("MD_DifficultyYO.png"_spr);

			mdSpr->setZOrder(zOrder);
			mdSpr->setID("more-difficulties-spr"_spr);
			mdSpr->setScale(difficultySize);
			difficultySpr->getParent()->addChild(mdSpr);
			mdSpr->setPosition(difficultyPos);
			difficultySpr->setVisible(false);
		}
	}
};