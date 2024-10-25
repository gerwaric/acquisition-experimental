#pragma once

#include <acquisition/utils/json_struct_qt.h>

#include <optional>

namespace poe_api {
    
    // https://www.pathofexile.com/developer/docs/reference#type-ItemSocket

    struct ItemSocket {
        unsigned group; // uint
        std::optional<QString> attr; // ? string S, D, I, G, A, or DV
        std::optional<QString> sColour; // ? string R, G, B, W, A, or DV
        JS_OBJ(group, attr, sColour);
    };

}
