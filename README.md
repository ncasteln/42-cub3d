# cub3D

cub3D is a project developed for 42 Heilbroon School.

## Keywords
C programming - ray casting - videogames - MLX42 library - map parsing - flood fill

<div align="center">
	<img src="./raycast.gif" alt="Short video example of the game">
</div>

## Subject
In this project we had to create a videogame using the raycasting technique, C programming language and the [MLX42 Codam library](https://github.com/codam-coding-college/MLX42.git). For more info about the requirements, take a look at the [subject](en.subject.pdf) contained in this repo.

## Brief explanation
The project covers the following topics:

### 1. Map parsing
As the project subject specifies, the input map has to be correctly validated: map file format, texture identifier with correct paths and values, map sourrounded by walls, the existence of one Player (without duplicates). During the parser, the data is collected and stored into a so called `t_cub3d` structure. A thing that we handled in a particular way were the whitespaces inside the map. Since the subject doesn't specify exactly what to do about them, we decided to put a sprite in those spaces (something like an obstacle), and make them not walkable.

### 2. Use of the graphical library
It was mandatory the use of MLX42 library, which handles the window and the images. For a deeper knowledge, I suggest to give a read to the official documentation of [MLX42](https://github.com/codam-coding-college/MLX42.git).

### 3. Raycasting
The core part in this project: *raycasting*. If you don't know what it is, you can start from the [wiki](https://en.wikipedia.org/wiki/Ray_casting) page and try out the most famous videogame done with this technique: _Wolfenstein 3D_.

### 4. Leaks free
Like in any other project of 42, the memory allocated by has to be properly freed. No leaks are tolerated during evaluation. In this project I checked the leaks using a project of a school mate, which re-implements the `malloc()` function and traces the allocated memory. Take a look at the amazing project of [iwillenshofer](https://github.com/iwillenshofer/leak_finder).

## 5. Testing
We built a mini-tester to have everything under control after debugging, cleaning and refctoring. So after some modifications, we could run the tester and check if everything was _green_ as expected. The tester is written in `bash` scripting.

## Bonus
In the bonus part of the project we had to first implement the wall collisions (you understand correctly, we could take 100% also without wall collisions). We decided also to create doors which can be open and closed. The subject specified to create another separated version of the program, but we decided to develop it slightly different. We just added a particular rule in the `Makefile` which define a constant `BONUS` only when this rule is called. Then, in the program code, we added the functionalities by checking if this `BONUS` flag was set or not.

## Randoom
Try `make randoom`, a custom rule to put random texture inspired by the world of the original _Doom_ (which actually is not made with pure raycasting).

---

## Try it out
_Importante note_: the game is developed at 42 school on macOS and it's not optimized to be executed on other platform. Because of this you'll have to wait until I mupdate the `Makefile` to set the correct dependencies and compilation flags.

1. Clone the repository:
```
git clone https://github.com/ncasteln/42-cub3d
```
2. Navigate to the `cub3d` directory and `make` program, or `make bonus` for more funcionalities:
```
cd 42-cub3d
make bonus
```
According to the Makefile, this should compile the program, using the local version of the library. To get an idea about the dependencies of the library, I suggest again to read the [MLX42](https://github.com/codam-coding-college/MLX42.git) documentation.

3. Execute it, passing a valid map as argument:
```
./cub3D maps/bonus_valid/bonus_9.cub
```
4. Move the player using `WASD`, rotate with `arrows` and terminate the program using `Esc`.

5. Don't be scared about the doomed world, it's just a game

## Useful resources
[lodev.org](https://lodev.org/cgtutor/raycasting.html) about raycasting, was our main tutorial to build it.
