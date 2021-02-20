#include "task_edit.h"

#include <QCheckBox>
#include <QDateTimeEdit>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>

TaskEdit::TaskEdit(QWidget* parent)
    : QWidget(parent), task_(nullptr), isDirty_(false) {
  auto titleLabel = new QLabel(tr("Заголовок:"));
  auto descriptionLabel = new QLabel(tr("Описание:"));
  auto timeLabel = new QLabel(tr("Время:"));
  auto completedLabel = new QLabel(tr("Выполнено:"));
  auto importantLabel = new QLabel(tr("Важное:"));

  title = new QLineEdit;
  description = new QTextEdit;
  time = new QDateTimeEdit;
  completed = new QCheckBox;
  important = new QCheckBox;

  connect(title, &QLineEdit::textEdited, this, &TaskEdit::onEdited);
  connect(description, &QTextEdit::textChanged, this, &TaskEdit::onEdited);
  connect(time, &QDateTimeEdit::dateTimeChanged, this, &TaskEdit::onEdited);
  connect(completed, &QCheckBox::stateChanged, this, &TaskEdit::onEdited);
  connect(important, &QCheckBox::stateChanged, this, &TaskEdit::onEdited);

  saveButton = new QPushButton(tr("Сохранить"));
  cancelButton = new QPushButton(tr("Отмена"));

  connect(saveButton, &QPushButton::clicked, this, &TaskEdit::save);
  connect(cancelButton, &QPushButton::clicked, this, &TaskEdit::cancel);

  auto buttonLayout = new QHBoxLayout;
  buttonLayout->addWidget(saveButton);
  buttonLayout->addWidget(cancelButton);

  updateBottons();

  auto layout = new QGridLayout;
  layout->addWidget(titleLabel, 0, 0);
  layout->addWidget(title, 0, 1);
  layout->addWidget(descriptionLabel, 1, 0);
  layout->addWidget(description, 1, 1);
  layout->addWidget(timeLabel, 2, 0);
  layout->addWidget(time, 2, 1);
  layout->addWidget(completedLabel, 3, 0);
  layout->addWidget(completed, 3, 1);
  layout->addWidget(importantLabel, 4, 0);
  layout->addWidget(important, 4, 1);
  layout->addLayout(buttonLayout, 5, 1, Qt::AlignCenter);

  setLayout(layout);
}

TaskEdit::~TaskEdit() {}

void TaskEdit::editTask(TaskObject* task) {
  task_ = task;

  updateView();
  isDirty_ = false;
  updateBottons();
}

void TaskEdit::onEdited() {
  isDirty_ = true;

  updateBottons();
}

void TaskEdit::save() {
  updateModel();

  if (task_) {
    task_->save();
    emit updated();
  }
};

void TaskEdit::cancel() {
  if (task_) {
    if (task_->isNew()) {
      emit updated();
    } else {
      task_->fetch();
      editTask(task_);
    }
  }
}

void TaskEdit::updateView() {
  if (task_) {
    title->setEnabled(true);
    title->setText(task_->title());

    description->setEnabled(true);
    description->setText(task_->description());

    time->setEnabled(true);
    time->setDateTime(task_->date());

    completed->setEnabled(true);
    completed->setChecked(task_->completed());

    important->setEnabled(true);
    important->setChecked(task_->important());

  } else {
    title->clear();
    title->setEnabled(false);

    description->clear();
    description->setEnabled(false);

    time->clear();
    time->setEnabled(false);

    completed->setChecked(false);
    completed->setEnabled(false);

    important->setChecked(false);
    important->setEnabled(false);
  }
}

void TaskEdit::updateBottons() {
  if (task_) {
    saveButton->setEnabled(isDirty_ || task_->isNew());
    cancelButton->setEnabled(isDirty_ || task_->isNew());
  } else {
    saveButton->setEnabled(false);
    cancelButton->setEnabled(false);
  }
}

void TaskEdit::updateModel() {
  if (task_) {
    task_->title(title->text());
    task_->description(description->toPlainText());
    task_->date(time->dateTime());
    task_->completed(completed->isChecked());
    task_->important(important->isChecked());
  }
}
