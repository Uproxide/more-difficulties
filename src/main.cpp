#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include "ToggleDifficultiesNode.hpp"
#include "ToggleDifficultiesPopup.hpp"
#include "SaveThings.hpp"

// amunjud

SettingNode* SettingRefreshValue::createNode(float width) {
    return ToggleDifficultiesNode::create(this, width);
}

void ToggleDifficultiesNode::onToggleBtn(CCObject*) {
	ToggleDifficultiesPopup::create()->show();
}

$on_mod(Loaded) {
    Mod::get()->addCustomSetting<SettingRefreshValue>("toggle-difficulties", "none");

	SaveThings::casual = Mod::get()->getSavedValue<bool>("casual", true);
	SaveThings::tough = Mod::get()->getSavedValue<bool>("tough", true);
	SaveThings::cruel = Mod::get()->getSavedValue<bool>("cruel", true);
}