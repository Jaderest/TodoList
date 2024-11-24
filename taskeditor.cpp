#include "taskeditor.h"

TaskEditor::TaskEditor(QWidget *parent, const QStringList &texts)
    : QDialog(parent)
{
    setWindowTitle("task");
    auto *layout = new QVBoxLayout(this);

    // 内容编辑
    contentEdit = new QLineEdit(this);
    contentEdit->setPlaceholderText("内容");
    layout->addWidget(contentEdit);

    // 时间编辑
    timeEdit = new QDateTimeEdit(QDateTime::currentDateTime(), this);
    layout->addWidget(timeEdit);

    // 类型选择
    typeCombo = new QComboBox(this);
    typeCombo->addItems(texts); // 可自定义类型
    layout->addWidget(typeCombo);

    auto *buttonLayout = new QHBoxLayout();
    auto *saveButton = new QPushButton("保存", this);
    auto *cancelButton = new QPushButton("取消", this);
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);

    layout->addLayout(buttonLayout);

    connect(saveButton, &QPushButton::clicked, this, &TaskEditor::accept);
    connect(cancelButton, &QPushButton::clicked, this, &TaskEditor::reject);
}

Task TaskEditor::getTask() const {
    return {
        contentEdit->text(),
        timeEdit->dateTime(),
        typeCombo->currentText()
    };
}

void TaskEditor::setTask(const Task &task) {
    //TODO 研究下这个怎么弄
    contentEdit->setText(task.content);
    timeEdit->setDateTime(task.dueTime);
    typeCombo->setCurrentText(task.type);
}