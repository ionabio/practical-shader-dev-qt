#pragma once
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWindow>


class QOpenGLBuffer;
class QOpenGLShaderProgram;

// Since it is comparably a smaller program, all the implementation is in single project
class P1OGLWin : public QOpenGLWindow
{
public:
	P1OGLWin(){};
	virtual ~P1OGLWin();
private:
	QOpenGLShaderProgram* m_program;
	QOpenGLBuffer* m_vertex_buffer;
	QOpenGLBuffer* m_uv_buffer;
	QOpenGLVertexArrayObject* m_vertex_array_object;
protected:
	virtual void initializeGL() final override;
	virtual void paintGL() final override;
	virtual void resizeGL(int w, int h) final override;
};
