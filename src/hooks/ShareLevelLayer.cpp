#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/ShareLevelLayer.hpp>
#include "../managers/SaveThings.hpp"

class $modify(ShareLevelLayer) {
    bool init(GJGameLevel* level) {
        if (!ShareLevelLayer::init(level)) return false;

        auto difficultySprite = m_mainLayer->getChildByType<CCSprite>(3);

		if (difficultySprite) {
            difficultySprite->setOpacity(255);

			auto useLegacyIcons = Mod::get()->getSettingValue<bool>("legacy-difficulties");
			cocos2d::CCPoint difficultyPos = difficultySprite->getPosition() + CCPoint { .0f, .0f };
			int zOrder = difficultySprite->getZOrder();
			float difficultySize = difficultySprite->getScale();

			auto mdSpr = CCSprite::createWithSpriteFrameName("MD_DifficultyYO.png"_spr);

			mdSpr->setZOrder(zOrder);
			mdSpr->setID("more-difficulties-spr"_spr);
			mdSpr->setScale(difficultySize);
			mdSpr->setPosition(difficultyPos);
			m_mainLayer->addChild(mdSpr);
			difficultySprite->setOpacity(0);
		}

        return true;
    }

	void selectRating(CCObject* p0) {
		ShareLevelLayer::selectRating(p0);

		if (auto mdSpriteExisting = static_cast<CCSprite*>(m_mainLayer->getChildByID("uproxide.more_difficulties/more-difficulties-spr"))) {
			mdSpriteExisting->removeFromParent();
		}

		if (p0 == nullptr) {
			log::info("created ShareLevelLayer, n/a selected");
		} else {
			auto difficultySprite = m_mainLayer->getChildByType<CCSprite>(3);

			if (difficultySprite) {
				difficultySprite->setOpacity(255);

				auto useLegacyIcons = Mod::get()->getSettingValue<bool>("legacy-difficulties");
				cocos2d::CCPoint difficultyPos = difficultySprite->getPosition() + CCPoint { .0f, .0f };
				int zOrder = difficultySprite->getZOrder();
				float difficultySize = difficultySprite->getScale();

				auto mdSpr = CCSprite::createWithSpriteFrameName("MD_DifficultyYO.png"_spr);

				mdSpr->setZOrder(zOrder);
				mdSpr->setID("more-difficulties-spr"_spr);
				mdSpr->setScale(difficultySize);
				mdSpr->setPosition(difficultyPos);
				m_mainLayer->addChild(mdSpr);
				difficultySprite->setOpacity(0);
			} 
		}
	}
};