#pragma once

#include <QIntValidator>
#include <QLineEdit>
#include <QStyledItemDelegate>
#include <QKeyEvent>
#include <QWidget>

class LineEditDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit LineEditDelegate(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;

protected:
    // Event filter to allow navigation with Tab and Arrow keys
    bool eventFilter(QObject *object, QEvent *event) override;
};
