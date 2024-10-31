#pragma once

#include <acquisition/api_types/frame_type.h>
#include <acquisition/api_types/item.h>

#include <QString>

enum class PropertyType {
    MapTier = 1,
    ItemQuantity = 2,
    ItemRarity = 3,
    MonsterPackSize = 4,
    Level = 5,
    Quality = 6,
    PhysicalDamage = 9,
    ElementalDamage = 10,
    ChaosDamage = 11,
    CriticalStrikeChance = 12,
    AttacksPerSecond = 13,
    WeaponRange = 14,
    ChanceToBlock = 15,
    Armour = 16,
    EvasionRating = 17,
    EnergyShield = 18,
    Radius = 26,
    StackSize = 32,
    AreaLevel = 34,
    Requires = 38,
    HeistTarget = 47,
    Ward = 54,
    Limit = 87,
    MoreMaps = 88,
    MoreScarabs = 89
};

enum class RequirementType {
    Level = 62,
    Strength = 63,
    Dexterity = 64,
    Intelligence = 65
    //Class = 66
};

class ItemInfo {
public:
    ItemInfo(const poe_api::Item& item);

    QString item_category;
    poe_api::FrameType item_rarity;

    float damage{ 0.0 };
    float critical_chance{ 0.0 };
    float physical_dps{ 0.0 };
    float attacks_per_second{ 0.0 };
    float damage_per_second{ 0.0 };
    float elemental_dps{ 0.0 };

    float chaos_dps{ 0.0 }; // currently unused

    int armour{ 0 };
    int energy_shield{ 0 };
    int block{ 0 };
    int evasion{ 0 };
    int ward{ 0 };
    int base_percentile{ 0 };

    int red_sockets{ 0 };
    int green_sockets{ 0 };
    int blue_sockets{ 0 };
    int white_sockets{ 0 };
    int sockets{ 0 };

    int red_links{ 0 };
    int green_links{ 0 };
    int blue_links{ 0 };
    int white_links{ 0 };
    int links{ 0 };

    int required_level{ 0 };
    int required_strength{ 0 };
    int required_dexterity{ 0 };
    int required_intelligence{ 0 };
    QString required_class;

    int quality{ 0 };
    int item_level{ 0 };
    int gem_level{ 0 };
    int gem_experience{ 0 };

    bool transigured_gem{ false };
    bool vaal_gem{ false };
    QString corpse_type;
    bool crucible_item{ false };
    bool fractured_item{ false };
    bool synthesised_item{ false };
    bool searing_exarch_item{ false };
    bool eater_of_worlds_item{ false };
    bool identified{ false };
    bool corrupted{ false };
    bool mirrored{ false };
    bool split{ false };
    bool crafted{ false };
    bool veiled{ false };
    bool forseeing{ false };
    int talisman_tier{ 0 };
    int stored_experience{ 0 };
    int stack_size{ 0 };
    QString alternate_art;
    QString foil_variation;
    int scourge_tier{ 0 };

private:
    void loadProperties(const poe_api::Item& item);
    void loadRequirements(const poe_api::Item& item);
    float averageValue(const QString& property, bool* ok);
};

/*
class ItemInfo {
public:
    ItemInfo(const poe_api::Item& item);

    QString item_category;
    QString item_rarity;

    std::optional<float> damage;
    std::optional<float> critical_chance;
    std::optional<float> physical_dps;
    std::optional<float> attacks_per_second;
    std::optional<float> damage_per_second;
    std::optional<float> elemental_dps;

    std::optional<int> armour;
    std::optional<int> energy_shield;
    std::optional<int> block;
    std::optional<int> evasion;
    std::optional<int> ward;
    std::optional<int> base_percentile;

    std::optional<int> red_sockets;
    std::optional<int> green_sockets;
    std::optional<int> blue_sockets;
    std::optional<int> white_sockets;
    std::optional<int> sockets;

    std::optional<int> red_links;
    std::optional<int> green_links;
    std::optional<int> blue_links;
    std::optional<int> white_links;
    std::optional<int> links;

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
    std::optional<QString> corpse_type;
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
    std::optional<QString> alternate_art;
    std::optional<QString> foil_variation;
    int scourge_tier;

private:
    void loadProperties(const poe_api::Item& item);
    void loadRequirements(const poe_api::Item& item);

};
*/
