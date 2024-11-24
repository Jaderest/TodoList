#include "CategoryManagerDialog.h"

CategoryManagerDialog::CategoryManagerDialog(CategoryManager *manager, QWidget *parent)
    : QDialog(parent), categoryManager(manager) {
    setWindowTitle("分类管理");

    auto *layout = new QVBoxLayout(this);

    categoryListWidget = new QListWidget(this);
    layout->addWidget(categoryListWidget);

    auto *inputLayout = new QHBoxLayout();
    categoryInput = new QLineEdit(this);
    addButton = new QPushButton("添加分类", this);
    inputLayout->addWidget(categoryInput);
    inputLayout->addWidget(addButton);
    layout->addLayout(inputLayout);

    deleteButton = new QPushButton("删除选中分类", this);
    layout->addWidget(deleteButton);

    // 更新分类列表
    updateCategoryList();

    // 信号槽连接
    connect(addButton, &QPushButton::clicked, this, &CategoryManagerDialog::addCategory);
    connect(deleteButton, &QPushButton::clicked, this, &CategoryManagerDialog::deleteSelected);
    connect(categoryManager, &CategoryManager::categoriesChanged, this, &CategoryManagerDialog::updateCategoryList);
}

void CategoryManagerDialog::addCategory() {
    QString newCategory = categoryInput->text().trimmed();
    if (!newCategory.isEmpty()) {
        categoryManager->addCategory(newCategory);
        categoryInput->clear();
    }
}

void CategoryManagerDialog::deleteSelected() {
    QListWidgetItem *selectedItem = categoryListWidget->currentItem();
    if (selectedItem) {
        categoryManager->removeCategory(selectedItem->text());
    }
}

void CategoryManagerDialog::updateCategoryList() {
    categoryListWidget->clear();
    categoryListWidget->addItems(categoryManager->getCategories());
}
