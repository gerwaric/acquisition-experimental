#pragma once

#include <acquisition/data_model/item_info.h>

#include <QObject>
#include <QQmlEngine>

using FilterFunction = std::function<bool(const ItemInfo& item_info)>;

class SearchFilters : public QObject {
    Q_OBJECT
    Q_PROPERTY(QStringList itemCategories MEMBER m_item_categories CONSTANT);
    Q_PROPERTY(QStringList itemRarities MEMBER m_item_rarities CONSTANT);
    Q_PROPERTY(QStringList characterClasses MEMBER m_character_classes CONSTANT);
    Q_PROPERTY(QStringList mapSeries MEMBER m_map_series CONSTANT);
    Q_PROPERTY(QStringList mapCompletionRewards MEMBER m_map_completion_rewards CONSTANT);
    Q_PROPERTY(QStringList heistContractObjectiveValues MEMBER m_heist_contract_objective_values CONSTANT);
    Q_PROPERTY(QStringList ultimatumChallengeTypes MEMBER m_ultimatum_challenge_types CONSTANT);
    Q_PROPERTY(QStringList ultimatumRewardTypes MEMBER m_ultimatum_reward_types CONSTANT);
    Q_PROPERTY(QStringList ultimatumRequiredItems MEMBER m_ultimatum_required_items CONSTANT);
    Q_PROPERTY(QStringList ultimatumRewardUniques MEMBER m_ultimatum_reward_uniques CONSTANT);
    Q_PROPERTY(QStringList corpseTypes MEMBER m_corpse_types CONSTANT);
    Q_PROPERTY(QStringList foilVariations MEMBER m_foil_variations CONSTANT);
    QML_ELEMENT

public:
    SearchFilters(QObject* parent = nullptr);

    enum class Filter {
        // Type
        Category,
        Rarity,
        // Weapon Filters
        DamageMin,
        DamageMax,
        CriticalChanceMin,
        CriticalChanceMax,
        AttacksPerSecondMin,
        AttacksPerSecondMax,
        DamagePerSecondMin,
        DamagePerSecondMax,
        ElementalDpsMin,
        ElementalDpsMax,
        // Armour Filters
        ArmourMin,
        ArmourMax,
        EnergyShieldMin,
        EnergyShieldMax,
        BlockMin,
        BlockMax,
        EvasionMin,
        EvasionMax,
        WardMin,
        WardMax,
        BasePercentileMin,
        BasePercentileMax,
        // Socket Filters
        SocketsRed,
        SocketsGreen,
        SocketsBlue,
        SocketsWhite,
        SocketsMin,
        SocketsMax,
        LinksRed,
        LinksBlue,
        LinksWhite,
        LinksMin,
        LinksMax,
        // Requirements
        LevelMin,
        LevelMax,
        StrengthMin,
        StrengthMax,
        DexterityMin,
        DexterityMax,
        IntelligenceMin,
        IntelligenceMax,
        CharacterClass,
        // MapFilters
        MapTier,
        MapPacksize,
        MapIIR,
        MapIIQ,
        AreaLevel,
        MapSeries,
        BlightedMap,
        BlightRavagedMap,
        MapCompletionReward,
        // HeistFilters
        WingsRevealed,
        TotalWingsRevealed,
        EscapeRoutesRevealed,
        TotalEscapeRoutes,
        RewardRoomsRevealed,
        TotalRewardRooms,
        ConractObjectiveValue,
        LockpickingLevel,
        BruteForceLevel,
        PerceptionLevel,
        DemolitionLevel,
        CounterThaumaturgyLevel,
        TrapDisarmamentLevel,
        AgilityLevel,
        DeceptionLevel,
        EngineeringLevel,
        // SanctumFilters
        Resolve,
        MaximumResolve,
        Inspiration,
        Aureus,
        // UltimatumFilters
        ChallengeType,
        RewardType,
        RequiredItem,
        RewardUnique,
        // Miscellaneous
        QualityMin,
        QualityMax,
        ItemLevelMin,
        ItemLevelMax,
        GemLevelMin,
        GemLevelMax,
        GemExperienceMin,
        GemExperienceMax,
        TransfiguredGem,
        VaalGem,
        CorpseType,
        CrucibleItem,
        FracturedItem,
        SynthesizedItem,
        SearingExarchItem,
        EaterOfWorldsItem,
        Identified,
        Corrupted,
        Mirrored,
        Split,
        Crafted,
        Veiled,
        Forseeing,
        TalismanTierMin,
        TalismanTierMax,
        StoredExperienceMin,
        StoredExperienceMax,
        StackSizeMin,
        StaskSizeMax,
        AlternateArt,
        FoilVariation,
        ScourgeTier,
    };
    Q_ENUM(Filter)

private:

    QStringList m_item_categories;
    QStringList m_item_rarities;
    QStringList m_character_classes;
    QStringList m_map_series;
    QStringList m_map_completion_rewards;
    QStringList m_heist_contract_objective_values;
    QStringList m_ultimatum_challenge_types;
    QStringList m_ultimatum_reward_types;
    QStringList m_ultimatum_required_items;
    QStringList m_ultimatum_reward_uniques;
    QStringList m_corpse_types;
    QStringList m_foil_variations;
};
