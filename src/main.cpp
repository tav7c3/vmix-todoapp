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

  return a.exec();
}
