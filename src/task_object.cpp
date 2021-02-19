#include "task_object.h"

TaskObject::TaskObject(vmix::taskio::task task,
                       vmix::taskio::task_service& service)
    : task_(task), service_(service) {
  if (isNew()) {
    title("new task");
    description("");
    completed(false);
    date(QDateTime::currentDateTime().addDays(1));
  }
}

TaskObject::TaskObject(const TaskObject& other)
    : task_(other.task_), service_(other.service_) {}

TaskObject::~TaskObject() {}

int TaskObject::id() const {
  return task_.id();
}

bool TaskObject::isNew() const {
  return task_.id() < 0;
}

QString TaskObject::title() const {
  auto sv = task_.title();
  return QString::fromLatin1(sv.data(), sv.size());
}

void TaskObject::title(const QString& newTitle) {
  task_.title(newTitle.toStdString());
}

QString TaskObject::description() const {
  auto sv = task_.description();
  return QString::fromLatin1(sv.data(), sv.size());
}

void TaskObject::description(const QString& newDesc) {
  task_.description(newDesc.toStdString());
}

QDateTime TaskObject::date() const {
  auto sv = task_.time();

  return QDateTime::fromString(QString::fromLatin1(sv.data(), sv.size()),
                               Qt::ISODate)
      .toLocalTime();
}

void TaskObject::date(const QDateTime& newDate) {
  task_.time(newDate.toUTC().toString(Qt::ISODate).toStdString());
}

bool TaskObject::completed() const {
  return task_.completed();
}

void TaskObject::completed(bool c) {
  task_.completed(c);
}

void TaskObject::save() {
  if (isNew()) {
    auto t = service_.create();
    task_.id(t.id());
  }
  service_.update(task_);
}

void TaskObject::remove() {
  if (!isNew()) {
    service_.remove(task_);
  }
}

void TaskObject::fetch() {
  if (!isNew()) {
    task_ = service_.find(task_.id());
  } else {
    task_ = vmix::taskio::task();
  }
}
