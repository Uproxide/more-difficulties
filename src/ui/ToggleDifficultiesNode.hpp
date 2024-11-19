#pragma once

#include <Geode/loader/SettingV3.hpp>
#include <Geode/loader/Mod.hpp>
#include "ToggleDifficultiesPopup.hpp"

using namespace geode::prelude;

class ToggleDifficultiesNode : public SettingV3 {
public:
    static Result<std::shared_ptr<ToggleDifficultiesNode>> parse(std::string const& key, std::string const& modID, matjson::Value const& json) {
        auto res = std::make_shared<ToggleDifficultiesNode>();
        auto root = checkJson(json, "ToggleDifficultiesNode");
        res->init(key, modID, root);
        res->parseNameAndDescription(root);
        res->parseEnableIf(root);
        root.checkUnknownKeys();
        return root.ok(res);
    }

    bool load(matjson::Value const& json) override {
        return true;
    }
    bool save(matjson::Value& json) const override {
        return true;
    }

    bool isDefaultValue() const override {
        return true;
    }
    void reset() override {}

    SettingNodeV3* createNode(float width) override;
};

class ToggleDFButtonNode : public SettingNodeV3 {
protected:
    CCSprite* m_buttonSprite;
    CCMenuItemSpriteExtra* m_button;

    bool init(std::shared_ptr<ToggleDifficultiesNode> setting, float width) {
        if (!SettingNodeV3::init(setting, width))
            return false;
    
        m_buttonSprite = CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png");
        m_buttonSprite->setScale(.4f);
        m_button = CCMenuItemSpriteExtra::create(
            m_buttonSprite, this, menu_selector(ToggleDFButtonNode::onButton)
        );
        this->getButtonMenu()->addChildAtPosition(m_button, Anchor::Center);
        this->getButtonMenu()->setContentWidth(40);
        this->getButtonMenu()->updateLayout();
        m_button->setPositionX(m_button->getPositionX() + 10);

        this->updateState(nullptr);
        
        return true;
    }
    
    void updateState(CCNode* invoker) override {
        SettingNodeV3::updateState(invoker);
        auto shouldEnable = this->getSetting()->shouldEnable();
        m_button->setEnabled(shouldEnable);
        m_buttonSprite->setCascadeColorEnabled(true);
        m_buttonSprite->setCascadeOpacityEnabled(true);
        m_buttonSprite->setOpacity(shouldEnable ? 255 : 155);
        m_buttonSprite->setColor(shouldEnable ? ccWHITE : ccGRAY);
    }
    void onButton(CCObject*) {
        ToggleDifficultiesPopup::create()->show();
    }

    void onCommit() override {}
    void onResetToDefault() override {}

public:
    static ToggleDFButtonNode* create(std::shared_ptr<ToggleDifficultiesNode> setting, float width) {
        auto ret = new ToggleDFButtonNode();
        if (ret && ret->init(setting, width)) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }

    bool hasUncommittedChanges() const override {
        return false;
    }
    bool hasNonDefaultValue() const override {
        return false;
    }

    std::shared_ptr<ToggleDifficultiesNode> getSetting() const {
        return std::static_pointer_cast<ToggleDifficultiesNode>(SettingNodeV3::getSetting());
    }
};

SettingNodeV3* ToggleDifficultiesNode::createNode(float width) {
    return ToggleDFButtonNode::create(
        std::static_pointer_cast<ToggleDifficultiesNode>(shared_from_this()),
        width
    );
}

$execute {
    (void)Mod::get()->registerCustomSettingType("toggle-difficulties", 
        [](const std::string& key, const std::string& modID, const matjson::Value& json) -> geode::Result<std::shared_ptr<geode::SettingV3>, std::string> {
            auto res = ToggleDifficultiesNode::parse(key, modID, json);
            return geode::Ok(std::static_pointer_cast<geode::SettingV3>(res.unwrap()));
        }
    );
}
