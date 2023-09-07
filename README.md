# Qt implementation of the Practical shader development book

Note. I am not affiliated with Apress or the original author of the book. 

Under fair use, this repository will contain qt (currently `QWidgets`) implementation of the source code.

The QT framework has its own wrappers for calling OpenGl functions. Since that is the framework I will be working on a daily basis, while reading the book, I practiced using QT.

The current implementation is targeted at `QWidgets`, and is `drawing` in `QOpenGlWindow`, which is very close to how 'QOpenGlWidget' functions are called 
However, you should note that many ways I have identified on drawing opengl content in Qt alone:
- [QOpenGLWindow](https://doc.qt.io/qt-6/qopenglwindow.html#details_) (Current work)
- QOpenGLWidget (Very similar to current implementation)
- [QWindow + QOpenGLFunction](https://doc.qt.io/qt-5/qtgui-openglwindow-example.html) (a bit different, and still doable)
  This is also what is refered in [Qt Gui](https://doc.qt.io/qt-5/qtgui-index.html) sections I assume
- [OpenGl using qml](https://doc.qt.io/qt-6/qtquick-scenegraph-openglunderqml-example.html) : currently I am not planning on this implementation yet 
- [QtOpenGL](https://doc.qt.io/qt-5/qtopengl-index.html) shouldn't be used, and I will avoid it as well
The original code is currently in the `Old` folder, but please refer to [original repository](https://github.com/Apress/practical-shader-dev) for the source of them. 

This repository accompanies [*Practical Shader Development*](https://www.apress.com/9781484244562) and the [original repository](https://github.com/Apress/practical-shader-dev) by Kyle Halladay (Apress, 2019).

[comment]: #cover
![Cover image](9781484244562.jpg)

## Installation

To Do. Until then the requirements are using CMake, and Qt 6
Some of the paths are hardcoded in cmake file, so please check them before compiling

-------------------------
From the original

## Releases

Release v1.0 corresponds to the code in the published book, without corrections or updates.

## Contributions

See the file Contributing.md for more information on how you can contribute to this repository.
