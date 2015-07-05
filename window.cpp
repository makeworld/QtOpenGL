#include "window.h"

static const GLfloat vertices[] = {
   0.0f, 0.707f, 0.0f,
  -0.5f,  -0.5f, 0.0f,
   0.5f,  -0.5f, 0.0f
};
static const GLfloat colors[] = {
  1.0f, 0.0f, 0.0f, 1.0f,
  0.0f, 1.0f, 0.0f, 1.0f,
  0.0f, 0.0f, 1.0f, 1.0f
};

OpenGLWindow::OpenGLWindow(QWindow *parent)
  : QOpenGLWindow(QOpenGLWindow::NoPartialUpdate, parent)
{
}

OpenGLWindow::~OpenGLWindow()
{

}

void OpenGLWindow::initializeGL()
{
  initializeOpenGLFunctions();

  //
  // shader program
  //

  m_program.reset(new QOpenGLShaderProgram(this));
  m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl");
  m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl");
  m_program->link();
  m_program->bind();

  //
  // variables
  //

  m_vertexLocation  = m_program->attributeLocation("vertex");
  m_colorLocation  = m_program->attributeLocation("sourceColor");
  m_program->enableAttributeArray(m_vertexLocation);
  m_program->enableAttributeArray(m_colorLocation);

  m_matrixLocation  = m_program->uniformLocation("matrix");
}

void OpenGLWindow::resizeGL(int, int)
{
}

void OpenGLWindow::paintGL()
{
  qint64 t = m_elapsedTimer.isValid() ? m_elapsedTimer.elapsed() : 0;

  glClear(GL_COLOR_BUFFER_BIT);

  m_program->setAttributeArray(m_vertexLocation, vertices, 3, 0);
  m_program->setAttributeArray(m_colorLocation, colors, 4, 0);

  QMatrix4x4 matrix;
  matrix.rotate(t / 10.0f, 0.0f, 1.0f, 0.0f);
  m_program->setUniformValue(m_matrixLocation, matrix);

  glDrawArrays(GL_TRIANGLES, 0, 3);
}

void OpenGLWindow::mousePressEvent(QMouseEvent *)
{
  if(!m_elapsedTimer.isValid()){
    m_elapsedTimer.start();
    startTimer(16);
  }
}

void OpenGLWindow::timerEvent(QTimerEvent *)
{
  update();
}

