#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/RateStarsLayer.hpp>
#include "../SaveThings.hpp"

class $modify(RateStarsLayer) {
	void selectRating(CCObject* p0) {
		RateStarsLayer::selectRating(p0);

		if (auto mdSprite = static_cast<CCSprite*>(this->getChildByID("uproxide.more_difficulties/more-difficulties-spr"))) {
			mdSprite->removeFromParent();
		}

		if (p0 == nullptr) {
			log::info("created ratestarslayer, n/a selected");
		} else {
			auto difficultySprite = getChildOfType<GJDifficultySprite>(m_mainLayer, 0);

			if (difficultySprite) {
				difficultySprite->setOpacity(255);

				auto useLegacyIcons = Mod::get()->getSettingValue<bool>("legacy-difficulties");
				cocos2d::CCPoint difficultyPos = difficultySprite->getPosition() + (useLegacyIcons ? CCPoint { .0f, .0f } : CCPoint { .25f, -.1f });
				int zOrder = difficultySprite->getZOrder();
				float difficultySize = difficultySprite->getScale();

				auto mdSpr = CCSprite::createWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty04_Legacy.png"_spr : "MD_Difficulty04.png"_spr);

				mdSpr->setZOrder(zOrder);
				mdSpr->setID("more-difficulties-spr"_spr);
				mdSpr->setScale(difficultySize);

				switch(p0->getTag()) {
					case 4:
						if (SaveThings::casual) {
							mdSpr->setPosition(difficultyPos);
							this->addChild(mdSpr);
							difficultySprite->setOpacity(0);
						}
						break;
					case 7:
						if (SaveThings::tough) {
							mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty07_Legacy.png"_spr : "MD_Difficulty07.png"_spr);
							mdSpr->setPosition(difficultyPos);
							this->addChild(mdSpr);
							difficultySprite->setOpacity(0);
						}
						break;
					case 9:
						if (SaveThings::cruel) {
							mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty09_Legacy.png"_spr : "MD_Difficulty09.png"_spr);
							mdSpr->setPosition(difficultyPos);
							this->addChild(mdSpr);
							difficultySprite->setOpacity(0);
						}
						break;
					default:
						break;
				}
			} else {
				auto mainMenu = getChildOfType<CCMenu>(m_mainLayer, 0);
				auto difficultyBtn = getChildOfType<CCMenuItemSpriteExtra>(mainMenu, 10);
				auto difficultySpriteMod = getChildOfType<GJDifficultySprite>(difficultyBtn, 0);


				difficultySpriteMod->setOpacity(255);

				auto useLegacyIcons = Mod::get()->getSettingValue<bool>("legacy-difficulties");
				cocos2d::CCPoint difficultyPos = difficultySpriteMod->getPosition() + CCPoint {(useLegacyIcons) ? .0f, .0f : .25f, -.1f};
				int zOrder = difficultySpriteMod->getZOrder();
				float difficultySize = difficultySpriteMod->getScale();

				if (auto mdSprite = static_cast<CCSprite*>(difficultyBtn->getChildByID("uproxide.more_difficulties/more-difficulties-spr"))) {
					mdSprite->removeFromParent();
				}

				auto mdSpr = CCSprite::createWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty04_Legacy.png"_spr : "MD_Difficulty04.png"_spr);

				mdSpr->setZOrder(zOrder);
				mdSpr->setID("more-difficulties-spr"_spr);
				mdSpr->setScale(difficultySize);

				switch(p0->getTag()) {
					case 4:
						if (SaveThings::casual) {
							mdSpr->setPosition(difficultyPos);
							difficultyBtn->addChild(mdSpr);
							difficultySpriteMod->setOpacity(0);
						}
						break;
					case 7:
						if (SaveThings::tough) {
							mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty07_Legacy.png"_spr : "MD_Difficulty07.png"_spr);
							mdSpr->setPosition(difficultyPos);
							difficultyBtn->addChild(mdSpr);
							difficultySpriteMod->setOpacity(0);
						}
						break;
					case 9:
						if (SaveThings::cruel) {
							mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty09_Legacy.png"_spr : "MD_Difficulty09.png"_spr);
							mdSpr->setPosition(difficultyPos);
							difficultyBtn->addChild(mdSpr);
							difficultySpriteMod->setOpacity(0);
						}
						break;
					default:
						break;
				}
			}
		}
	}
};