#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/LevelCell.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>

class $modify(LevelCell) {
    void loadFromLevel(GJGameLevel* p0) {
        LevelCell::loadFromLevel(p0);

        int starCount = p0->m_stars.value();
        auto difficultyNode = m_mainLayer->getChildByID("difficulty-container");

        if (difficultyNode) {
            auto difficultySpr = typeinfo_cast<GJDifficultySprite*>(difficultyNode->getChildByID("difficulty-sprite"));

            // I have no fucking clue why this broke, but now I need to add an offset.
            cocos2d::CCPoint difficultyPos = difficultySpr->getPosition();
            int zOrder = difficultySpr->getZOrder();
 	    float scale = difficultySpr->getScale();

            auto useLegacyIcons = Mod::get()->getSettingValue<bool>("legacy-icons");
            auto casualSpr = CCSprite::create((useLegacyIcons) ? "MD_Difficulty04_Legacy.png"_spr : "MD_Difficulty04.png"_spr);
            auto difficultSpr = CCSprite::create((useLegacyIcons) ? "MD_Difficulty07_Legacy.png"_spr : "MD_Difficulty07.png"_spr);
            auto cruelSpr = CCSprite::create((useLegacyIcons) ? "MD_Difficulty09_Legacy.png"_spr : "MD_Difficulty09.png"_spr);

            casualSpr->setZOrder(zOrder);
            difficultSpr->setZOrder(zOrder);
            cruelSpr->setZOrder(zOrder);

	    casualSpr->setScale(scale);
            difficultSpr->setScale(scale);
            cruelSpr->setScale(scale);

            switch (starCount) {
                case 4:
                    casualSpr->setPosition(difficultyPos);
                    difficultySpr->setOpacity(0);
                    this->addChild(casualSpr);
                    break;

                case 7:
                    difficultSpr->setPosition(difficultyPos);
                    difficultySpr->setOpacity(0);
                    this->addChild(difficultSpr);
                    break;

                case 9:
                    cruelSpr->setPosition(difficultyPos);
                    difficultySpr->setOpacity(0);
                    this->addChild(cruelSpr);
                    break;

                default:
                    break;
            }
        }

        else {
            // log::info("difficultyNode no no exist");
        }
    }
};

class $modify(LevelInfoLayer) {
	bool init(GJGameLevel* p0, bool p1) {
		if (!LevelInfoLayer::init(p0, p1)) {
			return false;
		}

			int starCount = p0->m_stars.value();
	
			cocos2d::CCPoint difficultyPos = m_difficultySprite->getPosition() + CCPoint { 0.25f, 0.f };;
			int zOrder = m_difficultySprite->getZOrder();
	
		        auto useLegacyIcons = Mod::get()->getSettingValue<bool>("legacy-icons");
		        auto casualSpr = CCSprite::create((useLegacyIcons) ? "MD_Difficulty04_Legacy.png"_spr : "MD_Difficulty04.png"_spr );
		        auto difficultSpr = CCSprite::create((useLegacyIcons) ? "MD_Difficulty07_Legacy.png"_spr : "MD_Difficulty07.png"_spr );
		        auto cruelSpr = CCSprite::create((useLegacyIcons) ? "MD_Difficulty09_Legacy.png"_spr : "MD_Difficulty09.png"_spr );
	
			casualSpr->setZOrder(zOrder);
			difficultSpr->setZOrder(zOrder);
			cruelSpr->setZOrder(zOrder);
	
		        switch (starCount) {
		            case 4:
		                m_difficultySprite->setOpacity(0);
		                casualSpr->setPosition(difficultyPos);
		                this->addChild(casualSpr);
		                break;
		
		            case 7:
		                m_difficultySprite->setOpacity(0);
		                difficultSpr->setPosition(difficultyPos);
		                this->addChild(difficultSpr);
		                break;
		
		            case 9:
		                m_difficultySprite->setOpacity(0);
		                cruelSpr->setPosition(difficultyPos);
		                this->addChild(cruelSpr);
		                break;
		
		            default:
		                break;
		        }


		return true;
	}
};
