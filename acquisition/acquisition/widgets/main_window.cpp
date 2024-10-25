#include <acquisition/widgets/main_window.h>

#include <acquisition/acquisition.h>
#include <acquisition/widgets/type_filters_panel.h>
#include <acquisition/widgets/weapon_filters_panel.h>

#include <QCheckBox>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QMenuBar>
#include <QPushButton>
#include <QScrollArea>
#include <QStatusBar>
#include <QTreeView>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(Acquisition& acquisition)
    : m_acquisition(acquisition)
{
    setMenuBar(new QMenuBar);
    setStatusBar(new QStatusBar);

    QVBoxLayout* search_layout = new QVBoxLayout;
    search_layout->addWidget(new TypeFiltersPanel(this));
    search_layout->addWidget(new WeaponFiltersPanel(this));
    search_layout->addStretch();

    QScrollArea* search_scroll = new QScrollArea(this);
    search_scroll->setLayout(search_layout);
    search_scroll->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QTreeView* results_view = new QTreeView(this);
    results_view->setModel(acquisition.treeModel());

    setCentralWidget(new QWidget(this));
    centralWidget()->setLayout(new QHBoxLayout);
    centralWidget()->layout()->addWidget(search_scroll);
    centralWidget()->layout()->addWidget(results_view);
}

