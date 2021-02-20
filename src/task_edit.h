#ifndef TODOAPP_H
#define TODOAPP_H

#include <QWidget>

#include "task_object.h"

class QLineEdit;
class QTextEdit;
class QDateTimeEdit;
class QCheckBox;
class QPushButton;

class TaskEdit : public QWidget {
  Q_OBJECT

 public:
  TaskEdit(QWidget* parent = nullptr);
  virtual ~TaskEdit();

 signals:
  void updated();

 public slots:
  void editTask(TaskObject* task);
  void onEdited();

 private:
  void save();
  void cancel();

  void updateView();
  void updateModel();

  void updateBottons();

  QLineEdit* title;
  QTextEdit* description;
  QDateTimeEdit* time;
  QCheckBox* completed;
  QCheckBox* important;
  QPushButton* saveButton;
  QPushButton* cancelButton;

  bool isDirty_;

  TaskObject* task_;
};

#endif  // TODOAPP_H
