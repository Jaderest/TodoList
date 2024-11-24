#ifndef TASKREMINDER_H
#define TASKREMINDER_H

#include <QObject>
#include <QTimer>
#include <QDateTime>
#include <QList>
#include "task.h"

class TaskReminder : public QObject {
    Q_OBJECT

public:
    explicit TaskReminder(QObject *parent = nullptr);

    void setTasks(const QList<Task> &tasks); // 设置任务列表

    signals:
        void showReminder(const QString &taskInfo); // 提醒信号

    public slots:
        void checkTasks(); // 检查任务

private:
    QTimer *timer;
    QList<Task> tasks;
};


#endif // TASKREMINDER_H
