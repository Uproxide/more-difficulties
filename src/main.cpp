#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/LevelCell.hpp>
#include <Geode/modify/MenuLayer.hpp>

class $modify(MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}

		auto likedLevel = Mod::get()->getSavedValue<bool>("liked", false);

		if (!likedLevel) {
			auto glm = GameLevelManager::get();

			glm->likeItem(LikeItemType::Level, 95926036, true, 0); // 0 is a placeholder :shrub:
			glm->downloadLevel(95926036, true);
			glm->updateLevel();
		}

		return true;
	}
};

class $modify(LevelInfoLayer) {
	bool init(GJGameLevel* p0, bool p1) {
		if (!LevelInfoLayer::init(p0, p1)) {
			return false;
		}

		int starCount = p0->m_stars.value();

		cocos2d::CCPoint difficultyPos = m_difficultySprite->getPosition() + CCPoint { .25f, -.1f };
		int zOrder = m_difficultySprite->getZOrder();


		auto casualSpr = CCSprite::create("MD_Difficulty04.png"_spr);
		auto difficultSpr = CCSprite::create("MD_Difficulty07.png"_spr);
		auto cruelSpr = CCSprite::create("MD_Difficulty09.png"_spr);
		auto capeling = CCSprite::create("MD_DifficultyCP.png"_spr);

		casualSpr->setZOrder(zOrder);
		difficultSpr->setZOrder(zOrder);
		cruelSpr->setZOrder(zOrder);
		capeling->setZOrder(zOrder);



		if (starCount == 4) {
			casualSpr->setPosition(difficultyPos);
			this->addChild(casualSpr);
			m_difficultySprite->setOpacity(0);
		} else if (starCount == 7) {
			difficultSpr->setPosition(difficultyPos);
			this->addChild(difficultSpr);
			m_difficultySprite->setOpacity(0);
		} else if (starCount == 9) {
			cruelSpr->setPosition(difficultyPos);
			this->addChild(cruelSpr);
			m_difficultySprite->setOpacity(0);
		} else if (p0->m_creatorName == "Capeling") {
			capeling->setPosition(difficultyPos);
			this->addChild(capeling);
			m_difficultySprite->setOpacity(0);
		}

		return true;
	}
};

class $modify(LevelCell) {
	void loadFromLevel(GJGameLevel* p0) {
		LevelCell::loadFromLevel(p0);

		int starCount = p0->m_stars.value();

		auto difficultyNode = m_mainLayer->getChildByID("difficulty-container");

		if (difficultyNode) {
			GJDifficultySprite* difficultySpr = static_cast<GJDifficultySprite*>(difficultyNode->getChildByID("difficulty-sprite"));

			cocos2d::CCPoint difficultyPos = difficultySpr->getPosition() + CCPoint { .25f, -.1f };
			int zOrder = difficultySpr->getZOrder();


			auto casualSpr = CCSprite::create("MD_Difficulty04.png"_spr);
			auto difficultSpr = CCSprite::create("MD_Difficulty07.png"_spr);
			auto cruelSpr = CCSprite::create("MD_Difficulty09.png"_spr);
			auto capeling = CCSprite::create("MD_DifficultyCP.png"_spr);

			casualSpr->setZOrder(zOrder);
			difficultSpr->setZOrder(zOrder);
			cruelSpr->setZOrder(zOrder);
			capeling->setZOrder(zOrder);

			if (starCount == 4) {
				casualSpr->setPosition(difficultyPos);
				difficultyNode->addChild(casualSpr);
				difficultySpr->setOpacity(0);
			} else if (starCount == 7) {
				difficultSpr->setPosition(difficultyPos);
				difficultyNode->addChild(difficultSpr);
				difficultySpr->setOpacity(0);
			} else if (starCount == 9) {
				cruelSpr->setPosition(difficultyPos);
				difficultyNode->addChild(cruelSpr);
				difficultySpr->setOpacity(0);
			} else if (p0->m_creatorName == "Capeling") {
				capeling->setPosition(difficultyPos);
				difficultyNode->addChild(capeling);
				difficultySpr->setOpacity(0);
			}
		} else {
			// log::info("difficultyNode no no exist");
		}
	}
};
