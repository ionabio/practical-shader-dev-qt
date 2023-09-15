#pragma once
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWindow>


class QOpenGLBuffer;
class QOpenGLShaderProgram;
class QOpenGLTexture;

// Since it is comparably a smaller program, all the implementation is in single project
class P5OGLWin : public QOpenGLWindow
{
public:
	P5OGLWin();
	virtual ~P5OGLWin();
private:
	QOpenGLShaderProgram* m_program;
	QOpenGLBuffer* m_vertex_buffer;
	QOpenGLBuffer* m_uv_buffer;
	QOpenGLTexture* m_texture;
	QOpenGLVertexArrayObject* m_vertex_array_object;
	QTime* start_time;
protected:
	virtual void initializeGL() final override;
	virtual void paintGL() final override;
	virtual void resizeGL(int w, int h) final override;
};
