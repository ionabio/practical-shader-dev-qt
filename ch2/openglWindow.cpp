#include "openglWindow.h"

#include <QtGui/QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QtGui/qopengl.h>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>

static const GLfloat vertexData[] = {
	// a diamond object with two triangles
		//    x      y     z , r, g, b, a
		-1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		1.0f,  -1.0f, 0.0f,
};

static const GLfloat colorData[] = {
	1.f, 0.f, 0.f, 1.f, // Vertex 1
	0.f, 1.f, 0.f, 1.f, // Vertex 2
	0.f, 0.f, 1.f, 1.f, // Vertex 3
};

const char* vertexShaderSource = R"(
        #version 410

        layout (location = 0) in vec3 pos;
        layout (location = 1) in vec4 col;

		out vec4 fragColor;

        void main()
        {
            gl_Position = vec4(pos, 1.0);
			fragColor = vec4(col);
        }
    )";

// Define your fragment shader source code as a string
const char* fragmentShaderSource = R"(
        #version 410
        
        in vec4 fragColor;  
        out vec4 outColor;

        void main()
        {
            outColor = fragColor;//vec4(1.0, 0.0, 0.0, 1.0); 
        }
    )";

OpenGlWindow::~OpenGlWindow() {
	makeCurrent();
	m_program->removeAllShaders();
	m_program->release();
	m_vertex_array_object->release();
	m_vertex_buffer->release();
	m_color_buffer->release();
}

void OpenGlWindow::initializeTriangleWithRainbowOnEdges()
{
	m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource); // Replace with your vertex shader path
	m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource); // Replace with your fragment shader path
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

void OpenGlWindow::initializeRedTriangle()
{
	//creat a red triangle without shaders
	

}

void OpenGlWindow::initializeTriangleWithUniformColor()
{
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
		  initializeRedTriangle();
		  break;
	  case(3):
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
