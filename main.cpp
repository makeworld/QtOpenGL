#include "window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  OpenGLWindow w;
  w.resize(640, 480);
  w.show();

  return a.exec();
}
