#pragma once

#include <libacq/json/json_struct_qt.h>

#include <libacq/poe_api/guild.h>

#include <optional>

namespace poe_api {

    // https://www.pathofexile.com/developer/docs/reference#type-Account

    struct Account {

        struct Challenges {
            QString set; // string the challenge set
            unsigned completed; // uint
            unsigned max; // uint
            JS_OBJ(set, completed, max);
        };

        struct TwitchStream {
            QString name; // string
            QString image; // string
            QString status; // string
            JS_OBJ(name, image, status);
        };

        struct Twitch {
            QString name; // string
            std::optional<poe_api::Account::TwitchStream> stream; // ? object
            JS_OBJ(name, stream);
        };

        QString name; // string
        std::optional<QString> realm; // ? string pc, xbox, or sony
        std::optional<poe_api::Guild> guild; // ? Guild
        std::optional<poe_api::Account::Challenges> challenges; // ? object
        std::optional<poe_api::Account::Twitch> twitch; // ? object
        JS_OBJ(name, realm, guild, challenges, twitch);
    };
}
