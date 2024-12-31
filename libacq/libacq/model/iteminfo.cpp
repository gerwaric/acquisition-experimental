#include <libacq/model/iteminfo.h>

#include <QsLog/QsLog.h>

ItemInfo::ItemInfo(const poe_api::Item& item)
{
    m_item_rarity = item.frameType;

    loadSockets(item);
    loadProperties(item);
    loadRequirements(item);

    //bool transigured_gem;
    m_vaal_gem = (item.hybrid) ? item.hybrid.value().isVaalGem.value_or(false) : false;
    //QString corpse_type;
    m_crucible_item = item.crucible.has_value();
    m_fractured_item = item.fractured.value_or(false);
    m_synthesised_item = item.synthesised.value_or(false);
    m_searing_exarch_item = item.searing.value_or(false);
    m_eater_of_worlds_item = item.tangled.value_or(false);
    m_identified = item.identified;
    m_corrupted = item.corrupted.value_or(false);
    //bool mirrored;
    m_split = item.split.value_or(false);
    m_crafted = item.craftedMods.has_value();
    m_veiled = item.veiled.value_or(false);
    m_forseeing = item.foreseeing.value_or(false);
    m_talisman_tier = item.talismanTier.value_or(0);
    //int stored_experience;
    m_stack_size = item.stackSize.value_or(0);
    //QString alternate_art;
    //QString foil_variation;
    //int scourge_tier;

}

void ItemInfo::loadSockets(const poe_api::Item& item)
{
    if (!item.sockets) {
        return;
    };
    for (const auto& socket : item.sockets.value()) {
        const unsigned int group = socket.group;
        while (group >= m_socket_groups.size()) {
            m_socket_groups.push_back(SocketGroup());
        };
        const QString& colour = socket.sColour.value_or("");
        if      (colour == "R") { ++m_red_sockets; ++m_socket_groups[group].red; }
        else if (colour == "G") { ++m_green_sockets; ++m_socket_groups[group].green; }
        else if (colour == "B") { ++m_blue_sockets; ++m_socket_groups[group].blue; }
        else if (colour == "W") { ++m_white_sockets; ++m_socket_groups[group].white; }
        else {
            QLOG_ERROR() << "Unhandled item socket:" << colour << "in" << item.name << item.typeLine;
        };
        ++m_sockets;
    };
}

void ItemInfo::loadProperties(const poe_api::Item& item)
{
    if (!item.properties) {
        return;
    };
    float average_physical_damage = 0.0;
    float average_elemental_damage = 0.0;
    float average_chaos_damage = 0.0;
    for (const auto& property : item.properties.value()) {
        if (!property.type) {
            continue;
        };
        bool ok = false;
        const int type = property.type.value();
        const QString& name = property.name;
        const QString value = std::get<0>(property.values[0]);
        switch (type) {
            case static_cast<int>(PropertyType::Level):
                if (value.contains(" ")) {
                    m_gem_level = value.left(value.indexOf(" ")).toInt(&ok);
                } else {
                    m_gem_level = value.toInt(&ok);
                };
                break;
            case static_cast<int>(PropertyType::Quality):
                m_quality = value.sliced(1, value.size()-2).toInt(&ok);
                break;
            case static_cast<int>(PropertyType::PhysicalDamage):
                average_physical_damage = averageValue(value, &ok);
                break;
            case static_cast<int>(PropertyType::ElementalDamage):
                average_elemental_damage = averageValue(value, &ok);
                break;
            case static_cast<int>(PropertyType::ChaosDamage):
                average_chaos_damage = averageValue(value, &ok);
                break;
            case static_cast<int>(PropertyType::CriticalStrikeChance):
                m_critical_chance = value.chopped(1).toFloat(&ok);
                break;
            case static_cast<int>(PropertyType::AttacksPerSecond):
                m_attacks_per_second = value.toFloat(&ok);
                break;
            case static_cast<int>(PropertyType::ChanceToBlock):
                m_block = value.chopped(1).toInt(&ok);
                break;
            case static_cast<int>(PropertyType::Armour):
                m_armour = value.toInt(&ok);
                break;
            case static_cast<int>(PropertyType::EvasionRating):
                m_evasion_rating = value.toInt(&ok);
                break;
            case static_cast<int>(PropertyType::EnergyShield):
                m_energy_shield = value.toInt(&ok);
                break;
            case static_cast<int>(PropertyType::Ward):
                m_ward = value.toInt(&ok);
                break;
            case static_cast<int>(PropertyType::StackSize):
                m_stack_size = value.split("/")[0].toInt(&ok);
                break;
            case static_cast<int>(PropertyType::MapTier):
            case static_cast<int>(PropertyType::ItemQuantity):
            case static_cast<int>(PropertyType::ItemRarity):
            case static_cast<int>(PropertyType::MonsterPackSize):
            case static_cast<int>(PropertyType::AreaLevel):
            case static_cast<int>(PropertyType::Radius):
            case static_cast<int>(PropertyType::Requires):
            case static_cast<int>(PropertyType::HeistTarget):
            case static_cast<int>(PropertyType::WeaponRange):
            case static_cast<int>(PropertyType::Limit):
            case static_cast<int>(PropertyType::MoreMaps):
            case static_cast<int>(PropertyType::MoreScarabs):
                ok = true;
                break;
            default:
                QLOG_ERROR() << "Unhandled property:" << type << name;
                break;
        };
        if (!ok) {
            QLOG_ERROR() << "Error loading property" << name << "from" << value;
        };
    };
    m_physical_dps = average_physical_damage * m_attacks_per_second;
    m_elemental_dps = average_elemental_damage * m_attacks_per_second;
    m_chaos_dps = average_chaos_damage * m_attacks_per_second;
}

void ItemInfo::loadRequirements(const poe_api::Item& item)
{
    if (!item.requirements) {
        return;
    };
    for (const auto& requirement : item.requirements.value()) {
        bool ok = false;
        const int type = requirement.type.value();
        const QString& name = requirement.name;
        const QString value = std::get<0>(requirement.values[0]);
        switch (type) {
            case static_cast<int>(RequirementType::Level):
                m_required_level = value.toInt(&ok);
                break;
            case static_cast<int>(RequirementType::Strength):
                m_required_strength = value.toInt(&ok);
                break;
            case static_cast<int>(RequirementType::Dexterity):
                m_required_dexterity = value.toInt(&ok);
                break;
            case static_cast<int>(RequirementType::Intelligence):
                m_required_intelligence = value.toInt(&ok);
                break;
            //case static_cast<int>(RequirementType::Class):
            //    required_class = value;
            //    break;
            default:
                QLOG_WARN() << "Unhandled requirement:" << type << name;
                break;
        };
        if (!ok) {
            QLOG_ERROR() << "Error loading requirement" << name << "from" << value;
        };
   };
}

float ItemInfo::averageValue(const QString& ranged_value, bool* ok)
{
    const QStringList parts = ranged_value.split("-");
    if (parts.size() == 2) {
        bool ok_a = false;
        bool ok_b = false;
        const int a = parts[0].toInt(&ok_a);
        const int b = parts[1].toInt(&ok_b);
        if (ok_a && ok_b) {
            *ok = true;
            return float(a + b) / 2.0;
        };
    };
    *ok = false;
    return 0;
};
