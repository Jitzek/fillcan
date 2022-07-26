# Fillcan 
[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/Jitzek/fillcan/blob/main/LICENSE)
Fillcan is a C++20 library for rendering graphics using Vulkan.

- [Home Page](https://jitzek.github.io/fillcan/)
- [Documentation](https://jitzek.github.io/fillcan/documentation)

## About the library
![](https://user-images.githubusercontent.com/43340162/136829908-d752617e-49b9-487d-bb74-ee59acf96a2b.png)

Fillcan aims to be a object-oriënted solution for communicating with the Vulkan API. It's main goals are as follows:
- Decrease the boilerplate code needed for talking with Vulkan.
- Handle the allocation and deallocation of memory within the objects that require it. Automatically deallocate memory once the object goes out of scope.
- Don't take away control from the user. Allow as many parameters to be tweaked by the application that implements the library.

### License
Fillcan is [MIT licensed](https://github.com/Jitzek/fillcan/blob/main/LICENSE);

## About the developer
Fillcan is the result of a school project requiring the student (me) to get familiar with computer graphics.
For this project I have written a 400+ page document researching Vulkan and designing a basic implementation. This document has taken a lot of information from the "Vulkan programming guide" written by Graham Sellers.

My main goal was to understand Vulkan enough to write my own implementation without the use of a tutorial (though I have taken inspiration from [Vulkan Tutorial](https://vulkan-tutorial.com/)). This project was and is never meant to be used within a production environment and will likely never reach a version 1.0 release, it is merely a learning experience for a curious software developer.