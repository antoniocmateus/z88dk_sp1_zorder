# z88dk SP1 z order

Change sprite plane according to it's y order, simulating z-order

## Getting Started

Z-order is a concept that is present since the beginning of videogames: in a 3d world, sprites that are far away of the camera are drawed behind the ones closer to the camera. This concept can also be applied to a 2d world, if we're using depth in our scene.

We again use the possibility of changing the sp1_cs structure to modify the plane property on the fly.

## Description

For this, we're using 2 methods:

* sp1_IterateSprChar, which allows us to iterate through all the sprite graphics
* sp1_IterateUpdateSpr, to invalidate the sprite. You should see if invalidation is or not needed. In this example it's not, because both sprites are moving and SP1 autoimatically invalidates them. I''ll keep it commented nevertheless so you'll know how to do it

## Program

The code is fully documented and can be compiled with

```
zcc +zx -vn -startup=31 -clib=sdcc_iy sprites.asm int.c main.c -o test_bed -create-app
```

You also have a compiled TAP file. Use QAOP keys to move the bubble and see the sprites behaviour.

## License

You can freely use the code or ideas as you wish. I have commented most of it, you should be able to follow it easily.
If it helps you in any way, I'll be happy.

## Acknowledgments

As always

* [z88dk](https://z88dk.org/) - z88dk home
* [World of Spectrum forums](https://worldofspectrum.org/forums)


