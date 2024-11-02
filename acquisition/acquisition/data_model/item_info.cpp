#include <acquisition/data_model/item_info.h>

#include <QsLog/QsLog.h>

ItemInfo::ItemInfo(const poe_api::Item& item)
{
    item_rarity = item.frameType;

    loadSockets(item);
    loadProperties(item);
    loadRequirements(item);

    //bool transigured_gem;
    vaal_gem = (item.hybrid) ? item.hybrid.value().isVaalGem.value_or(false) : false;
    //QString corpse_type;
    crucible_item = item.crucible.has_value();
    fractured_item = item.fractured.value_or(false);
    synthesised_item = item.synthesised.value_or(false);
    searing_exarch_item = item.searing.value_or(false);
    eater_of_worlds_item = item.tangled.value_or(false);
    identified = item.identified;
    corrupted = item.corrupted.value_or(false);
    //bool mirrored;
    split = item.split.value_or(false);
    crafted = item.craftedMods.has_value();
    veiled = item.veiled.value_or(false);
    forseeing = item.foreseeing.value_or(false);
    talisman_tier = item.talismanTier.value_or(0);
    //int stored_experience;
    stack_size = item.stackSize.value_or(0);
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
        while (group >= socket_groups.size()) {
            socket_groups.push_back(SocketGroup());
        };
        const QString& colour = socket.sColour.value_or("");
        if      (colour == "R") { ++red_sockets; ++socket_groups[group].red; }
        else if (colour == "G") { ++green_sockets; ++socket_groups[group].green; }
        else if (colour == "B") { ++blue_sockets; ++socket_groups[group].blue; }
        else if (colour == "W") { ++white_sockets; ++socket_groups[group].white; }
        else {
            QLOG_ERROR() << "Unhandled item socket:" << colour << "in" << item.name << item.typeLine;
        };
        ++sockets;
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
                    gem_level = value.left(value.indexOf(" ")).toInt(&ok);
                } else {
                    gem_level = value.toInt(&ok);
                };
                break;
            case static_cast<int>(PropertyType::Quality):
                quality = value.sliced(1, value.size()-2).toInt(&ok);
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
                critical_chance = value.chopped(1).toFloat(&ok);
                break;
            case static_cast<int>(PropertyType::AttacksPerSecond):
                attacks_per_second = value.toFloat(&ok);
                break;
            case static_cast<int>(PropertyType::ChanceToBlock):
                block = value.chopped(1).toInt(&ok);
                break;
            case static_cast<int>(PropertyType::Armour):
                armour = value.toInt(&ok);
                break;
            case static_cast<int>(PropertyType::EvasionRating):
                evasion = value.toInt(&ok);
                break;
            case static_cast<int>(PropertyType::EnergyShield):
                energy_shield = value.toInt(&ok);
                break;
            case static_cast<int>(PropertyType::Ward):
                ward = value.toInt(&ok);
                break;
            case static_cast<int>(PropertyType::StackSize):
                stack_size = value.split("/")[0].toInt(&ok);
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
    physical_dps = average_physical_damage * attacks_per_second;
    elemental_dps = average_elemental_damage * attacks_per_second;
    chaos_dps = average_chaos_damage * attacks_per_second;
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
                required_level = value.toInt(&ok);
                break;
            case static_cast<int>(RequirementType::Strength):
                required_strength = value.toInt(&ok);
                break;
            case static_cast<int>(RequirementType::Dexterity):
                required_dexterity = value.toInt(&ok);
                break;
            case static_cast<int>(RequirementType::Intelligence):
                required_intelligence = value.toInt(&ok);
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

float ItemInfo::averageValue(const QString& property, bool* ok)
{
    const QStringList parts = property.split("-");
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
