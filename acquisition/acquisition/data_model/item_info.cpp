#include <acquisition/data_model/item_info.h>

#include <QsLog/QsLog.h>

ItemInfo::WeaponInfo::WeaponInfo(const poe_api::Item& item)
{
    if (!item.properties) {
        QLOG_ERROR() << "Tried get weapon info for an item without properties";
        return;
    };
}

ItemInfo::ArmourInfo::ArmourInfo(const poe_api::Item& item)
{
    if (!item.properties) {
        QLOG_ERROR() << "Tried get armour info for an item without properties";
    };
    for (const auto& prop : item.properties.value()) {
        if (prop.name == "Armour") {
        } else if (prop.name == "Energy Shield") {
        } else if (prop.name == "Evasion Rating") {
        } else if (prop.name == "Chance to Block") {
        } else if (prop.name == "Ward") {
        };
    };
}
