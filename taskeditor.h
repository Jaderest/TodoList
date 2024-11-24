#ifndef TASKEDITOR_H
#define TASKEDITOR_H

#include <QObject>
#include <QDialog>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QComboBox>
#include <QPushButton>
#include "task.h"

class TaskEditor : public QDialog
{
    Q_OBJECT
public:
    TaskEditor(QWidget *parent = nullptr);

    Task getTask() const;

private:
    QLineEdit *contentEdit{};
    QDateTimeEdit *timeEdit{};
    QComboBox *typeCombo{};
};

#endif // TASKEDITOR_H
