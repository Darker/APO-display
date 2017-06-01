## Usage

Start the game by running ./display in a command line. Input arguments: 

* pong (sarts the game of Pong)

* car (starts the racing car game)

If you run the game without the input arguments, menu will pop up where you can choose the game you want to play.

The Pong game can be closed by getting to score of 10 or by pressing all three buttons at the same time.

To get out of the car game just run into the obstacle.

## Compiling:

To debug the application on standard PC, use Qt Creator. On target device, use makefile.

## Thread model

Three threads are used to execute the application:

1. **Tick thread: **Responsible for game ticks - that is computation of game states

2. **Render thread:** Renders shapes on pixmap, which is an std::vector full of 24 bit RGB values

3. **Hardware render thread:** Converts 24 bit RGB values into 16bit RGB565 values and prints them on hardware screen

## Object model

### **Interfaces:**

#### class Shape

Defines abstract graphical object. Method render() is used to render shapes on pixmap. 

####`class GameInterface`

Defines abstract game/rendering object. Has following abstract methods:

* `getShapes` - returns an array of Shape* for later rendering. Shapes are copied.

* `tick` - all the game logic is happening here, if this function returns false, game has ended. Must be thread-safe.

* `render` - renders all the objects directly, without copying. Must be thread-safe

* `reset` - resets the game to initial state

### **Classes:**

####`class GameButton`

Provides information about button states.

* `bool peekClicked`: Returns true if button is in clicked state. Does not reset the state. Thread safe.

* `bool isClicked`: returns clicked state and sets it to false. Thread safe.

####`class Circle`

A class inheriting from Shape used for ball structure.

Properties:

* x and y postion

* radius

* vx and vy stands for velocity vectors  in x and y postions

* possibly color 

Methods:

* `move` - taking in time parameter, moves ball on a plane depending on vx and vy values

* `bounce` - depending on the object it is bouncing from inverts according velocity vector, for instance is the ball is bouncing from platform only vx is going to be inverted.eej

* `isPlayable` - a function to check whether the ball is in the game plane

* `render` - renders the ball 

####`class Game`

A class inheriting from GameInterface, the game logic and game rendering is happening here 

* contains two platforms and a ball

* can read data from 3 buttons

####`class Platform` 

A class inheriting from Recatngle class

* x and y position, length and width, color parameters

functions     

* checky - checks whether the platform position is in the game plane

* render - redners the platform on the game plane

####`Rectangle`

A Shape class 

* x and y positions

* length and width

* color

functions 

* intersect - functions to check intersections with platforms and a ball

