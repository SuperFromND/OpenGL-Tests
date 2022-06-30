// Draws a hexagonal starburst effect
// AKA the "Super Hexagon" effect

#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <math.h>

int width = 854;
int height = 480;

const float to_rad = 3.1415926535 / 180;

void set_GL_aspect() {
    // re-calculates the openGL scale values
    // this prevents a stretching effect
    glLoadIdentity();
    float aspect = (float)width / (float)height;
    glOrtho(-aspect, aspect, -1, 1, -1, 1);
    
    return;
}

int main(int argc, char **argv) {
    SDL_Window *window = SDL_CreateWindow("Terrence", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    SDL_GLContext Context = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(1);
    set_GL_aspect();
    
    // change this to change the size of the hexagon; 4 is used here to fill most common aspect ratios
    float hex_w = 4.f;
    
    // calculates and stores the X and Y of the hexagon corners
    // we already know the center coord (0,0), so we can draw triangles from this
    float hex[12] = {
        hex_w, 0.f,
        hex_w * cos(60 * to_rad), hex_w * sin(60 * to_rad),
        hex_w * cos(120 * to_rad), hex_w * sin(120 * to_rad),
        -hex_w, 0.f,
        hex_w * cos(240 * to_rad), hex_w * sin(240 * to_rad),
        hex_w * cos(300 * to_rad), hex_w * sin(300 * to_rad)
    };
    
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

        glPushMatrix();
        glRotated(SDL_GetTicks() * 0.05, 0, 0, 1);
        
        // Draws the individual slices of the hexagon
        glBegin(GL_TRIANGLES);
            glColor3f(0.2, 0.75, 0.2);
            glVertex3f(hex[0], hex[1], 0);
            glVertex3f(hex[2], hex[3], 0);
            glVertex3f(0, 0, 0);

            glVertex3f(hex[4], hex[5], 0);
            glVertex3f(hex[6], hex[7], 0);
            glVertex3f(0, 0, 0);
            
            glVertex3f(hex[8], hex[9], 0);
            glVertex3f(hex[10], hex[11], 0);
            glVertex3f(0, 0, 0);
            
            glColor3f(0.4, 1, 0.4);
            glVertex3f(hex[2], hex[3], 0);
            glVertex3f(hex[4], hex[5], 0);
            glVertex3f(0, 0, 0);
            
            glVertex3f(hex[6], hex[7], 0);
            glVertex3f(hex[8], hex[9], 0);
            glVertex3f(0, 0, 0);
            
            glVertex3f(hex[10], hex[11], 0);
            glVertex3f(hex[0], hex[1], 0);
            glVertex3f(0, 0, 0);
        glEnd();
        
        glPopMatrix();

        glFlush();
        SDL_GL_SwapWindow(window);
    }
    
    return 0;
}