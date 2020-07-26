# Growing Neural Network 

## Features

### Class Preprocessor
* Read Images.
* Gray Scale.
* Sobel Mask.

### Class Graph
* Graph implementation with adjacency list.
* Suports dynamic allocation. 

### Class GNG
* Hyperparams in GNG/config.h file.
* Growing Neural Network Algorithm implementation.

### Class GraphDrawer
* Draw graphs.
* Suports Image Reading.
* Suports Video Writing.

## Prerequisites

### Open CV
You have to install Open CV on your System. 

## Run
### GNG
Compile the proyect 

```
cd Tests 
g++ gngTest.cpp -o gng `pkg-config --cflags --libs opencv`
```
You can use the test images placed in Tests/InputImages/ folder.

The code below shows how to run GNG on image 1.
```
./gng img1.jpg
```

You can use your own image as well. Just place an image on Tests/InputImages/ folder with name image_name and run the code below.

```
./gng image_name
```
- The processed image will be stored on Tests/ResultImages directory.
- The video showing the evolution of the Neural Network will be stored in Tests/ResultVideos

## Results

See the video of result of tests [here](https://www.youtube.com/JH00gTNH76M) 

