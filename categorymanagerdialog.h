#ifndef CATEGORYMANAGERDIALOG_H
#define CATEGORYMANAGERDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include "CategoryManager.h"

class CategoryManagerDialog : public QDialog {
    Q_OBJECT

public:
    explicit CategoryManagerDialog(CategoryManager *manager, QWidget *parent = nullptr);

    private slots:
        void addCategory();       // 添加分类
    void deleteSelected();    // 删除选中分类
    void updateCategoryList(); // 更新分类列表

private:
    CategoryManager *categoryManager;
    QListWidget *categoryListWidget;
    QLineEdit *categoryInput;
    QPushButton *addButton;
    QPushButton *deleteButton;
};

#endif // CATEGORYMANAGERDIALOG_H
