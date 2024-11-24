#include "taskreminder.h"
#include <QDebug>

TaskReminder::TaskReminder(QObject *parent)
    : QObject(parent), timer(new QTimer(this)) {
    connect(timer, &QTimer::timeout, this, &TaskReminder::checkTasks);
    timer->start(60000); // 每分钟检查一次
}

void TaskReminder::setTasks(const QList<Task> &tasks) {
    this->tasks = tasks;
}

void TaskReminder::checkTasks() {
    QDateTime now = QDateTime::currentDateTime();
    QDateTime oneDayLater = now.addDays(1);

    for (const Task &task : tasks) {
        // 检查是否正好在一天后（误差1分钟）
        qint64 timeDiff = task.dueTime.toSecsSinceEpoch() - oneDayLater.toSecsSinceEpoch();
        if (std::abs(timeDiff) <= 60 && !task.finished) {
            QString taskInfo = QString("Task: %1\nDue: %2\nType: %3")
                .arg(task.content)
                .arg(task.dueTime.toString("yyyy-MM-dd HH:mm"))
                .arg(task.type);
            emit showReminder(taskInfo); // 发送提醒信号
        }
    }
}
