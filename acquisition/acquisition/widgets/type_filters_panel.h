#pragma once

#include <acquisition/widgets/filters_panel.h>

class TypeFiltersPanel : public FiltersPanel {
    Q_OBJECT
public:
    TypeFiltersPanel(QWidget* parent = nullptr);
    virtual ~TypeFiltersPanel() {};
};