//#include "todoapp.h"
//#include "task_list.h"

#include "window.h"

#include <QApplication>
#include <QListView>

#include <vmix/taskio.hpp>

QString title();

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);

  using vmix::taskio::task_service;
  using vmix::taskio::task_storage_registry;

  task_service service(
      task_storage_registry::instance().make_storage("sqlite"));

  Window window(service);
  window.show();

  // TodoApp w(service);
  // w.show();
  return a.exec();
}
