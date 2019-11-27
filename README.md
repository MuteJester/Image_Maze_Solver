# Image_Maze_Solver
A CPP algorithm which imporats a .jpg image from drive storage ,finds the path trough the maze and saves a new image with the correct path colored red 

This project is based on implementation of the following library : " stb-master"
which gave me a great base for developing the coloring and analysis of the image data,
i trough away my self made jpg library after debuging i understood that my methods
wont cover every image type and size,pepole with greater expirence and skill already 
developed a simple and efficient library so shoutout to the creators of "stb-image library"

my "Maze" class inherits another class called "Image" which manages all the image handeling
needed to be done while reading the maze data'analysis runs ,path finding,and coloring.

For more about the "Image"class and its features you can reffer to the project
in my profile.

In order to run the algorithm all you need is the import all the header files and cpp files into your project
or simple copy the compressed project which holds all the data in one cpp file
dont forget to donwload the stb librarys as well into the project folder.

Running:

You can try out all the diffrent functions in both classes 
but for your simplicity if all you desire is to solve a maze ;

A:
create an object type maze-

Maze Test;

B:
Load and image into the maze:
test.Load_Maze("File_name");

C:
Init Solving algorithm ,at the end of the algorithm it will save the solution as "solution.jpg"
test.Solve_Maze();

you can use http://pixelartmaker.com/ to create your own mazes
keep in mind black pixels are walls and white are paths
the path is 1 pixel in width .
and the start has to be in the upmost upper row
and the end has to be in the bottom line.
