#pragma once

#include <acquisition/api_types/item.h>

#include <optional>

class ItemInfo {
public:

    struct WeaponInfo {
        WeaponInfo(const poe_api::Item& item);
        float damage;
        float critical_chance;
        float physical_dps;
        float attacks_per_second;
        float damage_per_second;
        float elemental_dps;
    };

    struct ArmourInfo {
        ArmourInfo(const poe_api::Item& item);
        int armour;
        int energy_shield;
        int block;
        int evasion;
        int ward;
        int base_percentile;
    };

    struct SocketGroup {
        int red;
        int green;
        int blue;
    };

    struct SocketInfo {
        SocketInfo(const poe_api::Item& item);
        SocketGroup sockets;
        SocketGroup links;
        int total_sockets;
        int total_links;
    };

    ItemInfo(const poe_api::Item& item);

    QString item_category;
    QString item_rarity;

    std::optional<WeaponInfo> weapon_info;
    std::optional<ArmourInfo> armour_info;
    std::optional<SocketInfo> socket_info;

    std::optional<int> required_level;
    std::optional<int> required_strength;
    std::optional<int> required_dexterity;
    std::optional<int> required_intelligence;
    std::optional<QString> required_class;

    std::optional<int> quality;
    std::optional<int> item_level;
    std::optional<int> gem_level;
    std::optional<int> gem_experience;

    bool transigured_gem;
    bool vaal_gem;
    QString corpse_type;
    bool crucible_item;
    bool fractured_item;
    bool synthesised_item;
    bool searing_exarch_item;
    bool eater_of_worlds_item;
    bool identified;
    bool corrupted;
    bool mirrored;
    bool split;
    bool crafted;
    bool veiled;
    bool forseeing;
    int talisman_tier;
    int stored_experience;
    int stack_size;
    QString alternate_art;
    QString foil_variation;
    int scourge_tier;
};
