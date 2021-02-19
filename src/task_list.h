
#ifndef TASK_LIST_H
#define TASK_LIST_H

#include "task_object.h"

#include <QAbstractListModel>
#include <QVector>

class TaskList : public QAbstractListModel {
  Q_OBJECT
 public:
  TaskList(vmix::taskio::task_service& service, QObject* parent = nullptr);
  ~TaskList() = default;

  int rowCount(const QModelIndex& parent = QModelIndex()) const override;

  QVariant data(const QModelIndex& index,
                int role = Qt::DisplayRole) const override;

  TaskObject* task(int row);

  void reload();

 private:
  vmix::taskio::task_service& service_;
  QVector<TaskObject> tasks_;
};

#endif  // TASK_MODEL_H
