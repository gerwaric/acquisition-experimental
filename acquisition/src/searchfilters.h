#pragma once

#include <libacq/model/iteminfo.h>

#include <QObject>
#include <QQmlEngine>

class ProxyModel;
class MinFilter;
class MaxFilter;

using FilterFunction = std::function<bool(const ItemInfo& item_info)>;

struct WeaponsFilters : public QObject {
    Q_OBJECT
    QML_ELEMENT
public:

};

struct RequirementFilters: public QObject {
    Q_OBJECT
    Q_PROPERTY(MinFilter* minLevel MEMBER m_level_min CONSTANT);
    Q_PROPERTY(MaxFilter* maxLevel MEMBER m_level_max CONSTANT);
    Q_PROPERTY(MinFilter* minStrength MEMBER m_strength_min CONSTANT);
    Q_PROPERTY(MaxFilter* maxStrength MEMBER m_strength_max CONSTANT);
    Q_PROPERTY(MinFilter* minDexterity MEMBER m_dexterity_min CONSTANT);
    Q_PROPERTY(MaxFilter* maxDexterity MEMBER m_dexterity_max CONSTANT);
    Q_PROPERTY(MinFilter* minIntelligence MEMBER m_intelligence_min CONSTANT);
    Q_PROPERTY(MaxFilter* maxIntelligence MEMBER m_intelligence_max CONSTANT);
    QML_ELEMENT
public:
    RequirementFilters(ProxyModel& model, QObject* parent);
private:
    MinFilter* m_level_min;
    MaxFilter* m_level_max;
    MinFilter* m_strength_min;
    MaxFilter* m_strength_max;
    MinFilter* m_dexterity_min;
    MaxFilter* m_dexterity_max;
    MinFilter* m_intelligence_min;
    MaxFilter* m_intelligence_max;
};

class SearchFilters : public QObject {
    Q_OBJECT
    Q_PROPERTY(QStringList itemCategories MEMBER s_item_categories CONSTANT);
    Q_PROPERTY(QStringList itemRarities MEMBER s_item_rarities CONSTANT);
    Q_PROPERTY(QStringList characterClasses MEMBER s_character_classes CONSTANT);
    Q_PROPERTY(QStringList mapSeries MEMBER s_map_series CONSTANT);
    Q_PROPERTY(QStringList mapCompletionRewards MEMBER s_map_completion_rewards CONSTANT);
    Q_PROPERTY(QStringList heistContractObjectiveValues MEMBER s_heist_contract_objective_values CONSTANT);
    Q_PROPERTY(QStringList ultimatumChallengeTypes MEMBER s_ultimatum_challenge_types CONSTANT);
    Q_PROPERTY(QStringList ultimatumRewardTypes MEMBER s_ultimatum_reward_types CONSTANT);
    Q_PROPERTY(QStringList ultimatumRequiredItems MEMBER s_ultimatum_required_items CONSTANT);
    Q_PROPERTY(QStringList ultimatumRewardUniques MEMBER s_ultimatum_reward_uniques CONSTANT);
    Q_PROPERTY(QStringList corpseTypes MEMBER s_corpse_types CONSTANT);
    Q_PROPERTY(QStringList foilVariations MEMBER s_foil_variations CONSTANT);
    Q_PROPERTY(RequirementFilters* requirements MEMBER m_requirements CONSTANT);
    QML_ELEMENT

public:
    SearchFilters(ProxyModel& model, QObject* parent);

    enum class Filter {
        // Type Filters
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

    RequirementFilters* m_requirements;

    static const QStringList s_item_categories;
    static const QStringList s_item_rarities;
    static const QStringList s_character_classes;
    static const QStringList s_map_series;
    static const QStringList s_map_completion_rewards;
    static const QStringList s_heist_contract_objective_values;
    static const QStringList s_ultimatum_challenge_types;
    static const QStringList s_ultimatum_reward_types;
    static const QStringList s_ultimatum_required_items;
    static const QStringList s_ultimatum_reward_uniques;
    static const QStringList s_corpse_types;
    static const QStringList s_foil_variations;
};
