# :rainbow: RS07-spectrum :rainbow:

![green_screenshot](screenshots/06_2017-06-05.gif)

## :page_facing_up: Description
This is a Software Development course project - 2D-platform-puzzle game.

Written in C++ using Qt 5.8

Created by:
- [Milana Kovacevic](https://github.com/milana-kovacevic)
- [Ivan Nedic](https://github.com/asdf12346)
- [Ivan Ristovic](https://github.com/ivan-ristovic)

## :computer: Installation
Clone the repository, run `qmake` from the repository root to generate a `Makefile`, and then run `make`:
```sh
$ git clone https://github.com/ivan-ristovic/Spectrum.git
$ cd Spectrum
$ qmake
$ make
```

## :page_facing_up: Description
Spectrum is a 2D puzzle game.
Each level is made of different elements, in a different color. You can choose one color as "active" and hide all objects which have that color.
By progressing through the game you will unlock more and more colors, allowing you to use more colors.

## :video_game: Usage
| **Key** | **Description** |
| :---  | :--- |
| ```Left``` , ```A``` | Move left |
| ```Right``` , ```D``` | Move right |
| ```Up``` , ```W``` | Climb ladder |
| ```Down``` , ```S``` | Stop player movement |
| ```Space``` | Jump |
| ```Mouse left/right``` | Open color change spectrum |
| ```ESC``` | Pause / Game Menu |

## :bug: Known bugs
* ~~Collision is not perfect (yet), so sometimes you might get inside a block.~~ It was a feature... removed.
