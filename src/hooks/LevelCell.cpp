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

        	MoreDFSprite* mdSpr = MoreDFSprite::createWithStarCount({(starCount != 0) ? starCount : suggestedStarCount}, false);
			CCSprite* mdGlow = CCSprite::createWithSpriteFrameName("MD_LegendaryGlow.png"_spr);
			// mdGlow->setBlendFunc(ccBlendFunc::)

			if (mdSpr && ((starCount != 0) ? (starCount == 4 || starCount == 7 || starCount == 9) : (suggestedStarCount == 4 || suggestedStarCount == 7 || suggestedStarCount == 9))) {
				mdSpr->setZOrder(zOrder);
				mdSpr->setID("more-difficulties-spr"_spr);

				mdSpr->setPosition(difficultyPos);
				difficultyNode->addChild(mdSpr);
				difficultySpr->setOpacity(0);
			}
			
			if (Mod::get()->getSettingValue<bool>("toggle-mythic-glow")) {
				if (mdSpr && p0->m_isEpic == 2) {
					mdSpr->addChild(mdGlow);
					mdGlow->setPosition(ccp(mdSpr->getContentWidth() / 2, 26.5));
					mdGlow->setOpacity(150);
				} else if (mdSpr && p0->m_isEpic == 3) {
					mdGlow->initWithSpriteFrameName("MD_MythicGlow.png"_spr);
					mdSpr->addChild(mdGlow);
					mdGlow->setPosition(ccp(mdSpr->getContentWidth() / 2, 26.5));
					mdGlow->setOpacity(150);
				}
			}
			
			if (p0->m_levelID == 79669868) {
				if (!mdSpr) mdSpr = MoreDFSprite::createWithSpriteFrameName("MD_DifficultyCP.png"_spr);
				else mdSpr->initWithSpriteFrameName("MD_DifficultyCP.png"_spr);
				mdSpr->setPosition(difficultyPos);
				if (mdSpr->getParent() != difficultyNode) difficultyNode->addChild(mdSpr);
				difficultySpr->setOpacity(0);
			}

		} else {
			// log::info("difficultyNode no no exist");
		}
	}
}; 
