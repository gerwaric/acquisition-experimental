#pragma once

#include <acquisition/widgets/filters_panel.h>

class WeaponFiltersPanel : public FiltersPanel {
    Q_OBJECT
public:
    WeaponFiltersPanel(QWidget* parent = nullptr);
    virtual ~WeaponFiltersPanel() {};
};