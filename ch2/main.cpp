#include "openglwindow.h"

#include <iostream>
#include <string>
#include <QApplication>
#include <QMainWindow>

// This application uses QOpenGLWindow without any Ui file,
// It is pretty simplistic implementation of a Qt application

using namespace std;
int main(int argc, char* argv[]) {
	cout<<"Welcome to Qt OpenGL"<<endl;
	cout<<R"(

Choose a mode of the chapter:

1. Triangle with rainbow on edges

2. Triangle with uniform color (press any key to change the colors
(note that this second part is never implemented in the book, but it is implied and would make a good exercise)

)";

	cout <<"Enter your choice:"<<endl;
	int choice;
	cin>>choice;
	assert(choice < 4 && choice > 0);

	//create a qt window
	QApplication app(argc, argv);
	OpenGlWindow openGlWindow(choice);
	openGlWindow.setFormat(openGlWindow.format());
	openGlWindow.resize(400, 400);
	openGlWindow.show();
	return app.exec();

}