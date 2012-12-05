painting-boids
==============

![Boids sample](https://dl.dropbox.com/u/15525442/suttu.png)

A silly graphics toy written in Qt.

The application runs a simulation which contains autonomous agents that follow
the famous "boids" rules (http://en.wikipedia.org/wiki/Boids) invented by Craig Reynolds.
As the boids wander around the scene, they leave a trail which has colors picked
from a user define image.

The simulation starts by clicking the left mouse button in the scene window. Moving
mouse cursor inside the scene window while holding down right mouse button will
move the target to which the boids feel irresistible urge to fly to. Otherwise
the UI should be easy to figure out. Have fun playing with the settings.

If your platform doesn't support OpenGL you can just comment out the lines in main.cpp:
    QGLWidget* viewport = new QGLWidget();
    view.setViewport(viewport);
