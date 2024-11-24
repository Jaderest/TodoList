# TodoList 开发日志

## 2024.11.24

### 功能开发
- 实现了基本界面和分类功能
  -[ ] 优化一下添加任务后的界面显示，我这个可以实现一个list用来存储所有的type，这个也支持用户去修改type，就应该会很好用
  -[x] 添加分类修改的功能
  -[ ] 然后在categoriesManager中添加一个currentType的变量，用来存储当前的type，用来给taskManager方便
  -[ ] 分类修改后的内容也要传给taskManager 
- 基本的添加task已经实现
  -[ ] 剩下就是删除和修改的功能
