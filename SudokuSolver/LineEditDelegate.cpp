#include "LineEditDelegate.h"

LineEditDelegate::LineEditDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{}

QWidget *LineEditDelegate::createEditor(QWidget *parent,
                                        const QStyleOptionViewItem &,
                                        const QModelIndex &) const
{
    QLineEdit *editor = new QLineEdit(parent);
    // Use constants from Sudoku class for validation range
    QIntValidator *validator = new QIntValidator(Sudoku::MIN_VALUE, Sudoku::MAX_VALUE, editor);
    editor->setValidator(validator);
    editor->setMaxLength(1); // Only allow single digit
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

    if (text.isEmpty()) {
        // Allow clearing the cell
        model->setData(index, QVariant(), Qt::EditRole);
        return;
    }

    bool ok;
    int value = text.toInt(&ok);

    // Use Sudoku class validation constants
    if (ok && value >= Sudoku::MIN_VALUE && value <= Sudoku::MAX_VALUE) {
        model->setData(index, text, Qt::EditRole);
    } else {
        // Clear invalid input
        model->setData(index, QVariant(), Qt::EditRole);
    }
}

void LineEditDelegate::updateEditorGeometry(QWidget *editor,
                                            const QStyleOptionViewItem &option,
                                            const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}

bool LineEditDelegate::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

        // Allow navigation keys to propagate
        static const QList<int> navigationKeys = {
            Qt::Key_Tab, Qt::Key_Left, Qt::Key_Right, Qt::Key_Up, Qt::Key_Down
        };

        if (navigationKeys.contains(keyEvent->key())) {
            return false; // Let the event propagate
        }
    }

    return QStyledItemDelegate::eventFilter(object, event);
}
