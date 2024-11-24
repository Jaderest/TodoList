#ifndef CATEGORYMANAGER_H
#define CATEGORYMANAGER_H

#include <QObject>

#include <QObject>
#include <QStringList>

class CategoryManager : public QObject {
    Q_OBJECT

public:
    explicit CategoryManager(QObject *parent = nullptr);

    [[nodiscard]] QStringList getCategories() const; // 获取分类列表
    void addCategory(const QString &category); // 添加分类
    void removeCategory(const QString &category); // 删除分类

    signals:
        void categoriesChanged(); // 分类列表变化信号

private:
    QStringList categories; // 存储分类列表
};

#endif // CATEGORYMANAGER_H
