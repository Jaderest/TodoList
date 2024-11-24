#include "reminderpopup.h"

ReminderPopup::ReminderPopup(const QString &message, QWidget *parent)
    : QDialog(parent) {
    setWindowTitle("Task Reminder");
    setMinimumSize(300, 150);

    messageLabel = new QLabel(message, this);
    messageLabel->setWordWrap(true);

    closeButton = new QPushButton("Close", this);
    connect(closeButton, &QPushButton::clicked, this, &ReminderPopup::accept);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(messageLabel);
    layout->addWidget(closeButton);
}
