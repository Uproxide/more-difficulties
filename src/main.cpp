#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/LevelCell.hpp>
#include <Geode/modify/RateStarsLayer.hpp>
#include <Geode/modify/ShareLevelLayer.hpp>
#include <Geode/modify/LevelPage.hpp>

// amunjud

class $modify(LevelInfoLayer) {
	bool init(GJGameLevel* p0, bool p1) {
		if (!LevelInfoLayer::init(p0, p1)) {
			return false;
		}

		log::info("{}", p0->m_isEpic);

		auto useLegacyIcons = Mod::get()->getSettingValue<bool>("legacy-difficulties");

		int starCount = p0->m_stars.value();
		int suggestedStarCount = p0->m_starsRequested;

		cocos2d::CCPoint difficultyPos = m_difficultySprite->getPosition() + CCPoint {(useLegacyIcons) ? .0f, .0f : .25f, -.1f};
		int zOrder = m_difficultySprite->getZOrder();

        auto mdSpr = CCSprite::createWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty04_Legacy.png"_spr : "MD_Difficulty04.png"_spr);

		mdSpr->setZOrder(zOrder);
		mdSpr->setID("more-difficulties-spr"_spr);

		switch(starCount) {
			case 4:
				if (p0->m_isEpic == 2) {
					mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty04_LegacyLegendary.png"_spr : "MD_Difficulty04Legendary.png"_spr);
				} else if (p0->m_isEpic == 3) {
					mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty04_LegacyMythic.png"_spr : "MD_Difficulty04Mythic.png"_spr);
				}
				mdSpr->setPosition(difficultyPos);
				this->addChild(mdSpr);
				m_difficultySprite->setOpacity(0);
				break;
			case 7:
				if (p0->m_isEpic == 2) {
					mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty07_LegacyLegendary.png"_spr : "MD_Difficulty07Legendary.png"_spr);
				} else if (p0->m_isEpic == 3) {
					mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty07_LegacyMythic.png"_spr : "MD_Difficulty07Mythic.png"_spr);
				} else {
					mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty07_Legacy.png"_spr : "MD_Difficulty07.png"_spr);
				}
				mdSpr->setPosition(difficultyPos);
				this->addChild(mdSpr);
				m_difficultySprite->setOpacity(0);
				break;
			case 9:
				if (p0->m_isEpic == 2) {
					mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty09_LegacyLegendary.png"_spr : "MD_Difficulty09Legendary.png"_spr);
				} else if (p0->m_isEpic == 3) {
					mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty09_LegacyMythic.png"_spr : "MD_Difficulty09Mythic.png"_spr);
				} else {
					mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty09_Legacy.png"_spr : "MD_Difficulty09.png"_spr);
				}
				mdSpr->setPosition(difficultyPos);
				this->addChild(mdSpr);
				m_difficultySprite->setOpacity(0);
				break;
			default:
				break;
		}

		if (starCount == 0) {
			switch(suggestedStarCount) {
				case 4:
					mdSpr->setPosition(difficultyPos);
					this->addChild(mdSpr);
					m_difficultySprite->setOpacity(0);
					break;
				case 7:
					mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty07_Legacy.png"_spr : "MD_Difficulty07.png"_spr);
					mdSpr->setPosition(difficultyPos);
					this->addChild(mdSpr);
					m_difficultySprite->setOpacity(0);
					break;
				case 9:
					mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty09_Legacy.png"_spr : "MD_Difficulty09.png"_spr);
					mdSpr->setPosition(difficultyPos);
					this->addChild(mdSpr);
					m_difficultySprite->setOpacity(0);
					break;
				default:
					break;
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

			switch(starCount) {
				case 4:
					if (p0->m_isEpic == 2) {
						mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty04_LegacyLegendary.png"_spr : "MD_Difficulty04Legendary.png"_spr);
					} else if (p0->m_isEpic == 3) {
						mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty04_LegacyMythic.png"_spr : "MD_Difficulty04Mythic.png"_spr);
					}
					mdSpr->setPosition(difficultyPos);
					difficultyNode->addChild(mdSpr);
					difficultySpr->setOpacity(0);
					break;
				case 7:
					if (p0->m_isEpic == 2) {
						mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty07_LegacyLegendary.png"_spr : "MD_Difficulty07Legendary.png"_spr);
					} else if (p0->m_isEpic == 3) {
						mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty07_LegacyMythic.png"_spr : "MD_Difficulty07Mythic.png"_spr);
					} else {
						mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty07_Legacy.png"_spr : "MD_Difficulty07.png"_spr);
					}
					mdSpr->setPosition(difficultyPos);
					difficultyNode->addChild(mdSpr);
					difficultySpr->setOpacity(0);
					break;
				case 9:
					if (p0->m_isEpic == 2) {
						mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty09_LegacyLegendary.png"_spr : "MD_Difficulty09Legendary.png"_spr);
					} else if (p0->m_isEpic == 3) {
						mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty09_LegacyMythic.png"_spr : "MD_Difficulty09Mythic.png"_spr);
					} else {
						mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty09_Legacy.png"_spr : "MD_Difficulty09.png"_spr);
					}
					mdSpr->setPosition(difficultyPos);
					difficultyNode->addChild(mdSpr);
					difficultySpr->setOpacity(0);
					break;
				default:
					break;
			}

			if (starCount == 0) {
				switch(suggestedStarCount) {
					case 4:
						mdSpr->setPosition(difficultyPos);
						difficultyNode->addChild(mdSpr);
						difficultySpr->setOpacity(0);
						break;
					case 7:
						mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty07_Legacy.png"_spr : "MD_Difficulty07.png"_spr);
						mdSpr->setPosition(difficultyPos);
						difficultyNode->addChild(mdSpr);
						difficultySpr->setOpacity(0);
						break;
					case 9:
						mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty09_Legacy.png"_spr : "MD_Difficulty09.png"_spr);
						mdSpr->setPosition(difficultyPos);
						difficultyNode->addChild(mdSpr);
						difficultySpr->setOpacity(0);
						break;
					default:
						break;
				}
			}
		} else {
			// log::info("difficultyNode no no exist");
		}
	}
}; 

#ifndef GEODE_IS_MACOS
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
				cocos2d::CCPoint difficultyPos = difficultySprite->getPosition() + CCPoint {(useLegacyIcons) ? .0f, .0f : .25f, -.1f};
				int zOrder = difficultySprite->getZOrder();
				float difficultySize = difficultySprite->getScale();

