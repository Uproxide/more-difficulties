#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/LevelCell.hpp>
#include <Geode/modify/RateStarsLayer.hpp>

class $modify(LevelInfoLayer) {
	bool init(GJGameLevel* p0, bool p1) {
		if (!LevelInfoLayer::init(p0, p1)) {
			return false;
		}

		auto useLegacyIcons = Mod::get()->getSettingValue<bool>("legacy-difficulties");

		int starCount = p0->m_stars.value();
		int suggestedStarCount = p0->m_starsRequested;

		cocos2d::CCPoint difficultyPos = m_difficultySprite->getPosition() + CCPoint {(useLegacyIcons) ? .0f, .0f : .25f, -.1f};
		int zOrder = m_difficultySprite->getZOrder();

        auto mdSpr = CCSprite::createWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty04_Legacy.png"_spr : "MD_Difficulty04.png"_spr);

		mdSpr->setZOrder(zOrder);

		mdSpr->setID("more-difficulties-spr"_spr);

		if (starCount == 4) {
			mdSpr->setPosition(difficultyPos);
			this->addChild(mdSpr);
			m_difficultySprite->setOpacity(0);
		} else if (starCount == 7) {
			mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty07_Legacy.png"_spr : "MD_Difficulty07.png"_spr);
			mdSpr->setPosition(difficultyPos);
			this->addChild(mdSpr);
			m_difficultySprite->setOpacity(0);
		} else if (starCount == 9) {
			mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty09_Legacy.png"_spr : "MD_Difficulty09.png"_spr);
			mdSpr->setPosition(difficultyPos);
			this->addChild(mdSpr);
			m_difficultySprite->setOpacity(0);
		} else if (starCount == 0) {
			if (suggestedStarCount == 4) {
				mdSpr->setPosition(difficultyPos);
				this->addChild(mdSpr);
				m_difficultySprite->setOpacity(0);
			} else if (suggestedStarCount == 7) {
				mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty07_Legacy.png"_spr : "MD_Difficulty07.png"_spr);
				mdSpr->setPosition(difficultyPos);
				this->addChild(mdSpr);
				m_difficultySprite->setOpacity(0);
			} else if (suggestedStarCount == 9) {
				mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty09_Legacy.png"_spr : "MD_Difficulty09.png"_spr);
				mdSpr->setPosition(difficultyPos);
				this->addChild(mdSpr);
				m_difficultySprite->setOpacity(0);
			}
		}

		return true;
	}
};

class $modify(LevelCell) {
	void loadFromLevel(GJGameLevel* p0) {
		LevelCell::loadFromLevel(p0);

		int starCount = p0->m_stars.value();
		int suggestedStarCount = p0->m_starsRequested;

		auto difficultyNode = m_mainLayer->getChildByID("difficulty-container");

		if (difficultyNode) {
			auto useLegacyIcons = Mod::get()->getSettingValue<bool>("legacy-difficulties");
			GJDifficultySprite* difficultySpr = static_cast<GJDifficultySprite*>(difficultyNode->getChildByID("difficulty-sprite"));

			cocos2d::CCPoint difficultyPos = difficultySpr->getPosition() + CCPoint {(useLegacyIcons) ? .0f, .0f : .25f, -.1f};
			int zOrder = difficultySpr->getZOrder();

        	auto mdSpr = CCSprite::createWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty04_Legacy.png"_spr : "MD_Difficulty04.png"_spr);

			mdSpr->setZOrder(zOrder);

			mdSpr->setID("more-difficulties-spr"_spr);

			if (starCount == 4) {
				mdSpr->setPosition(difficultyPos);
				difficultyNode->addChild(mdSpr);
				difficultySpr->setOpacity(0);
			} else if (starCount == 7) {
				mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty07_Legacy.png"_spr : "MD_Difficulty07.png"_spr);
				mdSpr->setPosition(difficultyPos);
				difficultyNode->addChild(mdSpr);
				difficultySpr->setOpacity(0);
			} else if (starCount == 9) {
				mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty09_Legacy.png"_spr : "MD_Difficulty09.png"_spr);
				mdSpr->setPosition(difficultyPos);
				difficultyNode->addChild(mdSpr);
				difficultySpr->setOpacity(0);
			} else if (starCount == 0) {
				if (suggestedStarCount == 4) {
					mdSpr->setPosition(difficultyPos);
					difficultyNode->addChild(mdSpr);
					difficultySpr->setOpacity(0);
				} else if (suggestedStarCount == 7) {
					mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty07_Legacy.png"_spr : "MD_Difficulty07.png"_spr);
					mdSpr->setPosition(difficultyPos);
					difficultyNode->addChild(mdSpr);
					difficultySpr->setOpacity(0);
				} else if (suggestedStarCount == 9) {
					mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty09_Legacy.png"_spr : "MD_Difficulty09.png"_spr);
					mdSpr->setPosition(difficultyPos);
					difficultyNode->addChild(mdSpr);
					difficultySpr->setOpacity(0);
				}
			}
		} else {
			// log::info("difficultyNode no no exist");
		}
	}
};

