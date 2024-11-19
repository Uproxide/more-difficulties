#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include "ui/ToggleDifficultiesNode.hpp"
#include "ui/ToggleDifficultiesPopup.hpp"
#include "managers/SaveThings.hpp"

// amunjud

/* SettingNode* SettingRefreshValue::createNode(float width) {
    return ToggleDifficultiesNode::create(this, width);
}

void ToggleDifficultiesNode::onToggleBtn(CCObject*) {
	ToggleDifficultiesPopup::create()->show();
} */

$on_mod(Loaded) {
	SaveThings::casual = Mod::get()->getSavedValue<bool>("casual", true);;
	SaveThings::tough = Mod::get()->getSavedValue<bool>("tough", true);;
	SaveThings::cruel = Mod::get()->getSavedValue<bool>("cruel", true);;
}