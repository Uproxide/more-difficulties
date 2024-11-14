#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/LevelInfoLayer.hpp>
#include "../managers/SaveThings.hpp"

class $modify(LevelInfoLayer) {
	bool init(GJGameLevel* p0, bool p1) {
		if (!LevelInfoLayer::init(p0, p1)) {
			return false;
		}

		log::info("{}", p0->m_isEpic);

		auto useLegacyIcons = Mod::get()->getSettingValue<bool>("legacy-difficulties");

		int starCount = p0->m_stars.value();
		int suggestedStarCount = p0->m_starsRequested;
		int difficulty = p0->getAverageDifficulty();
		bool isDemon = p0->m_demon.value() == 1;

		cocos2d::CCPoint difficultyPos = m_difficultySprite->getPosition() + CCPoint { .0f, .0f };
		int zOrder = m_difficultySprite->getZOrder();

        auto mdSpr = CCSprite::createWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty04_Legacy.png"_spr : "MD_Difficulty04.png"_spr);

		mdSpr->setZOrder(zOrder);
		mdSpr->setID("more-difficulties-spr"_spr);

		switch(starCount) {
			case 4:
				if (SaveThings::casual && !isDemon && difficulty == 3) {
					mdSpr->setPosition(difficultyPos);
					this->addChild(mdSpr);
					m_difficultySprite->setOpacity(0);
				}
				break;
			case 7:
				if (SaveThings::tough && !isDemon && difficulty == 4) {
					mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty07_Legacy.png"_spr : "MD_Difficulty07.png"_spr);
					mdSpr->setPosition(difficultyPos);
					this->addChild(mdSpr);
					m_difficultySprite->setOpacity(0);
				}
				break;
			case 9:
				if (SaveThings::cruel && !isDemon && difficulty == 5) {
					mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty09_Legacy.png"_spr : "MD_Difficulty09.png"_spr);
					mdSpr->setPosition(difficultyPos);
					this->addChild(mdSpr);
					m_difficultySprite->setOpacity(0);
				}
				break;
			default:
				break;
		}

		if (starCount == 0) {
			switch(suggestedStarCount) {
				case 4:
					if (SaveThings::casual) {
						mdSpr->setPosition(difficultyPos);
						this->addChild(mdSpr);
						m_difficultySprite->setOpacity(0);
					}
					break;
				case 7:
					if (SaveThings::tough) {
						mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty07_Legacy.png"_spr : "MD_Difficulty07.png"_spr);
						mdSpr->setPosition(difficultyPos);
						this->addChild(mdSpr);
						m_difficultySprite->setOpacity(0);
					}
					break;
				case 9:
					if (SaveThings::cruel) {
						mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty09_Legacy.png"_spr : "MD_Difficulty09.png"_spr);
						mdSpr->setPosition(difficultyPos);
						this->addChild(mdSpr);
						m_difficultySprite->setOpacity(0);
					}
					break;
				default:
					break;
			}
		}

		if (p0->m_levelID == 79669868) {
			mdSpr->initWithSpriteFrameName("MD_DifficultyCP.png"_spr);
			mdSpr->setPosition(difficultyPos);
			this->addChild(mdSpr);
			m_difficultySprite->setOpacity(0);
		}

		return true;
	}
};