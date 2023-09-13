#include "p1oglwin.h"
#include <QtGui/QOpenGLFunctions>
#include <QtGui/qopengl.h>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

static const GLfloat vertexData[] = {
	//    x      y    z
	-1.0f, -1.0f, 0.0f,
	-1.0f, 1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
};

//The shape is
//   2  - 4
//   |  \ |
//   1  - 3

//color data is skipped

static const GLfloat uvData[] = {
	0.f, 0.f, // Vertex 1
	0.f, 1.f, // Vertex 2
	1.f, 0.f, // Vertex 3
	1.f, 1.f, // Vertex 4
};

const std::string vertexShaderSource = R"(#version 410

layout (location = 0) in vec3 pos; 
layout (location = 1) in vec2 uv;

out vec2 fragUV;

void main()
{
	gl_Position = vec4(pos, 1.0);
	fragUV = uv;
}
)";

const std::string fragmentShaderSource = R"(#version 410

in vec2 fragUV;
out vec4 outCol;

void main()
{
	outCol = vec4(fragUV, 0.0f, 1.0f);
})";




P1OGLWin::~P1OGLWin() {
	makeCurrent();
	m_program->removeAllShaders();
	m_program->release();
	m_vertex_array_object->release();
	m_vertex_buffer->release();
	m_uv_buffer->release();
}

void P1OGLWin::initializeGL()
{
	QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
	f->initializeOpenGLFunctions();
	m_program = new QOpenGLShaderProgram();
	m_vertex_array_object = new QOpenGLVertexArrayObject();
	m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource.c_str()); // Replace with your vertex shader path
	m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource.c_str()); // Replace with your fragment shader path
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

	m_uv_buffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
	m_uv_buffer->create();
	m_uv_buffer->bind();
	m_uv_buffer->allocate(uvData, sizeof(uvData));

	int uvAttr = m_program->attributeLocation("uv");
	m_program->enableAttributeArray(uvAttr);
	m_program->setAttributeBuffer(uvAttr, GL_FLOAT, 0, 2, 0);;
	
}

void P1OGLWin::paintGL()
{
	glClearColor(0.0, 0.0, 0.0, 1.0); // Set the clear color to black
	glClear(GL_COLOR_BUFFER_BIT);
	// Note the GL_QUAD used to be an old way of drawing which is depreciated since OGL 3. Triangle strip is pretty similar to what we want to achieve
	// https://en.wikipedia.org/wiki/Triangle_strip
	// The downside is we cannot index it as it seems it is possible with quads
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void P1OGLWin::resizeGL(int w, int h)
{
}