Model Loader Markdown Report

This is a report for the SOFT356 Model Loader.
Throughout the first part of the module I have found it difficult however through learning how the Open GL side of things work I was able to get the model loader and texture to load.

<h1> Setup </h1>

After downloading the folder and running the solution the project will open and allow the user to explore the file structure. Opening the TexturedCube.cpp file will show the code that runs the program including the reading, sorting out buffers and displaying.
Upon installing all of the texture files sucha s the Creeper.mtl are there meaning they do not have to be inputted seperately however if errors are appearing around the GLM functions please go to package manager and re-install GLM to sort this.

<h2> Using the Model Loader </h2>

After making sure there are no errors and everything is setup in the solution running the project will open a blank window allowing for the user to enter in a command. Please type the word 'Creeper' into the window and press enter. From this it will display the cube with the texture
wrapped around it. This at the moment is as much as the program does so this should all render properly.

<h3> Structure of the Program </h3>

From taking inspiration from project 3 the model loader is set out in a structure similar to this, broken into points below. 
As aforementioned the code for reading, seperating and putting into the buffers is all in the TexturedCube.cpp

- Including everything needed and addeing stream ability
- Setting buffers and number of vertices then reading the file and setting up GLfloat arrays to push values into
- Pushing data back into the arrays based on character layout in the OBJ file
- Setting up the buffers and setting out the indeces used to create triangles
- Loading texture - MTL File. This is seperated based on the characters again.
- Drawing and displaying the OBG with the appropriate texture

At the moment the features listed above are all included until further implementation and is all on Github too.
On public SOFT356 Github