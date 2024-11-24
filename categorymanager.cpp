#include "CategoryManager.h"

CategoryManager::CategoryManager(QObject *parent)
    : QObject(parent), categories({"Work", "Life", "Study"}) {}

QStringList CategoryManager::getCategories() const {
    return categories;
}

void CategoryManager::addCategory(const QString &category) {
    if (!categories.contains(category)) {
        categories.append(category);
        emit categoriesChanged(); // 发出分类变化信号
    }
}

void CategoryManager::removeCategory(const QString &category) {
    if (categories.contains(category)) {
        categories.removeAll(category);
        emit categoriesChanged(); // 发出分类变化信号
    }
}
