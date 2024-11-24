#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QDateTime>

struct Task {
    QString content;
    QDateTime dueTime;
    QString type; // 任务性质
};

#endif // TASK_H
