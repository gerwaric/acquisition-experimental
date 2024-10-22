#pragma once

#include <QCheckBox>
#include <QPushButton>
#include <QWidget>

class FiltersPanel : public QWidget {
    Q_OBJECT
public:
    FiltersPanel();

    std::unique_ptr<QCheckBox> m_enabled;
    std::unique_ptr<QPushButton> m_visible;
    std::unique_ptr<QWidget> m_contents;
};