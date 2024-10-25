#pragma once

#include <acquisition/utils/json_struct_qt.h>

#include <acquisition/api_types/account.h>

#include <optional>

namespace poe_api{

    // https://www.pathofexile.com/developer/docs/reference#type-PvPLadderTeamMember

    struct PvPLadderTeamMember {

        struct Character {
            QString id; // string a unique 64 digit hexadecimal string
            QString name; // string
            unsigned level; // uint
            QString class_; // string
            std::optional<QString> league; // ? string
            std::optional<unsigned> score; // ? uint count of league objective completions
            
            JS_OBJECT(
                JS_MEMBER(id),
                JS_MEMBER(name),
                JS_MEMBER(level),
                JS_MEMBER_WITH_NAME(class_, "class"),
                JS_MEMBER(league),
                JS_MEMBER(score));
        };

        poe_api::Account account; // Account
        poe_api::PvPLadderTeamMember::Character character; // object
        std::optional<bool> public_; // ? bool always true if present
        
        JS_OBJECT(
            JS_MEMBER(account),
            JS_MEMBER(character),
            JS_MEMBER_WITH_NAME(public_, "public"));
    };

}
