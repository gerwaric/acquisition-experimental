#pragma once

#include <libacq/util/json_struct_qt.h>

#include <libacq/poe/item.h>

#include <unordered_map>
#include <vector>

namespace poe_api{

    struct LegacyCharacter {
        QString name;
        QString realm;
        QString class_;
        QString league;
        unsigned level;
        bool pinnable;
        JS_OBJECT(
            JS_MEMBER(name),
            JS_MEMBER(realm),
            JS_MEMBER_WITH_NAME(class_, "class"),
            JS_MEMBER(league),
            JS_MEMBER(level),
            JS_MEMBER(pinnable));
    };

    struct LegacyCharacterList {
        std::vector<poe_api::LegacyCharacter> characters;
        JS_OBJ(characters);
    };

    struct LegacyCharacterStash {
        std::vector<poe_api::Item> items;
        JS_OBJ(items);
    };

}
