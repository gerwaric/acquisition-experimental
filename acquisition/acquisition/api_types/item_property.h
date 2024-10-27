#pragma once

#include <acquisition/utils/json_struct_qt.h>

#include <acquisition/api_types/display_mode.h>

#include <optional>
#include <vector>

namespace poe_api {
    
    // https://www.pathofexile.com/developer/docs/reference#type-ItemProperty

    struct ItemProperty {

        struct PropertyValue {
            QString value;
            unsigned int value_type;
            JS_OBJ(value, value_type);
        };

        QString name; // string
        std::vector<PropertyValue> values; // array of array
        std::optional<poe_api::DisplayMode> displayMode; // ? uint as DisplayMode
        std::optional<double>progress; // ? double rounded to 2 decimal places
        std::optional<unsigned> type; // ? uint
        std::optional<QString> suffix; // ? string
        JS_OBJ(name, values, displayMode, progress, type, suffix);
    };

}