class $modify(RateStarsLayer) {
	void selectRating(CCObject* p0) {
		RateStarsLayer::selectRating(p0);

		if (auto mdSprite = static_cast<CCSprite*>(m_mainLayer->getChildByID("uproxide.more_difficulties/more-difficulties-spr"))) {
			mdSprite->removeFromParent();
		}

		if (p0 == nullptr) {
			log::info("created ratestarslayer, n/a selected");
		} else {
			auto difficultySprite = getChildOfType<GJDifficultySprite>(m_mainLayer, 0);

			if (difficultySprite) {
				difficultySprite->setOpacity(255);

				auto useLegacyIcons = Mod::get()->getSettingValue<bool>("legacy-difficulties");
				cocos2d::CCPoint difficultyPos = difficultySprite->getPosition() + CCPoint {(useLegacyIcons) ? .0f, .0f : .25f, -.1f};
				int zOrder = difficultySprite->getZOrder();
				float difficultySize = difficultySprite->getScale();

				auto mdSpr = CCSprite::createWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty04_Legacy.png"_spr : "MD_Difficulty04.png"_spr);

				mdSpr->setZOrder(zOrder);
				mdSpr->setID("more-difficulties-spr"_spr);
				mdSpr->setScale(difficultySize);

				if (p0->getTag() == 4) {
					mdSpr->setPosition(difficultyPos);
					m_mainLayer->addChild(mdSpr);
					difficultySprite->setOpacity(0);
				} else if (p0->getTag() == 7) {
					mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty07_Legacy.png"_spr : "MD_Difficulty07.png"_spr);
					mdSpr->setPosition(difficultyPos);
					m_mainLayer->addChild(mdSpr);
					difficultySprite->setOpacity(0);
				} else if (p0->getTag() == 9) {
					mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty09_Legacy.png"_spr : "MD_Difficulty09.png"_spr);
					mdSpr->setPosition(difficultyPos);
					m_mainLayer->addChild(mdSpr);
					difficultySprite->setOpacity(0);
				}
			} else {
				auto mainMenu = getChildOfType<CCMenu>(m_mainLayer, 0);
				auto difficultyBtn = getChildOfType<CCMenuItemSpriteExtra>(mainMenu, 10);
				auto difficultySpriteMod = getChildOfType<GJDifficultySprite>(difficultyBtn, 0);

				if (auto mdSprite = static_cast<CCSprite*>(difficultyBtn->getChildByID("uproxide.more_difficulties/more-difficulties-spr"))) {
					mdSprite->removeFromParent();
				}

				difficultySpriteMod->setOpacity(255);

				auto useLegacyIcons = Mod::get()->getSettingValue<bool>("legacy-difficulties");
				cocos2d::CCPoint difficultyPos = difficultySpriteMod->getPosition() + CCPoint {(useLegacyIcons) ? .0f, .0f : .25f, -.1f};
				int zOrder = difficultySpriteMod->getZOrder();
				float difficultySize = difficultySpriteMod->getScale();

				auto mdSpr = CCSprite::createWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty04_Legacy.png"_spr : "MD_Difficulty04.png"_spr);

				mdSpr->setZOrder(zOrder);
				mdSpr->setID("more-difficulties-spr"_spr);
				mdSpr->setScale(difficultySize);

				if (p0->getTag() == 4) {
					mdSpr->setPosition(difficultyPos);
					difficultyBtn->addChild(mdSpr);
					difficultySpriteMod->setOpacity(0);
				} else if (p0->getTag() == 7) {
					mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty07_Legacy.png"_spr : "MD_Difficulty07.png"_spr);
					mdSpr->setPosition(difficultyPos);
					difficultyBtn->addChild(mdSpr);
					difficultySpriteMod->setOpacity(0);
				} else if (p0->getTag() == 9) {
					mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty09_Legacy.png"_spr : "MD_Difficulty09.png"_spr);
					mdSpr->setPosition(difficultyPos);
					difficultyBtn->addChild(mdSpr);
					difficultySpriteMod->setOpacity(0);
				}
			}
		}
	}
};
