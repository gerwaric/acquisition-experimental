#pragma once

#include <QWidget>

class QCheckBox;
class QPushButton;
class QGridLayout;

class FiltersPanel : public QWidget {
    Q_OBJECT
public:
    FiltersPanel(const QString& title, QWidget* parent = nullptr);
    virtual ~FiltersPanel() {};

protected:
    QGridLayout* m_layout;

private:
    QCheckBox* m_enabled;
    QPushButton* m_visible;
};