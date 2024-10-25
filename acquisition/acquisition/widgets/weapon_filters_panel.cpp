#include <acquisition/widgets/weapon_filters_panel.h>

#include <acquisition/widgets/text_search_field.h>

#include <QGridLayout>
#include <QLabel>
#include <QTextEdit>

WeaponFiltersPanel::WeaponFiltersPanel(QWidget* parent)
    : FiltersPanel("Weapon Filters", parent)
{

    int row = 0;
    m_layout->addWidget(new QLabel("Damage", this), row, 0);
    m_layout->addWidget(new TextSearchField("Min", this), row, 1);
    m_layout->addWidget(new TextSearchField("Max", this), row, 2);

    ++row;
    m_layout->addWidget(new QLabel("Critical Chance", this), row, 0);
    m_layout->addWidget(new TextSearchField("Min", this), row, 1);
    m_layout->addWidget(new TextSearchField("Max", this), row, 2);


    ++row;
    m_layout->addWidget(new QLabel("Physical DPS", this), row, 0);
    m_layout->addWidget(new TextSearchField("Min", this), row, 1);
    m_layout->addWidget(new TextSearchField("Max", this), row, 2);

    ++row;
    m_layout->addWidget(new QLabel("Attacks per Second", this), row, 0);
    m_layout->addWidget(new TextSearchField("Min", this), row, 1);
    m_layout->addWidget(new TextSearchField("Max", this), row, 2);

    ++row;
    m_layout->addWidget(new QLabel("Damage per Second", this), row, 0);
    m_layout->addWidget(new TextSearchField("Min", this), row, 1);
    m_layout->addWidget(new TextSearchField("Max", this), row, 2);

    ++row;
    m_layout->addWidget(new QLabel("Elemental DPS", this), row, 0);
    m_layout->addWidget(new TextSearchField("Min", this), row, 1);
    m_layout->addWidget(new TextSearchField("Max", this), row, 2);
}