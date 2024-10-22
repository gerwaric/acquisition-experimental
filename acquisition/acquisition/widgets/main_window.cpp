#include <acquisition/widgets/main_window.h>

#include <acquisition/acquisition.h>

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
    

    QScrollArea* searchFilters = new QScrollArea;
    QVBoxLayout* searchFiltersLayout = new QVBoxLayout;
    searchFilters->setLayout(searchFiltersLayout);
    searchFiltersLayout->addWidget(typeFiltersHeader);
    searchFiltersLayout->addWidget(typeFilters);
    searchFiltersLayout->addStretch();

    QTreeView* searchResults = new QTreeView;
    searchResults->setModel(acquisition.treeModel());

    setCentralWidget(new QWidget);
    centralWidget()->setLayout(new QHBoxLayout);
    centralWidget()->layout()->addWidget(searchFilters);
    centralWidget()->layout()->addWidget(searchResults);
}

