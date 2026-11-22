#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include "ui/ToggleDifficultiesNode.hpp"
#include "ui/ToggleDifficultiesPopup.hpp"
#include "managers/SaveThings.hpp"
//#include <smjs.object-collab/include/object_collab.hpp>

//using namespace object_collab::prelude;


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


	/*ObjectAPI::registerObject(ObjectInfo::builder()
        .id("casual"_spr)
        .sprite("MD_Difficulty04Small.png"_spr)
        .construction(QuickObject::builder() // Optional
            .objectType(GameObjectType::Decoration) // Optional
            .defaultZLayer(ZLayer::Default) // Optional
            .defaultZOrder(9) // Optional
            .build())
        .editorTab(EditorTab::Particles) // Optional
        .build());

	ObjectAPI::registerObject(ObjectInfo::builder()
        .id("tough"_spr)
        .sprite("MD_Difficulty07Small.png"_spr)
        .construction(QuickObject::builder() // Optional
            .objectType(GameObjectType::Decoration) // Optional
            .defaultZLayer(ZLayer::Default) // Optional
            .defaultZOrder(9) // Optional
            .build())
        .editorTab(EditorTab::Particles) // Optional
        .build());

	ObjectAPI::registerObject(ObjectInfo::builder()
        .id("cruel"_spr)
        .sprite("MD_Difficulty09Small.png"_spr)
        .construction(QuickObject::builder() // Optional
            .objectType(GameObjectType::Decoration) // Optional
            .defaultZLayer(ZLayer::Default) // Optional
            .defaultZOrder(9) // Optional
            .build())
        .editorTab(EditorTab::Particles) // Optional
        .build());

	ObjectAPI::registerObject(ObjectInfo::builder()
        .id("theyellowone"_spr)
        .sprite("MD_DifficultyYOSmall.png"_spr)
        .construction(QuickObject::builder() // Optional
            .objectType(GameObjectType::Decoration) // Optional
            .defaultZLayer(ZLayer::Default) // Optional
            .defaultZOrder(9) // Optional
            .build())
        .editorTab(EditorTab::Particles) // Optional
        .build());*/
}