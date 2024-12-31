#pragma once

#include <libacq/poe/passivegroup.h>
#include <libacq/poe/passivenode.h>

#include <optional>
#include <unordered_map>

namespace poe_api {
    
    // https://www.pathofexile.com/developer/docs/reference#type-ItemJewelData

    struct ItemJewelData {

        struct Subgraph {
            std::unordered_map<QString, poe_api::PassiveGroup> groups; // dictionary of PassiveGroup the key is the string value of the group id
            std::unordered_map<QString, poe_api::PassiveNode> nodes; // dictionary of PassiveNode the key is the string value of the node identifier
            JS_OBJ(groups, nodes);
        };

        QString type; // string
        std::optional<unsigned> radius; // ? uint
        std::optional<unsigned> radiusMin; // ? uint
        std::optional<QString> radiusVisual; // ? string
        std::optional<poe_api::ItemJewelData::Subgraph> subgraph; // ? object only present on cluster jewels
        JS_OBJ(type, radius, radiusMin, radiusVisual, subgraph);
    };

}
