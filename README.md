# ComputerVisionProjects

### Table of Contents
1. [Description](#Description)
2. [PrimitivePaintApplication](#PrimitivePaintApplication)
3. [CoinCountingApplication](#CoinCountingApplication)

## Description
This repository is a collection of mini computer vision projects completed over the summer of 2023. These were developed on a 64-bit Ubuntu machine.

## Clone Repository
~~~
$ git clone https://github.com/faithg3/ComputerVisionProjects.git
~~~
## PrimitivePaintApplication
This application is a very primitive version of Paint installed on Windows machines.

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
* Navigate to the folder 'PrimitivePaintApplication' in the termial
* Compile
~~~
cmake
~~~
~~~
make
~~~
* Run the program with the test.png
~~~
./program1 test.png
~~~

## CoinCountingApplication
This application counts the amount of money in coins from images. The total is output in the terminal and the coin types are outlined in their respective colors. Pennies are red, nickles are yellow, dimes are blue, and quarters are green. Pictures must be taken from the same distance and angle to work properly. You can adjust the values on lines 79, 85, 91, and 97 to fit your image set.

### Features
* Edge detection is run on the input image.
* Contours are found using the edges.
* A minimum bounding rectangle is fitted to each contour.
* An ellipse is created within said rectangle.
* The width of each coin is calculated from the ellipses.
* The count is output in the terminal and the identified coins are output in an image.

### Demo
!!!!!!!!!!!!!!!!!!!!!!!!!!!

### Compile and Execute
* Navigate to the folder 'CoinCountingApplication' in the termial
* Compile
~~~
cmake
~~~
~~~
make
~~~
* Run the program with the desired image. 51Cents.jpg, 67Cents.jpg, 73Cents.jpg, 76Cents.jpg, and 78Cents.jpg are given in the folder to run the program with.
~~~
./program2 (image name here)
~~~
