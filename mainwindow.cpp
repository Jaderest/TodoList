#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    auto *centralWidget = new QWidget(this);
    auto *mainLayout = new QHBoxLayout(centralWidget); // 水平布局

    // 左侧分类框
    categoryListWidget = new QListWidget(this);
    categoryListWidget->addItems({"All", "我的一天","Work", "Life", "Study"});
    categoryListWidget->setCurrentRow(0); // 默认选中 "All"
    mainLayout->addWidget(categoryListWidget);

    // 右侧任务显示
    auto *taskLayout = new QVBoxLayout();
    taskListWidget = new QListWidget(this);
    taskLayout->addWidget(taskListWidget);

    auto *addTaskButton = new QPushButton("Add Task", this);
    taskLayout->addWidget(addTaskButton);

    mainLayout->addLayout(taskLayout);
    setCentralWidget(centralWidget);

    // 信号槽连接
    connect(addTaskButton, &QPushButton::clicked, this, &MainWindow::openTaskEditor);
    connect(categoryListWidget, &QListWidget::currentTextChanged, this, &MainWindow::filterTasks);
}

void MainWindow::openTaskEditor() {
    TaskEditor editor(this);
    if (editor.exec() == QDialog::Accepted) {
        Task task = editor.getTask();
        tasks.append(task);
        updateTaskList(this->tasks); // 更新显示
    }
}

void MainWindow::filterTasks(const QString &category) {
    filteredTasks.clear();

    if (category == "All") {
        filteredTasks = tasks; // 显示所有任务
    } else if (category == "我的一天") {
        QDate today = QDate::currentDate();
        for (const Task &task : tasks) {
            if (task.dueTime.date() == today) {
                filteredTasks.append(task);
            }
        }
    } else {
        // 根据分类筛选
        for (const Task &task : tasks) {
            if (task.type == category) {
                filteredTasks.append(task);
            }
        }
    }

    updateTaskList(filteredTasks); // 更新显示
}

void MainWindow::updateTaskList(QList<Task> &tasks) {
    taskListWidget->clear();
    for (const Task &task : tasks) {
        taskListWidget->addItem(task.dueTime.toString("yyyy-MM-dd HH:mm") + " - " + task.content + " (" + task.type + ")");
    }
}
