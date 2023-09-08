#pragma once
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWindow>


class QOpenGLBuffer;
class QOpenGLShaderProgram;

// Since it is comparably a smaller program, all the implementation is in single project
class OpenGlWindow : public QOpenGLWindow
{
public:
	OpenGlWindow(int choice) :m_choice(choice), m_current_color_index(-1){};
	virtual ~OpenGlWindow();
private:
	int m_choice;
	int m_current_color_index;
	QOpenGLShaderProgram* m_program;
	QOpenGLBuffer* m_vertex_buffer;
	QOpenGLBuffer* m_color_buffer;
	QOpenGLVertexArrayObject* m_vertex_array_object;

	void initializeTriangleWithRainbowOnEdges();
	void initializeTriangleWithUniformColor();
protected:
	virtual void initializeGL() final override;
	virtual void paintGL() final override;
	virtual void resizeGL(int w, int h) final override;
	virtual void keyReleaseEvent(QKeyEvent* e) final override;
};
