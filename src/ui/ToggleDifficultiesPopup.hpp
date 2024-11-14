#pragma once

#include <Geode/Geode.hpp>
#include <Geode/Loader.hpp>
#include <Geode/utils/web.hpp>
#include <Geode/loader/Event.hpp>
#include <Geode/ui/TextInput.hpp>
#include <cctype>
#include <algorithm>
#include "./managers/SaveThings.hpp"

using namespace geode::prelude;


class ToggleDifficultiesPopup : public Popup<> {
public:
    bool setup() {
        log::info("hai");

        auto bg = cocos2d::extension::CCScale9Sprite::create("square02_small.png");
        m_mainLayer->addChild(bg);
        bg->setPosition(m_bgSprite->getContentSize() / 2);
        bg->setContentHeight(90);
        bg->setContentWidth(365);
        bg->setOpacity(100);

        auto menu = CCMenu::create(); // ccmenucreate
        bg->addChild(menu);

        menu->setLayout(
            RowLayout::create()
                ->setGap(45)
        );
        

        menu->setPosition(bg->getContentSize() / 2);

        auto offCasual = CCSprite::createWithSpriteFrameName("MD_Difficulty04.png"_spr);
        offCasual->setOpacity(100);

        auto casualToggle = CCMenuItemToggler::create(
            offCasual,
            CCSprite::createWithSpriteFrameName("MD_Difficulty04.png"_spr),
            this,
            menu_selector(ToggleDifficultiesPopup::toggleDifficulty)
        );
        menu->addChild(casualToggle);

        auto offTough = CCSprite::createWithSpriteFrameName("MD_Difficulty07.png"_spr);
        offTough->setOpacity(100);

        auto toughToggle = CCMenuItemToggler::create(
            offTough,
            CCSprite::createWithSpriteFrameName("MD_Difficulty07.png"_spr),
            this,
            menu_selector(ToggleDifficultiesPopup::toggleDifficulty)
        );
        menu->addChild(toughToggle);

        auto offCruel = CCSprite::createWithSpriteFrameName("MD_Difficulty09.png"_spr);
        offCruel->setOpacity(100);

        auto cruelToggle = CCMenuItemToggler::create(
            offCruel,
            CCSprite::createWithSpriteFrameName("MD_Difficulty09.png"_spr),
            this,
            menu_selector(ToggleDifficultiesPopup::toggleDifficulty)
        );
        menu->addChild(cruelToggle);
        menu->setContentWidth(400);
        menu->setScale(1.5);
        menu->updateLayout();

        casualToggle->setTag(1);
        toughToggle->setTag(2);
        cruelToggle->setTag(3);

        casualToggle->toggle(SaveThings::casual);
        toughToggle->toggle(SaveThings::tough);
        cruelToggle->toggle(SaveThings::cruel);

        return true;
    }

    void toggleDifficulty(CCObject* toggler) {
        switch (toggler->getTag()) {
            case 1:
                SaveThings::casual = !SaveThings::casual;
                Mod::get()->setSavedValue<bool>("casual", SaveThings::casual);
                break;
            
            case 2:
                SaveThings::tough = !SaveThings::tough;
                Mod::get()->setSavedValue<bool>("tough", SaveThings::tough);
                break;

            case 3:
                SaveThings::cruel = !SaveThings::cruel;
                Mod::get()->setSavedValue<bool>("cruel", SaveThings::cruel);
                break;

            default:
                break;
        }

        log::info("{}", SaveThings::casual);
        log::info("{}", SaveThings::tough);
        log::info("{}", SaveThings::cruel);
    }

    static ToggleDifficultiesPopup* create() {
        auto ret = new ToggleDifficultiesPopup();
        if (ret && ret->initAnchored(400, 130, "geode.loader/GE_square01.png")) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
};