#pragma once

#include <libacq/util/json_struct_qt.h>

#include <optional>

namespace poe_api{

    // https://www.pathofexile.com/developer/docs/reference#type-EventLadderEntry

    struct EventLadderEntry {

        struct PrivateLeague {
            QString name; // string
            QString url; // string a url link to a Path of Exile Private League
            JS_OBJ(name, url);
        };

        unsigned rank; // uint
        std::optional<bool> ineligible; // ? bool
        std::optional<unsigned> time; // ? uint time taken to complete the league objective in seconds
        poe_api::EventLadderEntry::PrivateLeague private_league; // object
        JS_OBJ(rank, ineligible, time, private_league);
    };

}
