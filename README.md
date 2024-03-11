# ComputerVisionProjects

### Table of Contents
1. [Description](#Description)
2. [PrimitivePaintApplication](#PrimitivePaintApplication)
3. [CoinCountingApplication](#CoinCountingApplication)
4. [BoxDimensionCalculator](#BoxDimensionCalculator)

## Description
This repository is a collection of mini computer vision projects completed over the summer of 2023. These were developed on a 64-bit Ubuntu machine.

## Clone Repository
~~~
$ git clone https://github.com/faithg3/ComputerVisionProjects.git
~~~
## PrimitivePaintApplication
This program is a very primitive version of Paint installed on Windows machines.

### Features
Left-click to toggle through features. Right-click to use the selected tool.
* Eyedropper Tool: Click to select the color you would like to draw with.
* Pencil Tool: Hold and drag the mouse to draw with the selected color.
* Paint Buck Tool: Click the desired area to fill with the selected color.
* Crop Tool: Click in the top left corner and hold to the bottom right corner or desired crop area.
* Reset Tool: Double-click to reset the image back to default.

### Demo 
!!!!!!!!!!!!!!!!!!!!!

### Compile and Execute
* Navigate to the folder 'PrimitivePaintApplication' in the terminal
* Compile
~~~
cmake .
~~~
~~~
make
~~~
* Run the program with the test.png
~~~
./program1 test.png
~~~

## CoinCountingApplication
This program counts the amount of money in coins from images. The total is output in the terminal and the coin types are outlined in their respective colors. Pennies are red, nickles are yellow, dimes are blue, and quarters are green. Pictures must be taken from the same distance and angle to work properly. You can adjust the values on lines 79, 85, 91, and 97 to fit your image set.

### Features
* Outlines coin types with their respective colors.
* Counts the number of each type of coin in the image.
* Calculates the total money in the image.

### Demo
!!!!!!!!!!!!!!!!!!!!!!!!!!!

### Compile and Execute
* Navigate to the folder 'CoinCountingApplication' in the terminal
* Compile
~~~
cmake .
~~~
~~~
make
~~~
* Run the program with the desired image. Images 51Cents.jpg, 67Cents.jpg, 73Cents.jpg, 76Cents.jpg, and 78Cents.jpg are given in the folder to run the program with.
~~~
./program2 (image name here)
~~~

## BoxDimensionCalculator
This program identifies boxes on a table and calculates their dimensions from .ply files taken from above at a ~90 degree angle to the table top.

### Features
* Identifies the table plane and colors it blue.
* Identifies the tops of boxes and colors them red or blue.
* Calculates the dimensions of each box.
* Navigating the point cloud
  * Middle Mouse Scroll OR Right Mouse Hold and Drag - Zoom in or out.
  * Middle Mouse Scroll Hold and Drag - Change angle.
  * Left Mouse Hold and Drag - Rotate around the center.

### Demo
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

## Comple and Execute
* Navigate to the folder 'BoxDimensionCalculator' in the terminal
* Compile
~~~
cmake .
~~~
~~~
make
~~~
* Run the program with the desired .ply file. Files test1.ply, test2.ply, test3.ply, test4.ply, and test5.ply are given in the folder to run the program with.
~~~
./program4 (.ply file here)
~~~
