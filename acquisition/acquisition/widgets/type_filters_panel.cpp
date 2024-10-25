#include <acquisition/widgets/type_filters_panel.h>

#include <QCheckBox>
#include <QComboBox>
#include <QGridLayout>
#include <QHboxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

TypeFiltersPanel::TypeFiltersPanel(QWidget* parent)
    : FiltersPanel("Type Filters", parent)
{
    m_layout->addWidget(new QLabel("Item Category", this), 0, 0);
    m_layout->addWidget(new QComboBox(this), 0, 1);
    m_layout->addWidget(new QLabel("Item Rarity", this), 1, 0);
    m_layout->addWidget(new QComboBox(this), 1, 1);
}