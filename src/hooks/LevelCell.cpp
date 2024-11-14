#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/LevelCell.hpp>
#include "../managers/SaveThings.hpp"
#include "../ui/MoreDFSprite.hpp"

class $modify(LevelCell) {
	void loadFromLevel(GJGameLevel* p0) {
		LevelCell::loadFromLevel(p0);

		int starCount = p0->m_stars.value();
		int suggestedStarCount = p0->m_starsRequested;

		auto difficultyNode = m_mainLayer->getChildByID("difficulty-container");

		if (difficultyNode) {
			auto useLegacyIcons = Mod::get()->getSettingValue<bool>("legacy-difficulties");
			GJDifficultySprite* difficultySpr = static_cast<GJDifficultySprite*>(difficultyNode->getChildByID("difficulty-sprite"));

			cocos2d::CCPoint difficultyPos = difficultySpr->getPosition() + CCPoint { .0f, .0f };
			int zOrder = difficultySpr->getZOrder();
			int difficulty = p0->getAverageDifficulty();
			bool isDemon = p0->m_demon.value() == 1;

        	CCSprite* mdSpr = CCSprite::createWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty04_Legacy.png"_spr : "MD_Difficulty04.png"_spr);
			CCSprite* mdGlow = CCSprite::createWithSpriteFrameName("MD_LegendaryGlow.png"_spr);
			// mdGlow->setBlendFunc(ccBlendFunc::)

			mdSpr->setZOrder(zOrder);
			mdSpr->setID("more-difficulties-spr"_spr);

			switch(starCount) {
				case 4:
					if (SaveThings::casual && !isDemon && difficulty == 3) {
						
						mdSpr->setPosition(difficultyPos);
						difficultyNode->addChild(mdSpr);
						difficultySpr->setOpacity(0);
					}
					break;
				case 7:
					if (SaveThings::tough && !isDemon && difficulty == 4) {
						mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty07_Legacy.png"_spr : "MD_Difficulty07.png"_spr);
						mdSpr->setPosition(difficultyPos);
						difficultyNode->addChild(mdSpr);
						difficultySpr->setOpacity(0);
					}
					break;
				case 9:
					if (SaveThings::cruel && !isDemon && difficulty == 5) {
						mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty09_Legacy.png"_spr : "MD_Difficulty09.png"_spr);
						mdSpr->setPosition(difficultyPos);
						difficultyNode->addChild(mdSpr);
						difficultySpr->setOpacity(0);
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
							difficultyNode->addChild(mdSpr);
							difficultySpr->setOpacity(0);
						}
						break;
					case 7:
						if (SaveThings::tough) {
							mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty07_Legacy.png"_spr : "MD_Difficulty07.png"_spr);
							mdSpr->setPosition(difficultyPos);
							difficultyNode->addChild(mdSpr);
							difficultySpr->setOpacity(0);
						}
						break;
					case 9:
						if (SaveThings::cruel) {
							mdSpr->initWithSpriteFrameName((useLegacyIcons) ? "MD_Difficulty09_Legacy.png"_spr : "MD_Difficulty09.png"_spr);
							mdSpr->setPosition(difficultyPos);
							difficultyNode->addChild(mdSpr);
							difficultySpr->setOpacity(0);
						}
						break;
					default:
						break;
				}
			}

			if (p0->m_isEpic == 2) {
				// mdSpr->addChild(mdGlow);
			}

			if (p0->m_levelID == 79669868) {
				mdSpr->initWithSpriteFrameName("MD_DifficultyCP.png"_spr);
				mdSpr->setPosition(difficultyPos);
				difficultyNode->addChild(mdSpr);
				difficultySpr->setOpacity(0);
			}

		} else {
			// log::info("difficultyNode no no exist");
		}
	}
}; 