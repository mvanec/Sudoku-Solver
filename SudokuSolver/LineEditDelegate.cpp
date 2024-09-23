#include "LineEditDelegate.h"

LineEditDelegate::LineEditDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{}

QWidget *LineEditDelegate::createEditor(QWidget *parent,
                                        const QStyleOptionViewItem &,
                                        const QModelIndex &) const
{
    QLineEdit *editor = new QLineEdit(parent);
    QIntValidator *validator = new QIntValidator(1, 9, editor); // Set range 1-9
    editor->setValidator(validator);
    return editor;
}

void LineEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();
    QLineEdit *lineEdit = static_cast<QLineEdit *>(editor);
    lineEdit->setText(value);
}

void LineEditDelegate::setModelData(QWidget *editor,
                                    QAbstractItemModel *model,
                                    const QModelIndex &index) const
{
    QLineEdit *lineEdit = static_cast<QLineEdit *>(editor);
    QString text = lineEdit->text();
    bool ok;
    int value = text.toInt(&ok);

    if (ok && value >= 1 && value <= 9) {
        model->setData(index, text, Qt::EditRole);
    } else {
        // Optionally, reset to a default value or clear the cell
        // Here, we'll reset to "1" if the input is invalid
        model->setData(index, QVariant(), Qt::EditRole);
    }
}

void LineEditDelegate::updateEditorGeometry(QWidget *editor,
                                            const QStyleOptionViewItem &option,
                                            const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}
