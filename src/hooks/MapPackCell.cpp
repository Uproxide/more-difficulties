#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/MapPackCell.hpp>
#include "../managers/SaveThings.hpp"
#include "../ui/MoreDFSprite.hpp"

class $modify(MapPackCell) {
	void loadFromMapPack(GJMapPack* p0) {
		MapPackCell::loadFromMapPack(p0);

		if (auto duplicateDFSpr = this->getChildByID("difficulty-spr")) {
			duplicateDFSpr->removeFromParent();
		}

		if (auto duplicateMDSpr = this->getChildByID("more-difficulties-spr"_spr)) {
			duplicateMDSpr->removeFromParent();
		}

		int starCount = p0->m_stars;
        auto difficultySpr = this->getChildByType<CCSprite*>(0);

        if (difficultySpr) {
			difficultySpr->setID("difficulty-spr");
            MoreDFSprite* mdSpr = MoreDFSprite::createWithSpriteFrameName("MD_DifficultyYO.png"_spr);

			mdSpr->setZOrder(difficultySpr->getZOrder());
			mdSpr->setID("more-difficulties-spr"_spr);
            mdSpr->setScale(difficultySpr->getScale());
			mdSpr->setPosition(difficultySpr->getPosition());
			this->addChild(mdSpr);
			difficultySpr->setOpacity(0);
        }
    }
}; 
