#pragma once

#include <libacq/util/json_struct_qt.h>

#include <libacq/poe/item.h>

#include <optional>
#include <vector>

namespace poe_api{

    struct LegacyStash {

        struct Colour {
            unsigned r;
            unsigned g;
            unsigned b;
            JS_OBJ(r, g, b);
        };

        struct Tab {
            QString n;
            unsigned i;
            QString id;
            QString type;
            bool selected;
            poe_api::LegacyStash::Colour colour;
            QString srcL;
            QString srcC;
            QString srcR;
            JS_OBJ(n, i, id, type, selected, colour, srcL, srcC, srcR);
        };

        unsigned numTabs;
        std::vector<poe_api::LegacyStash::Tab> tabs;
        // blightLayout
        // currencyLayout
        // deliriumLayout
        // delveLayout
        // divinationLayout
        // essenceLayout
        // gemLayout
        // mapLayout
        // ultimatumLayout
        std::optional<bool> quadLayout;
        std::vector<poe_api::Item> items;
        JS_OBJ(numTabs, tabs, quadLayout, items);
    };

}
