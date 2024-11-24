#ifndef REMINDERPOPUP_H
#define REMINDERPOPUP_H

#include <QObject>

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

class ReminderPopup : public QDialog {
    Q_OBJECT

public:
    explicit ReminderPopup(const QString &message, QWidget *parent = nullptr);

private:
    QLabel *messageLabel;
    QPushButton *closeButton;
};

#endif // REMINDERPOPUP_H
