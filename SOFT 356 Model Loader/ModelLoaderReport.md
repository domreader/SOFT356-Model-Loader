Model Loader Markdown Report

This is a report for the SOFT356 Model Loader.
Throughout the first part of the module I have found it difficult however through learning how the Open GL side of things work I was able to get the model loader and texture to load. For the second part of the project I proposed further working on the model loader adding more features and making the program work better.

<h1> Setup </h1>

After downloading the folder and running the solution the project will open and allow the user to explore the file structure. Opening the ShadedCube.cpp file will show the code that runs the program including the reading, sorting out buffers and displaying.
Upon installing all of the texture files such as the Creeper.mtl are there meaning they do not have to be inputted seperately however if errors are appearing around the GLM functions please go to package manager and re-install GLM to sort this.

All of the files required to run should be present, the shaders have had little to no changes so these will work smoothly.

<h2> Using the Model Loader </h2>

After making sure there are no errors and everything is setup in the solution running the project will open a blank window allowing for the user to enter in a command. Please type the word 'Creeper' into the window and press enter. From this two cubes will spawn with the texture wrapped around and a light source will be visible too. A new implementation of camera movement is present allowing for basic movement with the WASD keys as well as mouse looking and zooming. This is using GLFW to read inputs and display them. The user can also close out of the window using the ESCAPE key then open the file again by typing Creeper.

<h3> Structure of the Program </h3>

From taking inspiration from project 5 the model loader is set out in a structure similar to this, broken into points below. 
As aforementioned the code for adding the new features as well as implementing on the previous submission is in the shadedcube.cpp. The lighting used and the shaders do use the basic features from project 5 due to difficulty implementing in the time.

- Including everything needed and adding stream ability
-Including GLM features to be able to render the cube
- Setting buffers and number of vertices then reading the file and setting up GLfloat arrays to push values into.
- Creating the Camera and setting initial position.
- Setting time between frames for refresh purposes
- Pushing data back into the arrays based on character layout in the OBJ file
- Setting up the buffers and setting out the indeces used to create triangles
- Loading texture - MTL File. This is seperated based on the characters again.
- In the Init file taking all of the GLfloat values and loading in information from shader.
- Configuring Lighting and setting up things such as Ambient, Specular and regaing these into Vec4, or Vec3.
- Setting up colours for rendering 
- Drawing and displaying the OBG with the appropriate texture (now draws two shapes)
- While loop for drawing and making sure that the inputs are managed.
- All of GLFW inputs including movement, toggling between wireframe too.
- Callback functions allowing for mouse tracking and scroll wheel tracking.

At the moment the features listed above are all included and the project is available on public SOFT356 Github


The features implemented in my project in the later stages included
- Camera & Movement
- Setting up lighting
- Adding user input to close and reopen the file.
- Adding an additional cube by redrawing original.
- Fixing texture wrapping issues.

<h4> Evaluation </h4>

Throughout the project I have struggled due to level of ability but by using project 3 to kickstart the initial build allowing for the rendering of the cube and texture I got to a point where I was confident on how it worked. From there using the ideas presented in Project 5 I managed to integrate lighting based on the Phong model having ambient, diffuse and specular. The movement was inspired from a learn OpenGL tutorial that was recommended to me. From the initial starting point I am happy with the stage I am at and my level of understanding. If I were to further develop the project I would add multiple VAO's and the ability to render different object; with potential to allow different shaders to be used.

YouTube Link to VS Walkthrough - https://youtu.be/Cu7eVeo9KXY
YouTube Link to Model Loader Demo - https://youtu.be/i2a9tkVZ79Q