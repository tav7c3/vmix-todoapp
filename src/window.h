
#ifndef WINDOW_H
#define WINDOW_H

#include <QModelIndex>
#include <QVector>
#include <QWidget>

#include "task_object.h"

class TaskList;
class QPushButton;
class TaskList;
class QListView;
class QItemSelection;

namespace vmix::taskio {
class task_service;
}

class Window : public QWidget {
  Q_OBJECT

 public:
  Window(vmix::taskio::task_service& service, QWidget* parent = nullptr);

 private slots:
  void selectionTaskChanged(const QItemSelection& selected,
                            const QItemSelection& deselected);

  void newTask();
  void removeTask();

  void reload();

 signals:
  void activeTask(TaskObject* task);

 private:
  void changeActive(TaskObject* task);

  QPushButton* newButton;
  QPushButton* removeButton;

  TaskList* taskList_;
  QListView* taskListView_;

  vmix::taskio::task_service& service_;
  TaskObject* active_;

  QModelIndex selectedIndex_;
};

#endif  // WINDOW_H
