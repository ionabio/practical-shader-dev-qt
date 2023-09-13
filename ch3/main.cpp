#include "p1uvquad/P1OGLWin.h"
#include "p2fulltexture/P2OGLWin.h"
#include "p4colormath/p4oglwin.h"

#include <iostream>
#include <QApplication>
#include <QMainWindow>

// This application uses QOpenGLWindow without any Ui file,
// It is pretty simplistic implementation of a Qt application

using namespace std;
int main(int argc, char* argv[]) {
	cout<<"Welcome to Qt OpenGL"<<endl;
	cout<<R"(

Choose a mode of the chapter 3:

Due to different behaviors in windows and code complexity, each section is put in its folder, but still in a single project

1. UV Quad (where we represent colors red, green, yellow as the edges of the quat mapping)

2. Full texture (of parrot)

3. --- Nothing was presented

4. Full texture with color math (of parrot)
)";

	cout <<"Enter your choice:"<<endl;
	int choice;
	cin>>choice;
	assert(choice < 4 && choice > 0);

	//create a qt window
	QApplication app(argc, argv);
	QOpenGLWindow* openGlWindow;
	switch(choice)
	{
		case 1:
			openGlWindow = new P1OGLWin();
		break;
		case 2:
			openGlWindow = new P2OGLWin();
			break;
		case 3:
		case 4:
			openGlWindow = new P4OGLWin();
			break;

	}
	openGlWindow->setFormat(openGlWindow->format());
	openGlWindow->resize(400, 400);
	openGlWindow->show();
	return app.exec();
}