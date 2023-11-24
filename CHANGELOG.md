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
- Fixed a bug where using the W and S keys will move towards and away the y-axis when looking directly towards the y or -y axes
- Included getWindow() in W_App to get an application's window