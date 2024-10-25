#include <acquisition/widgets/filters_panel.h>

#include <QCheckBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>

FiltersPanel::FiltersPanel(const QString& title, QWidget* parent)
    : QWidget(parent)
{
    setObjectName(title);
    m_enabled = new QCheckBox(this);
    m_visible = new QPushButton(title, this);
    m_layout = new QGridLayout(this);

    m_layout->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout* header_layout = new QHBoxLayout;
    header_layout->addWidget(m_enabled);
    header_layout->addWidget(m_visible, 1);

    QWidget* header = new QWidget(this);
    header->setLayout(header_layout);

    QWidget* content = new QWidget(this);
    content->setLayout(m_layout);
    content->setVisible(false);

    connect(m_enabled, &QCheckBox::checkStateChanged, this,
        [=](bool checked) {
            m_visible->setEnabled(checked);
            content->setVisible(checked);
        });

    connect(m_visible, &QPushButton::clicked, this,
        [=]() {
            content->setVisible(!content->isVisible());
        });

    setLayout(new QVBoxLayout);
    layout()->addWidget(header);
    layout()->addWidget(content);
}