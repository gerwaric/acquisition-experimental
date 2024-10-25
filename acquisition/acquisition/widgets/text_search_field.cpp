#include <acquisition/widgets/text_search_field.h>

#include <QSizePolicy>

TextSearchField::TextSearchField(const QString& placeholder, QWidget* parent)
    : QTextEdit(parent)
{
    setPlaceholderText(placeholder);
}