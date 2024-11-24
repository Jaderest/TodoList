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
    TaskEditor(QWidget *parent = nullptr, const QStringList &texts = {});

    Task getTask() const;

    void setTask(const Task &task);

private:
    QLineEdit *contentEdit{};
    QDateTimeEdit *timeEdit{};
    QComboBox *typeCombo{};
};

#endif // TASKEDITOR_H