				auto mdSpr = CCSprite::createWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty04_Legacy.png"_spr : "MD_Difficulty04.png"_spr);

				mdSpr->setZOrder(zOrder);
				mdSpr->setID("more-difficulties-spr"_spr);
				mdSpr->setScale(difficultySize);

				switch(p0->getTag()) {
					case 4:
						mdSpr->setPosition(difficultyPos);
						this->addChild(mdSpr);
						difficultySprite->setOpacity(0);
						break;
					case 7:
						mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty07_Legacy.png"_spr : "MD_Difficulty07.png"_spr);
						mdSpr->setPosition(difficultyPos);
						this->addChild(mdSpr);
						difficultySprite->setOpacity(0);
						break;
					case 9:
						mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty09_Legacy.png"_spr : "MD_Difficulty09.png"_spr);
						mdSpr->setPosition(difficultyPos);
						this->addChild(mdSpr);
						difficultySprite->setOpacity(0);
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
						mdSpr->setPosition(difficultyPos);
						difficultyBtn->addChild(mdSpr);
						difficultySpriteMod->setOpacity(0);
						break;
					case 7:
						mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty07_Legacy.png"_spr : "MD_Difficulty07.png"_spr);
						mdSpr->setPosition(difficultyPos);
						difficultyBtn->addChild(mdSpr);
						difficultySpriteMod->setOpacity(0);
						break;
					case 9:
						mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty09_Legacy.png"_spr : "MD_Difficulty09.png"_spr);
						mdSpr->setPosition(difficultyPos);
						difficultyBtn->addChild(mdSpr);
						difficultySpriteMod->setOpacity(0);
						break;
					default:
						break;
				}
			}
		}
	}
};
#endif

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
					difficultySpr->getParent()->addChild(mdSpr);
					mdSpr->setPosition(difficultyPos);
					difficultySpr->setVisible(false);
					break;
				
				case 8:
				case 9:		
				case 13:
				case 21:
					difficultySpr->getParent()->addChild(mdSpr);
					mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty07Small_Legacy.png"_spr : "MD_Difficulty07Small.png"_spr);
					mdSpr->setPosition(difficultyPos);
					difficultySpr->setVisible(false);
					break;
					
				case 11:
				case 15:
					difficultySpr->getParent()->addChild(mdSpr);
					mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty09Small_Legacy.png"_spr : "MD_Difficulty09Small.png"_spr);
					mdSpr->setPosition(difficultyPos);
					difficultySpr->setVisible(false);
					break;

				default:
					/* we all gotta */ break; /* sometime */
			} // sorry for the sin guys... best way for Main Levles...
		}
	}
};

/* class $modify(ShareLevelLayer) {
	void selectRating(CCObject* p0) {
		ShareLevelLayer::selectRating(p0);

		if (auto mdSprite = static_cast<CCSprite*>(m_mainLayer->getChildByID("more-difficulties-spr"_spr))) {
			mdSprite->removeFromParent();
		}

		if (p0 == nullptr) {
			log::info("created ShareLevelLayer, n/a selected");


		} else {

		}
	}
}; */

