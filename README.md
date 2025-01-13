<h1 align="center">
	📖 so_long
</h1>

```
This project is a very small 2D game.
Its purpose is to make you work with textures, sprites,
and some other very basic gameplay elements.
```

## Description
So long is a simple 2D game. It's purpose is to familiralize yourself with game mechanics, mlx42 library as well as managing larger scale projects.

[![so_long demo](https://res.cloudinary.com/marcomontalbano/image/upload/v1736770089/video_to_markdown/images/youtube--c3kqH85pSE8-c05b58ac6eb4c4700831b2b3070cd403.jpg)](https://youtu.be/c3kqH85pSE8 "so_long demo")

## Compile and Run

There are two versions of the program, the mandatory part and the bonus part. Bonus part adds monsters (birds) that kill you and wake up when the player is close as well as sprite animations.

`❗note` : we cannot gurantee that it will work on windows devices, it should run on mac and linux just fine.

To compile the mandatory part, `cd` into the cloned directory and:

```shell
make
```

To compile the bonus part, `cd` into the cloned directory and:

```shell
make bonus
```

To run the program:

```shell
./so_long <path/to/map.ber>
```

The program takes a map file as an argument. Maps are available in the `maps` directory. There are valid maps which the program should run smoothly with, and invalid maps which the program should reject.
For example:

- `./so_long maps/valid/map_1.ber` should run.

- `./so_long maps/invalid/empty.ber` should print an error and abort.

## Controls

Controls for movement and rotation are:

- `W`: move forward
- `S`: move backward
- `A`: move left
- `D`: move right
- `left arrow`: rotate left
- `right arrow`: rotate right
- `mouse`: rotate by moving the mouse (bonus only)
