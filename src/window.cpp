#include "window.h"
#include "task_edit.h"
#include "task_list.h"

#include <QtWidgets>

#include <QItemSelection>

Window::Window(vmix::taskio::task_service& service, QWidget* parent)
    : service_(service), QWidget(parent) {
  active_ = nullptr;
  taskList_ = new TaskList(service_, this);

  taskListView_ = new QListView;
  taskListView_->setModel(taskList_);

  auto selectionModel = taskListView_->selectionModel();

  connect(selectionModel, &QItemSelectionModel::selectionChanged, this,
          &Window::selectionTaskChanged);

  auto taskEdit = new TaskEdit;
  connect(this, &Window::activeTask, taskEdit, &TaskEdit::editTask);
  connect(taskEdit, &TaskEdit::updated, this, &Window::reload);

  newButton = new QPushButton(tr("Добавить"));
  removeButton = new QPushButton(tr("&Удалить"));
  removeButton->setEnabled(false);

  auto buttonLayout = new QHBoxLayout;

  buttonLayout->addWidget(newButton);
  buttonLayout->addWidget(removeButton);

  connect(newButton, &QPushButton::clicked, this, &Window::newTask);
  connect(removeButton, &QPushButton::clicked, this, &Window::removeTask);

  QGridLayout* layout = new QGridLayout;
  layout->addWidget(taskListView_, 0, 0);
  layout->addLayout(buttonLayout, 1, 0, Qt::AlignCenter);
  layout->addWidget(taskEdit, 0, 1, 2, 1);

  setLayout(layout);
  setWindowTitle(QString("TodoApp 0.2.0, taskio %1.%2.%3 [%4.%5.%6]")
                     .arg(vmix::taskio::version_major())
                     .arg(vmix::taskio::version_minor())
                     .arg(vmix::taskio::version_micro())
                     .arg(VMIX_TASKIO_VERSION_MAJOR)
                     .arg(VMIX_TASKIO_VERSION_MINOR)
                     .arg(VMIX_TASKIO_VERSION_MICRO));

  changeActive(nullptr);
}

void Window::selectionTaskChanged(const QItemSelection& selected,
                                  const QItemSelection& deselected) {
  auto items = selected.indexes();

  selectedIndex_ = items.isEmpty() ? QModelIndex() : items.front();

  if (selectedIndex_.isValid()) {
    changeActive(taskList_->task(selectedIndex_.row()));
  } else {
    changeActive(nullptr);
  }
}

void Window::newTask() {
  taskListView_->selectionModel()->clearSelection();

  changeActive(new TaskObject(vmix::taskio::task(), service_));
}

void Window::reload() {
  taskList_->reload();

  if (taskList_->rowCount() > 0) {
    if (!selectedIndex_.isValid()) {
      selectedIndex_ =
          taskList_->index(taskList_->rowCount() - 1, 0, QModelIndex());
    }
  }

  QItemSelection selection(selectedIndex_, selectedIndex_);

  taskListView_->selectionModel()->select(selection,
                                          QItemSelectionModel::Select);
}

void Window::removeTask() {
  if (active_ && !active_->isNew()) {
    active_->remove();
    changeActive(nullptr);

    auto rowCount = taskList_->rowCount() - 1;

    auto row = selectedIndex_.row();
    row = row >= rowCount ? row - 1 : row;

    selectedIndex_ = taskList_->index(row, 0, QModelIndex());
  }

  reload();
}

void Window::changeActive(TaskObject* task) {
  if (active_ && active_->isNew()) {
    delete active_;
  }

  active_ = task;

  removeButton->setEnabled(active_ ? !active_->isNew() : false);

  emit activeTask(active_);
}
