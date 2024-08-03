#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/LevelPage.hpp>
#include "../SaveThings.hpp"

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

			auto mdSpr = CCSprite::createWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty04Small_Legacy.png"_spr : "MD_Difficulty04Small.png"_spr);

			mdSpr->setZOrder(zOrder);
			mdSpr->setID("more-difficulties-spr"_spr);
			mdSpr->setScale(difficultySize);

			switch(p0->m_levelID) {
				case 5:
				case 7:
					if (SaveThings::casual) {
						difficultySpr->getParent()->addChild(mdSpr);
						mdSpr->setPosition(difficultyPos);
						difficultySpr->setVisible(false);
					}
					break;
				case 8:
				case 9:		
				case 13:
				case 21:
				case 22:
					if (SaveThings::tough) {
						difficultySpr->getParent()->addChild(mdSpr);
						mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty07Small_Legacy.png"_spr : "MD_Difficulty07Small.png"_spr);
						mdSpr->setPosition(difficultyPos);
						difficultySpr->setVisible(false);
					}
					break;
				case 11:
				case 15:
					if (SaveThings::cruel) {
						difficultySpr->getParent()->addChild(mdSpr);
						mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty09Small_Legacy.png"_spr : "MD_Difficulty09Small.png"_spr);
						mdSpr->setPosition(difficultyPos);
						difficultySpr->setVisible(false);
					}
					break;
				default:
					/* we all gotta */ break; /* sometime */
			} // sorry for the sin guys... best way for Main Levles...
		}
	}
};