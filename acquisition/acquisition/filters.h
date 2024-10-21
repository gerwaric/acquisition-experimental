#pragma once

#include <QObject>
//#include <QQmlEngine>

class Filter : public QObject {
    Q_OBJECT
    //Q_PROPERTY(QStringList itemCategories MEMBER m_item_categories CONSTANT);
    //Q_PROPERTY(QStringList itemRarities MEMBER m_item_rarities CONSTANT);
    //Q_PROPERTY(QStringList characterClasses MEMBER m_character_classes CONSTANT);
    //Q_PROPERTY(QStringList mapSeries MEMBER m_map_series CONSTANT);
    //Q_PROPERTY(QStringList mapCompletionRewards MEMBER m_map_completion_rewards CONSTANT);
    //Q_PROPERTY(QStringList heistContractObjectiveValues MEMBER m_heist_contract_objective_values CONSTANT);
    //Q_PROPERTY(QStringList ultimatumChallengeTypes MEMBER m_ultimatum_challenge_types CONSTANT);
    //Q_PROPERTY(QStringList ultimatumRewardTypes MEMBER m_ultimatum_reward_types CONSTANT);
    //Q_PROPERTY(QStringList ultimatumRequiredItems MEMBER m_ultimatum_required_items CONSTANT);
    //Q_PROPERTY(QStringList ultimatumRewardUniques MEMBER m_ultimatum_reward_uniques CONSTANT);
    //Q_PROPERTY(QStringList corpseTypes MEMBER m_corpse_types CONSTANT);
    //Q_PROPERTY(QStringList foilVariations MEMBER m_foil_variations CONSTANT);
    //QML_ELEMENT
    //QML_SINGLETON

public:
    Filter(QObject* parent = nullptr);

    enum class Type {
        Category,
        Rarity
    };
    Q_ENUM(Type)

    enum class Weapon {
        DamageMin,
        DamageMax,
        CriticalChanceMin,
        CriticalChanceMax,
        AttacksPerSecondMin,
        AttacksPerSecondMax,
        DamagePerSecondMin,
        DamagePerSecondMax,
        ElementalDpsMin,
        ElementalDpsMax
    };
    Q_ENUM(Weapon)

    enum class Armour {
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
        BasePercentileMax
    };
    Q_ENUM(Armour)

    enum class Socket {
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
        LinksMax
    };
    Q_ENUM(Socket)

    enum class Requirements {
        LevelMin,
        LevelMax,
        StrengthMin,
        StrengthMax,
        DexterityMin,
        DexterityMax,
        IntelligenceMin,
        IntelligenceMax,
        CharacterClass
    };
    Q_ENUM(Requirements)

    enum class MapFilters {
        MapTier,
        MapPacksize,
        MapIIR,
        MapIIQ,
        AreaLevel,
        MapSeries,
        BlightedMap,
        BlightRavagedMap,
        MapCompletionReward
    };
    Q_ENUM(MapFilters)

    enum class HeistFilters {
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
        EngineeringLevel
    };
    Q_ENUM(HeistFilters)

    enum class SanctumFilters {
        Resolve,
        MaximumResolve,
        Inspiration,
        Aureus
    };
    Q_ENUM(SanctumFilters)

    enum class UltimatumFilters {
        ChallengeType,
        RewardType,
        RequiredItem,
        RewardUnique
    };
    Q_ENUM(UltimatumFilters)

    enum class Miscelanneous  {
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
        ScourgeTier
    };
    Q_ENUM(Miscelanneous)

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
