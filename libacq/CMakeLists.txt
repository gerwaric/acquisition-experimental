add_library(libacq STATIC
    "libacq/json/json_struct_qt.h"
    "libacq/poe_api/account.h"
    "libacq/poe_api/account_profile.h"
    "libacq/poe_api/character.h"
    "libacq/poe_api/crucible_node.h"
    "libacq/poe_api/display_mode.h"
    "libacq/poe_api/event_ladder_entry.h"
    "libacq/poe_api/frame_type.h"
    "libacq/poe_api/guild.h"
    "libacq/poe_api/item.h"
    "libacq/poe_api/item_filter.h"
    "libacq/poe_api/item_jewel_data.h"
    "libacq/poe_api/item_property.h"
    "libacq/poe_api/item_socket.h"
    "libacq/poe_api/ladder_entry.h"
    "libacq/poe_api/league.h"
    "libacq/poe_api/league_account.h"
    "libacq/poe_api/league_rule.h"
    "libacq/poe_api/legacy_character.h"
    "libacq/poe_api/legacy_stash_tab.h"
    "libacq/poe_api/passive_group.h"
    "libacq/poe_api/passive_node.h"
    "libacq/poe_api/public_stash_change.h"
    "libacq/poe_api/pvp_ladder_team_entry.h"
    "libacq/poe_api/pvp_ladder_team_member.h"
    "libacq/poe_api/pvp_match.h"
    "libacq/poe_api/stash_tab.h"
)

target_link_libraries(libacq PUBLIC
    Qt6::Core
    json_struct
)

target_include_directories(libacq PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
