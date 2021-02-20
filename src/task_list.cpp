
#include "task_list.h"

#include <QBrush>

TaskList::TaskList(vmix::taskio::task_service& service, QObject* parent)
    : service_(service), QAbstractListModel(parent) {
  reload();
}

int TaskList::rowCount(const QModelIndex&) const {
  return tasks_.size();
}

QVariant TaskList::data(const QModelIndex& index, int role) const {
  if (!index.isValid())
    return QVariant();

  if (index.row() >= tasks_.size() || index.row() < 0)
    return QVariant();

  const auto& task = tasks_.at(index.row());

  if (role == Qt::DisplayRole) {
    return QString("%1 | %2 (%3) %4 %5")
        .arg(index.row() + 1, 3)
        .arg(task.title())
        .arg(task.date().toString())
        .arg(task.completed() ? "+" : "-")
        .arg(task.important() ? "^" : "");
  } else if (role == Qt::BackgroundRole) {
    if (task.completed())
      return QBrush(Qt::green);
    if (!task.completed() && QDateTime::currentDateTime() > task.date())
      return QBrush(Qt::red);
    if (task.important() && !task.completed())
      return QBrush(Qt::yellow);
  }

  return QVariant();
}

TaskObject* TaskList::task(int row) {
  if (row >= tasks_.size() || row < 0)
    return nullptr;

  return &tasks_[row];
}

void TaskList::reload() {
  beginResetModel();

  tasks_.clear();
  auto tasks = service_.all();

  for (auto task : tasks) {
    tasks_.push_back(TaskObject(task, service_));
  }

  endResetModel();
}
