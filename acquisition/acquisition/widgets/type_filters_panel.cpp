#include <acquisition/widgets/type_filters_panel.h>

#include <QCheckBox>
#include <QComboBox>
#include <QHboxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

TypeFiltersPanel::TypeFiltersPanel()
{
    QCheckBox* typeFiltersEnabled = new QCheckBox;
    QPushButton* typeFiltersVisible = new QPushButton("Type Filters");

    QHBoxLayout* typeFiltersHeaderLayout = new QHBoxLayout;
    typeFiltersHeaderLayout->addWidget(typeFiltersEnabled);
    typeFiltersHeaderLayout->addWidget(typeFiltersVisible, 1);

    QWidget* typeFiltersHeader = new QWidget;
    typeFiltersHeader->setLayout(typeFiltersHeaderLayout);

    QGridLayout* typeFiltersGrid = new QGridLayout();
    typeFiltersGrid->addWidget(new QLabel("Item Category"), 0, 0);
    typeFiltersGrid->addWidget(new QComboBox(), 0, 1);
    typeFiltersGrid->addWidget(new QLabel("Item Rarity"), 1, 0);
    typeFiltersGrid->addWidget(new QComboBox(), 1, 1);

    QWidget* typeFilters = new QWidget();
    typeFilters->setVisible(false);
    typeFilters->setLayout(typeFiltersGrid);

    connect(typeFiltersEnabled, &QCheckBox::checkStateChanged, this,
        [=](bool checked) {
            typeFiltersVisible->setEnabled(checked);
            typeFilters->setVisible(checked);
        });
    
    connect(typeFiltersVisible, &QPushButton::clicked, this,
        [=]() {
            typeFilters->setVisible(!typeFilters->isVisible());
        });

}