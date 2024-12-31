#pragma once

#include <libacq/util/json_struct_qt.h>

#include <optional>

namespace poe_api {

    struct AccountProfile {

        struct TwitchInfo {
            QString name;
            JS_OBJ(name);
        };

        QString uuid; // string UUIDv4 in canonical format
        QString name; // string
        std::optional<QString> realm; // ? string pc, xbox, or sony
        std::optional<TwitchInfo> twitch; // ? object present if the account is Twitch - linked
        JS_OBJ(uuid, name, realm, twitch);
    };

}