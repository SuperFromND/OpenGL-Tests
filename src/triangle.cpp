// Shamelessly copied and modified from:
// https://gist.github.com/jordandee/94b187bcc51df9528a2f

#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <math.h>

int width = 640;
int height = 480;

void set_GL_aspect() {
    // re-calculates the openGL scale values
    // this prevents a stretching effect
    glLoadIdentity();
    float aspect = (float)width / (float)height;
    glOrtho(-aspect, aspect, -1, 1, -1, 1);
    
    return;
}

int main(int argc, char **argv) {
    SDL_Window *window = SDL_CreateWindow("Trevor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    SDL_GLContext Context = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(1);
    set_GL_aspect();

    float red = 0;
    float grn = 0;
    float blu = 0;
    
    glClearColor(0.f, 0.f, 0.f, 1.f);

    bool running = 1;
    
    while (running) {
        
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            
            if (event.type == SDL_WINDOWEVENT) {
                if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    SDL_GetWindowSize(window, &width, &height);
                    set_GL_aspect();
                }
            }
        }

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        red = fmod(red + 0.01, 1.f);
        grn = fmod(grn + 0.02, 1.f);
        blu = fmod(blu + 0.03, 1.f);

        // Cool triangle!
        glBegin(GL_POLYGON);
            glColor3f(red, 0, 0);
            glVertex3f(-red, -red, 0.5);
            glColor3f(0, grn, 0);
            glVertex3f(grn, -grn, 0);
            glColor3f(0, 0, blu);
            glVertex3f(0, blu, 0);
        glEnd();

        glFlush();        
        SDL_GL_SwapWindow(window);
    }
    
    return 0;
}