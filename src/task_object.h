#ifndef TASK_OBJECT_H
#define TASK_OBJECT_H

#include <QDateTime>

#include <vmix/taskio.hpp>

class TaskObject {
 public:
  TaskObject(vmix::taskio::task task, vmix::taskio::task_service& service);
  ~TaskObject();

  TaskObject(const TaskObject& other);

  int id() const;

  bool isNew() const;

  QString title() const;
  void title(const QString&);

  QString description() const;
  void description(const QString&);

  QDateTime date() const;
  void date(const QDateTime&);

  bool completed() const;
  void completed(bool);

  void save();
  void remove();
  void fetch();

 private:
  vmix::taskio::task task_;
  vmix::taskio::task_service& service_;
};

#endif  // TASK_H
