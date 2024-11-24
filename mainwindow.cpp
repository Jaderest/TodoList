#include "mainwindow.h"
#include <QDebug>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    auto *centralWidget = new QWidget(this);
    auto *mainLayout = new QHBoxLayout(centralWidget); // 水平布局

    categoryManager = new CategoryManager(this);
    // 分类管理按钮
    auto *manageCategoriesButton = new QPushButton("分类管理", this);
    mainLayout->addWidget(manageCategoriesButton);

    // 左侧分类框
    categoryListWidget = new QListWidget(this);
    // categoryListWidget->addItems(categoryManager->getCategories());
    updateCategoryList();
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

    // 任务编辑
    auto *editTaskButton = new QPushButton("Edit Task", this);
    taskLayout->addWidget(editTaskButton); // 将按钮添加到主界面布局中
    editTaskButton->setEnabled(false);
    // 信号槽连接：点击按钮时调用 editSelectedTask
    connect(editTaskButton, &QPushButton::clicked, this, &MainWindow::editSelectedTask);
    // 当任务列表中有任务被选中时启用按钮
    connect(taskListWidget, &QListWidget::itemSelectionChanged, this, [this, editTaskButton]() {
        editTaskButton->setEnabled(taskListWidget->currentItem() != nullptr);
    });

    // 任务完成
    auto *finishTaskButton = new QPushButton("Finish Task", this);
    taskLayout->addWidget(finishTaskButton);
    connect(finishTaskButton, &QPushButton::clicked, this, &MainWindow::finishSelectedTask);

    // 任务提醒
    taskReminder = new TaskReminder(this);
    taskReminder->setTasks(tasks);
    connect(taskReminder, &TaskReminder::showReminder, this, &MainWindow::showTaskReminder);

    // 信号槽连接
    connect(addTaskButton, &QPushButton::clicked, this, &MainWindow::openTaskEditor);
    connect(categoryListWidget, &QListWidget::currentTextChanged, this, &MainWindow::filterTasks);
    connect(manageCategoriesButton, &QPushButton::clicked, this, [this]() {
        CategoryManagerDialog dialog(categoryManager, this);
        dialog.exec();
        updateCategoryList();
        // TODO：更新所有任务
        auto categories = categoryManager->getCategories();
        for (auto &task: tasks) {
            if (!categories.contains(task.type)) {
                task.type = "type被删除";
                // qDebug() << "yes";
            }
        }
        updateTaskList(tasks);
    });
}

void MainWindow::openTaskEditor() {
    if (TaskEditor editor(this, categoryManager->getCategories()); editor.exec() == QDialog::Accepted) {
        Task task = editor.getTask();
        tasks.append(task);
        updateTaskList(this->tasks); // 更新显示
    }
}

void MainWindow::filterTasks(const QString &category) {
    filteredTasks.clear();

    if (category == "All") {
        filteredTasks = tasks; // 显示所有任务
    } else if (category == "Today") {
        QDate today = QDate::currentDate();
        for (const Task &task: tasks) {
            if (task.dueTime.date() == today) {
                filteredTasks.append(task);
            }
        }
    } else {
        // 根据分类筛选
        for (const Task &task: tasks) {
            if (task.type == category) {
                filteredTasks.append(task);
            }
        }
    }

    updateTaskList(filteredTasks); // 更新显示
}

void MainWindow::updateTaskList(QList<Task> &tasks) {
    taskListWidget->clear();

    // 现在要排序task
    std::sort(tasks.begin(), tasks.end(), [](const Task &a, const Task &b) {
        if (a.finished != b.finished) {
            return !a.finished;
        }
        return a.dueTime < b.dueTime;
    });

    for (const Task &task: tasks) {
        QString taskText = task.dueTime.toString("yyyy-MM-dd HH:mm") + " - " + task.content + " (" + task.type + ")";
        auto *item = new QListWidgetItem(taskText, taskListWidget);

        // 设置已完成任务的样式
        if (task.finished) {
            item->setForeground(Qt::gray);
            item->setFont(QFont("Arial", 10, QFont::StyleItalic));
        } else {
            item->setForeground(Qt::black);
        }

        taskListWidget->addItem(item);
    }
    taskReminder->setTasks(this->tasks);
}

void MainWindow::updateCategoryList() {
    // 清空分类列表并添加固定分类
    categoryListWidget->clear();
    categoryListWidget->addItem("All");
    categoryListWidget->addItem("Today");

    // 添加用户自定义分类
    QStringList userCategories = categoryManager->getCategories();
    for (const QString &category: userCategories) {
        categoryListWidget->addItem(category);
    }
}

void MainWindow::editSelectedTask() {
    QListWidgetItem *selectedItem = taskListWidget->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "No Task Selected", "Please select a task to edit.");
        return;
    }

    // 找到选中的任务在任务列表中的索引
    int taskIndex = taskListWidget->row(selectedItem);
    Task &selectedTask = tasks[taskIndex]; // 获取对应的任务对象

    // 弹出任务编辑对话框
    TaskEditor editorDialog(this, categoryManager->getCategories());
    editorDialog.setTask(selectedTask); // 将选中的任务传递给编辑器

    if (editorDialog.exec() == QDialog::Accepted) {
        // 更新任务信息
        selectedTask = editorDialog.getTask();

        // 更新任务显示
        updateTaskList(filteredTasks);
    }
}

void MainWindow::finishSelectedTask() {
    // 获取当前选中的任务项
    QListWidgetItem *selectedItem = taskListWidget->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "No Task Selected", "Please select a task to mark as finished.");
        return;
    }

    // 找到选中任务的索引并更新状态
    int taskIndex = taskListWidget->row(selectedItem);
    tasks[taskIndex].finished = true;

    // 刷新任务列表
    updateTaskList(filteredTasks);
}

void MainWindow::showTaskReminder(const QString &taskInfo) {
    ReminderPopup *popup = new ReminderPopup(taskInfo, this);
    popup->setAttribute(Qt::WA_DeleteOnClose); // 关闭后自动释放
    popup->exec();
}
