#include <filter.h>

Filter::Filter(QObject* parent) : QObject(parent)
{
    m_item_categories = {
        "Any",
        "Any Weapon",
        "One-Handed Weapon",
        "One-Handed Melee Weapon",
        "Two-Handed Melee Weapon",
        "Bow",
        "Claw",
        "Any Dagger",
        "Base Dagger",
        "Rune Dagger",
        "One-Handed Axe",
        "One-Handed Sword",
        "Any One-handed Mace",
        "Base One-Handed Mace",
        "Sceptre",
        "Any Staff",
        "Base Staff",
        "Warstaff",
        "Two-Handed Axe",
        "Two-Handed Mace",
        "Two-Handed Sword",
        "Wand",
        "Fishing Rod",
        "Any Armour",
        "Body Armour",
        "Boots",
        "Gloves",
        "Helmet",
        "Shield",
        "Quiver",
        "Any Acessory",
        "Amulet",
        "Belt",
        "Ring",
        "Trinket",
        "Any Gem",
        "Skill Gem",
        "Support Gem",
        "Awakened Support Gem",
        "Any Jewel",
        "Base Jewel",
        "Abyss Jewel",
        "Cluster Jewel",
        "Flask",
        "Map",
        "Map Fragment",
        "Breachstone",
        "Maven's Invitation",
        "Scarab",
        "Leaguestone",
        "Memory Line",
        "Divination Card",
        "Captured Beast",
        "Any Heist Equipment",
        "Heist Gear",
        "Heist Tool",
        "Heist Cloak",
        "Heist Brooch",
        "Any Heist Mission",
        "Heist Contract",
        "Heist Blueprint",
        "Any Expedition Logbook",
        "Sanctum Research",
        "Sanctum Relic",
        "Any Tincture",
        "Any Corpse",
        "Any Currency",
        "Unique Fragment",
        "Resonator",
        "Fossil",
        "Incubator",
        "Heist Target",
        "Omen",
        "Tatoo"
    };

    m_item_rarities = {
        "Any",
        "Normal",
        "Magic",
        "Rare",
        "Unique",
        "Unique (Foil)",
        "Any Non-Unique"
    };

    m_character_classes = {
        "Any",
        "Scion",
        "Marauder",
        "Ranger",
        "Witch",
        "Duelist",
        "Templar",
        "Shadow"
    };

    m_corpse_types = {
        "Any",
        "Eldritch",
        "Demon",
        "Construct",
        "Undead",
        "Beast",
        "Humanoid"
    };

    m_foil_variations = {
        "Any",
        "None",
        "Rainbow (Default)",
        "Any Voidborn Variant",
        "Amethyst",
        "Verdant",
        "Ruby",
        "Cobalt",
        "Sunset",
        "Aureate",
        "Any Celestial Variant"
        "Celestial Quartz",
        "Celestial Ruby",
        "Celestial Emerald",
        "Celestial Aureate",
        "Celestial Pearl",
        "Celestial Amethyst",
    };

};
