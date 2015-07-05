#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QScopedPointer>
#include <QElapsedTimer>
#include <QOpenGLFunctions>
#include <QOpenGLWindow>
#include <QOpenGLShaderProgram>

class OpenGLWindow : public QOpenGLWindow, protected QOpenGLFunctions
{
  Q_OBJECT

public:
  explicit OpenGLWindow(QWindow *parent = 0);
  ~OpenGLWindow();

protected:
  void initializeGL() Q_DECL_OVERRIDE;
  void resizeGL(int, int) Q_DECL_OVERRIDE;
  void paintGL() Q_DECL_OVERRIDE;

  void mousePressEvent(QMouseEvent *);
  void timerEvent(QTimerEvent *);

private:
  QScopedPointer<QOpenGLShaderProgram> m_program;
  int m_vertexLocation;
  int m_colorLocation;
  int m_matrixLocation;

  QElapsedTimer m_elapsedTimer;
};

#endif // WINDOW_H
