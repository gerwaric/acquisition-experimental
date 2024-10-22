target_include_directories(acquisition PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    # This second line is a compromise that violates the
    # rest of the project layout, but the headers for
    # QML_ELEMENT objects must be directly on the include
    # path, not in a subdirectory
    ${CMAKE_CURRENT_SOURCE_DIR}/acquisition
)

add_subdirectory("acquisition/qml")

# Acquisition
target_sources(acquisition PRIVATE
    "acquisition/acquisition.cpp"
    "acquisition/acquisition.h"
    "acquisition/command_line.cpp"
    "acquisition/command_line.h"
    "acquisition/constants.h"
    "acquisition/search_filters.cpp"
    "acquisition/search_filters.h"
    "acquisition/main.cpp"
    "acquisition/settings.cpp"
    "acquisition/settings.h"
)

# API data structures
target_sources(acquisition PRIVATE
    "acquisition/api_types/account.h"
    "acquisition/api_types/character.h"
    "acquisition/api_types/crucible_node.h"
    "acquisition/api_types/display_mode.h"
    "acquisition/api_types/event_ladder_entry.h"
    "acquisition/api_types/frame_type.h"
    "acquisition/api_types/guild.h"
    "acquisition/api_types/item.h"
    "acquisition/api_types/item_filter.h"
    "acquisition/api_types/item_jewel_data.h"
    "acquisition/api_types/item_property.h"
    "acquisition/api_types/item_socket.h"
    "acquisition/api_types/ladder_entry.h"
    "acquisition/api_types/league.h"
    "acquisition/api_types/league_account.h"
    "acquisition/api_types/league_rule.h"
    "acquisition/api_types/legacy_character.h"
    "acquisition/api_types/legacy_stash_tab.h"
    "acquisition/api_types/passive_group.h"
    "acquisition/api_types/passive_node.h"
    "acquisition/api_types/public_stash_change.h"
    "acquisition/api_types/pvp_ladder_team_entry.h"
    "acquisition/api_types/pvp_ladder_team_member.h"
    "acquisition/api_types/pvp_match.h"
    "acquisition/api_types/stash_tab.h"
)

target_sources(acquisition PRIVATE
    "acquisition/data_model/character_node.cpp"
    "acquisition/data_model/character_node.h"
    "acquisition/data_model/item_node.cpp"
    "acquisition/data_model/item_node.h"
    "acquisition/data_model/stash_node.cpp"
    "acquisition/data_model/stash_node.h"
    "acquisition/data_model/tree_model.cpp"
    "acquisition/data_model/tree_model.h"
    "acquisition/data_model/tree_node.cpp"
    "acquisition/data_model/tree_node.h"
)

# Databases
target_sources(acquisition PRIVATE
    #"acquisition/data_stores/data_store.cpp"
    #"acquisition/data_stores/data_store.h"
    "acquisition/data_stores/league_data_store.cpp"
    "acquisition/data_stores/league_data_store.h"
    "acquisition/data_stores/user_data_store.h"
    "acquisition/data_stores/user_data_store.cpp"
)

# OAuth authentication
target_sources(acquisition PRIVATE
    "acquisition/oauth/oauth_manager.cpp"
    "acquisition/oauth/oauth_manager.h"
    "acquisition/oauth/oauth_token.cpp"
    "acquisition/oauth/oauth_token.h"
)

# API rate limiting
target_sources(acquisition PRIVATE
    "acquisition/rate_limit/rate_limited_reply.cpp"
    "acquisition/rate_limit/rate_limited_reply.h"
    "acquisition/rate_limit/rate_limited_request.cpp"
    "acquisition/rate_limit/rate_limited_request.h"
    "acquisition/rate_limit/rate_limiter.cpp"
    "acquisition/rate_limit/rate_limiter.h"
    "acquisition/rate_limit/rate_limit_manager.cpp"
    "acquisition/rate_limit/rate_limit_manager.h"
    "acquisition/rate_limit/rate_limit_policy.cpp"
    "acquisition/rate_limit/rate_limit_policy.h"
    #"acquisition/rate_limit/rate_limit_status_dialog.cpp"
    #"acquisition/rate_limit/rate_limit_status_dialog.h"
)

# Utils
target_sources(acquisition PRIVATE
    "acquisition/utils/fatal_error.cpp"
    "acquisition/utils/fatal_error.h"
    "acquisition/utils/json.h"
    #"acquisition/utils/oauth2.cpp"
    #"acquisition/utils/oauth2.h"
    "acquisition/utils/utils.cpp"
    "acquisition/utils/utils.h"
)

#[[
# User interface
target_sources(acquisition PRIVATE
    "acquisition/widgets/filters_panel.cpp"
    "acquisition/widgets/filters_panel.h"
    "acquisition/widgets/main_window.cpp"
    "acquisition/widgets/main_window.h"
    "acquisition/widgets/type_filters_panel.cpp"
    "acquisition/widgets/type_filters_panel.h"
)
#]]
