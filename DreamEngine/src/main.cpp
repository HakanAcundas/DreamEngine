#include "widow/window.h"

using namespace dream;
using namespace window;

int main(void)
{
    Window window("DreamEngine", 640, 480, false);
    glClearColor(0.5, 0.5, 0.5, 1.0);

    while (!window.isClosed())
    {
        window.clear();
        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5, -0.5);
        glVertex2f(0.0, 0.5);
        glVertex2f(0.5, -0.5);
        glEnd();
        /* Swap front and back buffers */
        window.update();

        //std::cout << window.getWidth() << "||" << window.getHeight() << std::endl;
    }

    return 0;
}