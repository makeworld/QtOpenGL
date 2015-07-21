#include "window.h"

const qint64 DURATION = 200;

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
  , m_timerCount(1)
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
#if 0
  qint64 t = m_elapsedTimer.isValid() ? m_elapsedTimer.elapsed() : 0;
#else
  qint64 t = m_timerCount * 16;
#endif

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
#if 0
  if(!m_elapsedTimer.isValid()){
    m_elapsedTimer.start();
    startTimer(16);
  }
#else
  const QString filename = "capture-%1.png";
  for(qint64 i = 0; i < DURATION; ++i){
    context()->makeCurrent(this);
    glViewport(0, 0, width(), height());
    paintGL();
    context()->swapBuffers(this);
    grabFramebuffer().save(filename.arg(m_timerCount++));
  }
#endif
}

void OpenGLWindow::timerEvent(QTimerEvent *)
{
  update();
}

