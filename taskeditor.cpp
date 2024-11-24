#include "taskeditor.h"

TaskEditor::TaskEditor(QWidget *parent)
    : QDialog(parent)
{
    auto *layout = new QVBoxLayout(this);

    contentEdit = new QLineEdit(this);
    contentEdit->setPlaceholderText("Task content");
    layout->addWidget(contentEdit);

    timeEdit = new QDateTimeEdit(QDateTime::currentDateTime(), this);
    layout->addWidget(timeEdit);

    typeCombo = new QComboBox(this);
    typeCombo->addItems({"Work", "Life", "Study"}); // 可自定义类型
    layout->addWidget(typeCombo);

    auto *buttonLayout = new QHBoxLayout();
    auto *saveButton = new QPushButton("Save", this);
    auto *cancelButton = new QPushButton("Cancel", this);
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
