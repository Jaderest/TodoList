#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QList>

#include "task.h"
#include "taskeditor.h"
#include "categorymanager.h"
#include "categorymanagerdialog.h"
#include "taskreminder.h"
#include "reminderpopup.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void openTaskEditor();
    void editSelectedTask();
    void finishSelectedTask();
    void showTaskReminder(const QString &taskInfo);

private:
    QList<Task> tasks;            // 所有任务
    QList<Task> filteredTasks;    // 当前筛选后的任务
    QListWidget *taskListWidget;  // 右侧任务显示
    QListWidget *categoryListWidget; // 左侧分类框
    CategoryManager *categoryManager;
    TaskReminder *taskReminder;
    // QString currentCategory;      // 当前分类

    void updateTaskList(QList<Task> &tasks);
    void filterTasks(const QString &category);

    void updateCategoryList();
};

#endif // MAINWINDOW_H
