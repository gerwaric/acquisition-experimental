#pragma once

#include <QTextEdit>

class TextSearchField : public QTextEdit {
    Q_OBJECT
public:
    TextSearchField(const QString& placeholder, QWidget* parent = nullptr);
};