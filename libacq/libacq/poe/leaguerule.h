#pragma once

#include <libacq/util/json_struct_qt.h>

#include <optional>

namespace poe_api{

    // https://www.pathofexile.com/developer/docs/reference#type-LeagueRule
    
    struct LeagueRule {
        QString                              id;             // string examples : Hardcore, NoParties(SSF)
        QString                              name;           // string
        std::optional<QString>                    description;    // ? string
        JS_OBJ(id, name, description);
    };

}
