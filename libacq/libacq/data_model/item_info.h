#pragma once

#include <libacq/poe_api/frame_type.h>
#include <libacq/poe_api/item.h>

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

    inline static float damage(const ItemInfo& item) { return item.m_damage; };
    inline static float criticalChance(const ItemInfo& item) { return item.m_critical_chance; };
    inline static float physicalDamagePerSecond(const ItemInfo& item) { return item.m_physical_dps; };
    inline static float attacksPerSecond(const ItemInfo& item) { return item.m_attacks_per_second; };
    inline static float damagePerSecond(const ItemInfo& item) { return item.m_damage_per_second; };
    inline static float elementalDamagePerSecond(const ItemInfo& item) { return item.m_elemental_dps; };
    inline static float chaosDamagePerSecond(const ItemInfo& item) { return item.m_chaos_dps; };

    inline static int redSockets(const ItemInfo& item) { return item.m_red_sockets; };
    inline static int greenSockets(const ItemInfo& item) { return item.m_green_sockets; };
    inline static int blueSockets(const ItemInfo& item) { return item.m_blue_sockets; };
    inline static int whiteSockets(const ItemInfo& item) { return item.m_white_sockets; };
    inline static int abyssSockets(const ItemInfo& item) { return item.m_abyss_sockets; };
    inline static int sockets(const ItemInfo& item) { return item.m_sockets; };

    // TBD: socket groups

    inline static float armour(const ItemInfo& item) { return item.m_armour; };
    inline static float energyShield(const ItemInfo& item) { return item.m_energy_shield; };
    inline static float block(const ItemInfo& item) { return item.m_block; };
    inline static float evasionRating(const ItemInfo& item) { return item.m_evasion_rating; };
    inline static float ward(const ItemInfo& item) { return item.m_ward; };
    inline static float basePercentile(const ItemInfo& item) { return item.m_base_percentile; };

    inline static float requiredLevel(const ItemInfo& item) { return item.m_required_level; };
    inline static float requiredStrength(const ItemInfo& item) { return item.m_required_strength; };
    inline static float requiredDexterity(const ItemInfo& item) { return item.m_required_dexterity; };
    inline static float requiredIntelligence(const ItemInfo& item) { return item.m_required_intelligence; };
    inline static QString requiredClass(const ItemInfo& item) { return item.m_required_class; };

private:

    static float averageValue(const QString& ranged_value, bool* ok);

    void loadSockets(const poe_api::Item& item);
    void loadProperties(const poe_api::Item& item);
    void loadRequirements(const poe_api::Item& item);

    QString m_item_category;
    poe_api::FrameType m_item_rarity;

    float m_damage{ 0.0 };
    float m_critical_chance{ 0.0 };
    float m_physical_dps{ 0.0 };
    float m_attacks_per_second{ 0.0 };
    float m_damage_per_second{ 0.0 };
    float m_elemental_dps{ 0.0 };
    float m_chaos_dps{ 0.0 }; // custom extension

    int m_armour{ 0 };
    int m_energy_shield{ 0 };
    int m_block{ 0 };
    int m_evasion_rating{ 0 };
    int m_ward{ 0 };
    int m_base_percentile{ 0 };

    int m_red_sockets{ 0 };
    int m_green_sockets{ 0 };
    int m_blue_sockets{ 0 };
    int m_white_sockets{ 0 };
    int m_abyss_sockets{ 0 }; // custom extension
    int m_sockets{ 0 };

    struct SocketGroup {
        unsigned red;
        unsigned green;
        unsigned blue;
        unsigned white;
        unsigned abyss;
    };
    std::vector<SocketGroup> m_socket_groups;

    int m_required_level{ 0 };
    int m_required_strength{ 0 };
    int m_required_dexterity{ 0 };
    int m_required_intelligence{ 0 };
    QString m_required_class;

    int m_quality{ 0 };
    int m_item_level{ 0 };
    int m_gem_level{ 0 };
    int m_gem_experience{ 0 };

    bool m_transigured_gem{ false };
    bool m_vaal_gem{ false };
    QString m_corpse_type;
    bool m_crucible_item{ false };
    bool m_fractured_item{ false };
    bool m_synthesised_item{ false };
    bool m_searing_exarch_item{ false };
    bool m_eater_of_worlds_item{ false };
    bool m_identified{ false };
    bool m_corrupted{ false };
    bool m_mirrored{ false };
    bool m_split{ false };
    bool m_crafted{ false };
    bool m_veiled{ false };
    bool m_forseeing{ false };
    int m_talisman_tier{ 0 };
    int m_stored_experience{ 0 };
    int m_stack_size{ 0 };
    QString m_alternate_art;
    QString m_foil_variation;
    int m_scourge_tier{ 0 };
};
