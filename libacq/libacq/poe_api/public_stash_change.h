#pragma once

#include <libacq/json/json_struct_qt.h>

#include <libacq/poe_api/item.h>

#include <optional>
#include <vector>

namespace poe_api{

    // https://www.pathofexile.com/developer/docs/reference#type-PublicStashChange

    struct PublicStashChange {

        QString id; // string a unique 64 digit hexadecimal string
        bool public_; // bool if false then optional properties will be null
        std::optional<QString> accountName; // ? string
        std::optional<QString> stash; // ? string the name of the stash
        std::optional<QString> lastCharacterName; // ? string not included by default.Requires extra permissions
        QString stashType; // string
        std::optional<QString> league; // ? string the league's name
        std::vector<poe_api::Item> items; // array of Item

        JS_OBJECT(
            JS_MEMBER(id),
            JS_MEMBER_WITH_NAME(public_, "public"),
            JS_MEMBER(accountName),
            JS_MEMBER(stash),
            JS_MEMBER(lastCharacterName),
            JS_MEMBER(stashType),
            JS_MEMBER(league),
            JS_MEMBER(items));

    };

}
