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
	SaveThings::casual = true;
	SaveThings::tough = true;
	SaveThings::cruel = true;
}