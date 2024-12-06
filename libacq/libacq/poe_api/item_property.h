#pragma once

#include <libacq/json/json_struct_qt.h>

#include <libacq/poe_api/display_mode.h>

#include <optional>
#include <vector>

namespace poe_api {
    
    // https://www.pathofexile.com/developer/docs/reference#type-ItemProperty

    struct ItemProperty {
        QString name; // string
        std::vector<std::tuple<QString, int>> values; // array of array
        std::optional<poe_api::DisplayMode> displayMode; // ? uint as DisplayMode
        std::optional<double>progress; // ? double rounded to 2 decimal places
        std::optional<unsigned> type; // ? uint
        std::optional<QString> suffix; // ? string
        JS_OBJ(name, values, displayMode, progress, type, suffix);
    };

}
