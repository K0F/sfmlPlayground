////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <math.h>

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////


int frameCount = 0;

using namespace std;

sf::ContextSettings contextSettings;
sf::RenderWindow window;
sf::Font font;
sf::Text text;
GLfloat ratio;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////


// Define a 3D cube (6 faces made of 2 triangles composed by 3 vertices)
GLfloat cube[] =
{
  // positions    // colors (r, g, b, a)
  -50, -50, -50,  0, 0, 1, 1,
  -50,  50, -50,  0, 0, 1, 1,
  -50, -50,  50,  0, 0, 1, 1,
  -50, -50,  50,  0, 0, 1, 1,
  -50,  50, -50,  0, 0, 1, 1,
  -50,  50,  50,  0, 0, 1, 1,

  50, -50, -50,  0, 1, 0, 1,
  50,  50, -50,  0, 1, 0, 1,
  50, -50,  50,  0, 1, 0, 1,
  50, -50,  50,  0, 1, 0, 1,
  50,  50, -50,  0, 1, 0, 1,
  50,  50,  50,  0, 1, 0, 1,

  -50, -50, -50,  1, 0, 0, 1,
  50, -50, -50,  1, 0, 0, 1,
  -50, -50,  50,  1, 0, 0, 1,
  -50, -50,  50,  1, 0, 0, 1,
  50, -50, -50,  1, 0, 0, 1,
  50, -50,  50,  1, 0, 0, 1,

  -50,  50, -50,  0, 1, 1, 1,
  50,  50, -50,  0, 1, 1, 1,
  -50,  50,  50,  0, 1, 1, 1,
  -50,  50,  50,  0, 1, 1, 1,
  50,  50, -50,  0, 1, 1, 1,
  50,  50,  50,  0, 1, 1, 1,

  -50, -50, -50,  1, 0, 1, 1,
  50, -50, -50,  1, 0, 1, 1,
  -50,  50, -50,  1, 0, 1, 1,
  -50,  50, -50,  1, 0, 1, 1,
  50, -50, -50,  1, 0, 1, 1,
  50,  50, -50,  1, 0, 1, 1,

  -50, -50,  50,  1, 1, 0, 1,
  50, -50,  50,  1, 1, 0, 1,
  -50,  50,  50,  1, 1, 0, 1,
  -50,  50,  50,  1, 1, 0, 1,
  50, -50,  50,  1, 1, 0, 1,
  50,  50,  50,  1, 1, 0, 1,
};


///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////



int setup(){
  contextSettings.depthBits = 24;
  // Request a 24-bits depth buffer when creating the window
  // Create the main window
  window.create(sf::VideoMode(640, 480), "Hello World OPENGL", sf::Style::Default, contextSettings);
  window.setVerticalSyncEnabled(true);
  window.setFramerateLimit(60);

  // Make it the active window for OpenGL calls
  window.setActive();

  if(!font.loadFromFile("resources/SempliceRegular.ttf"))
    return EXIT_FAILURE;

  text.setFont(font);
  text.setColor(sf::Color(255,255,255,170));
  text.setPosition(20.f,20.f);
  text.setCharacterSize(8);


  // Set the color and depth clear values
  glClearDepth(1.f);
  glClearColor(0.f, 0.f, 0.f, 1.f);

  // Enable Z-buffer read and write
  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);

  // Disable lighting and texturing
  glDisable(GL_LIGHTING);
  glDisable(GL_TEXTURE_2D);

  // Configure the viewport (the same size as the window)
  glViewport(0, 0, window.getSize().x, window.getSize().y);

  // Setup a perspective projection
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  ratio = static_cast<float>(window.getSize().x) / window.getSize().y;
  glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, 500.f);

  // Enable position and color vertex components
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glVertexPointer(3, GL_FLOAT, 7 * sizeof(GLfloat), cube);
  glColorPointer(4, GL_FLOAT, 7 * sizeof(GLfloat), cube + 3);

  // Disable normal and texture coordinates vertex components
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);

  return 0;
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////



int draw(sf::Clock clock){

  // Clear the color and depth buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Apply some transformations to rotate the cube
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.f, 0.f, -200.f);
  glRotatef(clock.getElapsedTime().asSeconds() * 5, 1.f, 0.f, 0.f);
  glRotatef(clock.getElapsedTime().asSeconds() * 30, 0.f, 1.f, 0.f);
  glRotatef(clock.getElapsedTime().asSeconds() * 90, 0.f, 0.f, 1.f);

  // Draw the cube
  glDrawArrays(GL_TRIANGLES, 0, 36);


  std::ostringstream ss;
  ss << (frameCount / clock.getElapsedTime().asSeconds()) << " FPS";
  text.setString(ss.str());

  window.pushGLStates();
  window.draw(text);
  window.popGLStates();

  frameCount++;

  /////////////////////////////////////////////////
  // Finally, display the rendered frame on screen
  window.display();
  /////////////////////////////////////////////////

  return 0;
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

int main()
{


  setup();
  // Create a clock for measuring the time elapsed

  sf::Clock clock;
  // Start the game loop
  while (window.isOpen())
  {
    // Process events
    sf::Event event;
    while (window.pollEvent(event))
    {
      // Close window: exit
      if (event.type == sf::Event::Closed)
        window.close();

      // Escape key: exit
      if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
        window.close();

      // Resize event: adjust the viewport
      if (event.type == sf::Event::Resized)
        glViewport(0, 0, event.size.width, event.size.height);
    }

    draw(clock);
  }

  return EXIT_SUCCESS;
}


