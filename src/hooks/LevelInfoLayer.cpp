#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/LevelInfoLayer.hpp>
#include "../managers/SaveThings.hpp"
#include "../ui/MoreDFSprite.hpp"

class $modify(LevelInfoLayer) {
	bool init(GJGameLevel* p0, bool p1) {
		if (!LevelInfoLayer::init(p0, p1)) {
			return false;
		}

		auto useLegacyIcons = Mod::get()->getSettingValue<bool>("legacy-difficulties");

		int starCount = p0->m_stars.value();
		int suggestedStarCount = p0->m_starsRequested;
		int difficulty = p0->getAverageDifficulty();
		bool isDemon = p0->m_demon.value() == 1;

		cocos2d::CCPoint difficultyPos = m_difficultySprite->getPosition() + CCPoint { .0f, .0f };
		int zOrder = m_difficultySprite->getZOrder();

        MoreDFSprite* mdSpr = MoreDFSprite::createWithStarCount({(starCount != 0) ? starCount : suggestedStarCount}, false);
		CCSprite* mdGlow = CCSprite::createWithSpriteFrameName("MD_LegendaryGlow.png"_spr);

		if (mdSpr && ((starCount != 0) ? (starCount == 4 || starCount == 7 || starCount == 9) : (suggestedStarCount == 4 || suggestedStarCount == 7 || suggestedStarCount == 9))) {
			mdSpr->setZOrder(zOrder);
			mdSpr->setID("more-difficulties-spr"_spr);

			mdSpr->setPosition(difficultyPos);
			this->addChild(mdSpr);
			m_difficultySprite->setOpacity(0);
		}

		if (p0->m_levelID == 79669868) {
			if (!mdSpr) mdSpr = MoreDFSprite::createWithSpriteFrameName("MD_DifficultyCP.png"_spr);
			else mdSpr->initWithSpriteFrameName("MD_DifficultyCP.png"_spr);
			mdSpr->setPosition(difficultyPos);
			if (mdSpr->getParent() != this) this->addChild(mdSpr);
			m_difficultySprite->setOpacity(0);
		}

		return true;
	}
};
