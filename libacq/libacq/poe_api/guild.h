#pragma once

#include <libacq/json/json_struct_qt.h>

namespace poe_api {

    // https://www.pathofexile.com/developer/docs/reference#type-Guild

    struct Guild {
        unsigned id; // uint
        QString name; // string
        QString tag; // string
        JS_OBJ(id, name, tag);
    };

}
