PURPOSE: 
the main purpose of it to test the map generation from txts and also to make a buffer so that it loads only that part of map that is visible from *SFML View*.
PROBLEMS:
the only remark you can have is that the images in *Cell_Textures* folder may not load and may display a blank white screen because i have given relative paths to them.
if they do not load kindly use *Absloute Path*.
it does not draw *Sprites* instead it just applies Texture to each cell in the grid. 

the cmake file provided can automatically generate the build folder from which you can get bin folder and the executable as well.
just go to the directory containing CMakeLists.txt and the src folder and type 

cmake -B build in cmd

let it run and
after that type 

cmake --build build

both these commands take some time and create the build folder
