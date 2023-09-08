#pragma once
#include <QOpenGLWindow>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

// Since it is comparably a smaller program, all the implementation is in single project
class OpenGlWindow : public QOpenGLWindow
{
public:
	OpenGlWindow(int choice) :m_choice(choice){};
	virtual ~OpenGlWindow();
private:
	int m_choice;
	QOpenGLShaderProgram* m_program;
	QOpenGLBuffer* m_vertex_buffer;
	QOpenGLBuffer* m_color_buffer;
	QOpenGLVertexArrayObject* m_vertex_array_object;

	void initializeTriangleWithRainbowOnEdges();
	void initializeRedTriangle();
	void initializeTriangleWithUniformColor();
protected:
	virtual void initializeGL() final override;
	virtual void paintGL() final override;
	virtual void resizeGL(int w, int h) final override;
};
