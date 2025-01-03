add_library(libacq STATIC
    "libacq/constants.h"
    "libacq/model/characternode.cpp"
    "libacq/model/characternode.h"
    "libacq/model/iteminfo.cpp"
    "libacq/model/iteminfo.h"
    "libacq/model/itemnode.cpp"
    "libacq/model/itemnode.h"
    "libacq/model/rootnode.cpp"
    "libacq/model/rootnode.h"
    "libacq/model/stashnode.cpp"
    "libacq/model/stashnode.h"
    "libacq/model/treemodel.cpp"
    "libacq/model/treemodel.h"
    "libacq/model/treenode.cpp"
    "libacq/model/treenode.h"
    "libacq/oauth/oauthmanager.cpp"
    "libacq/oauth/oauthmanager.h"
    "libacq/oauth/oauthsettings.h"
    "libacq/oauth/oauthtoken.cpp"
    "libacq/oauth/oauthtoken.h"
    "libacq/poe/account.h"
    "libacq/poe/accountprofile.h"
    "libacq/poe/character.h"
    "libacq/poe/cruciblenode.h"
    "libacq/poe/displaymode.h"
    "libacq/poe/eventladderentry.h"
    "libacq/poe/frametype.h"
    "libacq/poe/guild.h"
    "libacq/poe/item.h"
    "libacq/poe/itemfilter.h"
    "libacq/poe/itemjeweldata.h"
    "libacq/poe/itemproperty.h"
    "libacq/poe/itemsocket.h"
    "libacq/poe/ladderentry.h"
    "libacq/poe/league.h"
    "libacq/poe/leagueaccount.h"
    "libacq/poe/leaguerule.h"
    "libacq/poe/passivegroup.h"
    "libacq/poe/passivenode.h"
    "libacq/poe/publicstashchange.h"
    "libacq/poe/pvpladderteamentry.h"
    "libacq/poe/pvpladderteammember.h"
    "libacq/poe/pvpmatch.h"
    "libacq/poe/stashtab.h"
    "libacq/poe/webcharacter.h"
    "libacq/poe/webstashtab.h"
    "libacq/ratelimit/ratelimitedreply.cpp"
    "libacq/ratelimit/ratelimitedreply.h"
    "libacq/ratelimit/ratelimitedrequest.cpp"
    "libacq/ratelimit/ratelimitedrequest.h"
    "libacq/ratelimit/ratelimiter.cpp"
    "libacq/ratelimit/ratelimiter.h"
    "libacq/ratelimit/ratelimitmanager.cpp"
    "libacq/ratelimit/ratelimitmanager.h"
    "libacq/ratelimit/ratelimitpolicy.cpp"
    "libacq/ratelimit/ratelimitpolicy.h"
    "libacq/storage/leaguestore.cpp"
    "libacq/storage/leaguestore.h"
    "libacq/storage/userstore.h"
    "libacq/storage/userstore.cpp"
    "libacq/util/commandline.cpp"
    "libacq/util/commandline.h"
    "libacq/util/fatalerror.cpp"
    "libacq/util/fatalerror.h"
    "libacq/util/json_struct_qt.h"
    "libacq/util/settings.cpp"
    "libacq/util/settings.h"
    "libacq/util/utils.cpp"
    "libacq/util/utils.h"
)

target_link_libraries(libacq PUBLIC
    Qt6::Core
    Qt6::HttpServer
    Qt6::Network
    Qt6::Quick
    Qt6::Sql
    boost-headers-only
    QsLog
    json_struct
)

target_include_directories(libacq PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
