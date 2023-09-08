#include "openglWindow.h"
#include "shaders.h"

#include <QtGui/QOpenGLFunctions>
#include <QtGui/qopengl.h>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

static const GLfloat vertexData[] = {
		//    x      y    z
		-1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		1.0f,  -1.0f, 0.0f,
};

static const GLfloat colorData[] = {
	1.f, 0.f, 0.f, 1.f, // Vertex 1
	0.f, 1.f, 0.f, 1.f, // Vertex 2
	0.f, 0.f, 1.f, 1.f, // Vertex 3
};

static const GLfloat uniformColorData[] = {
	1.f, 0.f, 0.f, 1.f, // color 1
	0.f, 1.f, 0.f, 1.f, // color 2
	0.f, 0.f, 1.f, 1.f, // color 3
};


OpenGlWindow::~OpenGlWindow() {
	makeCurrent();
	m_program->removeAllShaders();
	m_program->release();
	m_vertex_array_object->release();
	m_vertex_buffer->release();
	if(m_choice == 1) m_color_buffer->release();
}

void OpenGlWindow::initializeTriangleWithRainbowOnEdges()
{
	m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderRainbowSource); // Replace with your vertex shader path
	m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderRainbowSource); // Replace with your fragment shader path
	m_program->link();
	m_program->bind();

	m_vertex_array_object->create();
	m_vertex_array_object->bind();

	m_vertex_buffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
	m_vertex_buffer->create();
	m_vertex_buffer->bind();
	m_vertex_buffer->allocate(vertexData, sizeof(vertexData));

	int positionAttr = m_program->attributeLocation("pos");
	m_program->enableAttributeArray(positionAttr);
	m_program->setAttributeBuffer(positionAttr, GL_FLOAT, 0, 3, 0);

	m_color_buffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
	m_color_buffer->create();
	m_color_buffer->bind();
	m_color_buffer->allocate(colorData, sizeof(colorData));

	int colAttr = m_program->attributeLocation("col");
	m_program->enableAttributeArray(colAttr);
	m_program->setAttributeBuffer(colAttr, GL_FLOAT, 0, 4, 0);
}

void OpenGlWindow::initializeTriangleWithUniformColor()
{
	m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderUniformSource); // Replace with your vertex shader path
	m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderUniformSource); // Replace with your fragment shader path
	m_program->link();
	m_program->bind();

	m_vertex_array_object->create();
	m_vertex_array_object->bind();

	m_vertex_buffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
	m_vertex_buffer->create();
	m_vertex_buffer->bind();
	m_vertex_buffer->allocate(vertexData, sizeof(vertexData));

	int positionAttr = m_program->attributeLocation("pos");
	m_program->enableAttributeArray(positionAttr);
	m_program->setAttributeBuffer(positionAttr, GL_FLOAT, 0, 3, 0);

	m_program->setUniformValue("col", uniformColorData[0], uniformColorData[1], uniformColorData[2], 1.0);
}

void OpenGlWindow::initializeGL()
{
	QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
	f->initializeOpenGLFunctions();
	m_program = new QOpenGLShaderProgram();
	m_vertex_array_object = new QOpenGLVertexArrayObject();
	switch (m_choice)
	{
	  case(1):
	  	initializeTriangleWithRainbowOnEdges();
		break;
	  case(2):
	  default:
		initializeTriangleWithUniformColor();
		break;
	}
}

void OpenGlWindow::paintGL()
{
	glClearColor(0.0, 0.0, 0.0, 1.0); // Set the clear color to black
	glClear(GL_COLOR_BUFFER_BIT);    
	glDrawArrays(GL_TRIANGLES, 0, sizeof(vertexData) / sizeof(GLfloat));
}

void OpenGlWindow::resizeGL(int w, int h)
{
}

void OpenGlWindow::keyReleaseEvent(QKeyEvent* event)
{
	if (m_choice == 1)
		return;

	// on any key we are going to switch color and issue a redraw
	// note that window should be on focus for this to work

	if(m_current_color_index >= sizeof(uniformColorData) / sizeof(GLfloat))
		m_current_color_index = 0;
 	m_program->setUniformValue("col", uniformColorData[m_current_color_index],
	                           uniformColorData[m_current_color_index + 1], 
	                           uniformColorData[m_current_color_index + 2],
	                           uniformColorData[m_current_color_index + 3]);
	m_current_color_index += 4;

	update();
}