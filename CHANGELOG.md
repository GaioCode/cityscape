# version 1.0.0
This version aims to create and render a basic cube and first person camera, as well as integrating the program using
wolf libraries. The camera will have WASD and Sprint functionality. Mouse functionality will be added later.

- Cloned week9 assignment by Gordon Wood; remove samples from src folder
- Added CHANGELOG.md and README.md files
- Set up Cityscape class as main program to render a cube with camera
- Set up basic.vsh and basic.fsh, which are temporary vertex and pixel shaders for the project
- Added sheep, a helper library for this project (it's Shaun the Sheep!)
- Added sheep directory in CMakeLists.txt
- Added basicStructures.h in sheep to make standardized structures reusable
- Added FirstPersonCamera classes in sheep
- Created Cube class

## version 1.1.0
This version aims to complete the first person camera class by adding mouse movement functionality, adjusting and
optimzing code, and completing documentation. The camera will also include keys to "ascend" and "descend" the camera,
where the camera moves up and down vertically.

- Changed Sprint key from Left-Shift to Left-Control
- Added mouse movement functionality in firstPersonCamera classes
- Adjusted camera to look at cube when initialized after adding mouse calculations
- Added printCameraInfo() that shows debugging information in the console
- Changed camera sprint key from LeftShift to Left-Control in firstPersonCamera classes
- Added Spacebar input for camera ascend and Shift input for camera descend in firstPersonCamera classes
- Fixed a bug where using the W and S keys will move towards and away the y-axis when looking directly towards the y or
  -y axes
- Included getWindow() in W_App to get an application's window

## version 1.2.0
This version aims to create a textured cube.

- Provided functionality for missing methods for Cube class in Cube.cpp
- Added textures folder under cityscape > data
- Added brick.png into the textures folder
- Created TexturedCube class and texture shaders
- Added depth tests to Cityscape classes
- Modified sheep::structure to support textures

## version 2.0.0
The goal is to set up a class hierarchy that contains classes to generate buildings. A Building class will be an
abstract class consisting of many differnet components. This version aims to create just one building model, called 
StandardBuilding. StandardBuilding will comprise of 3 different components: the base, middle, and height.

- Created sheep.h to store all header files
- Adjusted code to implement sheep.h where necessary
- Added polygonStructures.h to store vertices of common polygons
- Created Building parent class and StandardBuilding child class
- Created Component class
- Created ComponentHelper class to store methods to generate components
- Fixed bugs and optimized code across multiple classes
- Modified W_VertexBuffer, W_IndexBuffer, and W_BufferManager classes to support updating existing VBOs and Index
  Buffers
- Implemented randomization to generate random buildings

## version 2.1.0
This version aims to create a way to generate polygon prisms. This generator will be able to generate a polygon prism
of any sides, providing the correct vertices and indices. Moreover, this version also aims to add a regenerate tool to
regenerate the city. This involves destructing the entire city and reconstructing it. The reconstruction will
re-randomize the entire city and its buildings.

- Added regenerate() in Cityscape class to regenerate a new random world
- Added transform() in ComponentHelper class to transform individual vertices
- Created randomNumberGenerator class and implemented to Buildings for random generation
- Created n-sided polygon generator for vertices and indices
- Set textures to nearest filtering
- Fixed a bug where all buildings are generated using the same VBO data

## version 3.0.0
This version aims to add roads and a class to manage entities. Entities include roads, buildings, and any future objects,
such as lamps. The entity manager will handle the building generaton and randomization, including randomizing the
building's components. This version will also implement texture atlassing, along with a tileset that I designed using
Aseprite.

- Created EntityManager class, which is now in charge of initializing buildings, roads, and other entities
- Created Land class to act as the land for the buildings
- Created an algorithm to generate buildings in chunks, where each chunk contains up to 4 buildings
- Created TextureMap class to store structures related to texture atlassing
- Added road texture and tileset for buildings
- Created texture sets, allowing EntityManager to choose which set of textures to use for the buildings to provide
  logical randomization
- Edited Building class and its child classes to support texture atlassing

## version 3.0.1

- Fixed texture atlassing for PolygonBuilding