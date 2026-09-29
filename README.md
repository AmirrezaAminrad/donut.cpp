# donut.cpp

> A C++ version of the classic [`donut.c`](https://www.a1k0n.net/2011/07/20/donut-math.html) — a spinning 3D ASCII donut that fits in a terminal window, written in the shape of a donut.

`donut.cpp` renders a rotating torus using nothing but ASCII characters and a few lines of trigonometry. There are no graphics libraries, no dependencies beyond the C++ standard library, and the source code itself is laid out as a donut.

```text
             @@@@@@$
        $@@@@$$$#########
     #$$$$$$$$###**!!==!!***
    #$$$$$$$###**!===;=;;===!*
  !#$$$$$$###**!==;::::~::;=!!!!
  ##$$$$$###***!=;:~-,,.,-~:;=!!!
 *##########**!!;:~,......,~:;=!!!
=**########***!==:-.......,~:;=!**!
=!**#######***!==;-   ....,~;=!*#**
=!***######***!!=;:     ..~;!#####*!
;!!***********!!!=;:     -=*#$$$$$#!
;=!!***********!!!=;;    =*#$@@@$$#*
 ==!!!!*********!!!!====!*#$$@@@$$#!
 :===!!!!!!******!!!!!!!!**#$$$$$#*!
  :;==!!!!!!!!!!!!!!!!!****######*!:
   :;;==!!!!!!!!!!!!!!!*********!!;~
    ~:;;=====!!!!!!!!!!!!!!!!!!!=;~
     -~::;;============!=!====;=;~
       ,~~::;;;;;========;=;;;;~,
         .--~~:::::;;;:;;:::~~.
```

*One frame of the animation, captured from this program's output.*

## About

This is a port of Andy Sloane's ([a1k0n](https://www.a1k0n.net/)) famous obfuscated C program, `donut.c`, to C++. The algorithm and the donut-shaped layout are the same. The differences are on the language side:

- Uses the C++ standard headers `<cmath>`, `<cstdio>` and `<cstring>` instead of relying on old-style C declarations.
- Declares the loop variables inside their `for` statements.
- Builds as ordinary C++ and compiles without warnings under `g++ -Wall`.

For a full walkthrough of the math, read the original write-up: [Donut math: how donut.c works](https://www.a1k0n.net/2011/07/20/donut-math.html).

## Quick start

```sh
g++ -O2 donut.cpp -o donut
./donut
```

Press **Ctrl+C** to quit.

<details>
<summary>Other compilers</summary>

**Clang** (Linux, macOS):

```sh
clang++ -O2 donut.cpp -o donut
```

**MSYS2 / MinGW** (Windows):

```sh
g++ -O2 donut.cpp -o donut.exe
```

**MSVC** (Visual Studio Developer Command Prompt):

```bat
cl /O2 donut.cpp
donut.exe
```

</details>

## Requirements

| Requirement | Details |
|---|---|
| Compiler | Any C++ compiler with a standard library (GCC, Clang, MSVC) |
| Terminal size | At least **80 columns × 22 rows**. Smaller windows will wrap or distort the image |
| Terminal type | Must understand ANSI escape codes (clear screen and cursor-home) |

**Platform notes**

- **Linux / macOS:** any terminal works.
- **Windows:** use [Windows Terminal](https://aka.ms/terminal) or an MSYS2/mintty shell. Older console hosts may print the escape sequences as literal text unless virtual terminal processing is enabled.

## How it works

Each frame goes through the same steps:

1. **Sample the torus.** Two nested loops walk around the surface: `j` sweeps the small circle of the tube (step `0.07`) and `i` sweeps around the donut's central axis (step `0.02`). Together they cover a full `2π` (about `6.28`) in each direction.
2. **Rotate.** Every point is rotated by two angles, `A` and `B`, which grow a little each frame (`+0.04` and `+0.02`), giving the tumbling motion.
3. **Project.** A perspective divide (`D = 1/z`) maps the 3D point to a cell on an 80×22 character grid.
4. **Depth-test.** A z-buffer (`z[]`) keeps only the nearest point for each cell, so the front of the donut hides the back.
5. **Shade.** The surface normal is compared to a fixed light direction, and the result picks a character from the ramp `.,-~:;=!*#$@`, dark to bright.
6. **Draw.** The cursor is sent home (`\x1b[H`) and the whole buffer is printed in one go, which redraws in place without scrolling.

### Where the magic numbers come from

| Value | Meaning |
|---|---|
| `1760` | Number of character cells: 80 × 22 |
| `7040` | Size of the z-buffer in bytes: 1760 × `sizeof(float)` |
| `6.28` | Approximately 2π, a full revolution |
| `h = d + 2` | Distance of the tube centre from the donut centre (`R2 = 2`) plus the tube radius (`R1 = 1`) times `cos(j)` |
| `+ 5` in `D` | Distance from the viewer to the donut (`K2 = 5`) |
| `40`, `12` | Screen centre (column, row) |
| `30`, `15` | Horizontal and vertical scale. Vertical is halved because terminal cells are about twice as tall as they are wide |
| `8 * (…)` | Luminance scaled to index the 12-character ramp |

## Customising

The layout of the source is part of the charm, so edit with care, since changing the length of a line will bend the donut. A few safe tweaks:

| Change | Edit |
|---|---|
| Spin faster or slower | The increments `A+=.04` and `B+=.02` |
| Smoother or coarser surface | The step sizes `j+=.07` and `i+=.02` (smaller is smoother but slower) |
| Different shading | The ramp string `".,-~:;" "=!*#$@"` (keep it at 12 characters, or adjust the `8*` factor) |

### Frame rate

The program has no delay between frames, so it draws as fast as your CPU allows and will use a full core. To cap the speed, add `#include <thread>` and `#include <chrono>` at the top and put this line at the end of the main loop, next to `A+=.04;B+=.02;`:

```cpp
std::this_thread::sleep_for(std::chrono::milliseconds(30));
```

## Troubleshooting

| Symptom | Likely cause and fix |
|---|---|
| Garbage like `←[2J` on screen | The terminal is not interpreting ANSI codes. Switch to Windows Terminal, or another VT-capable terminal |
| Donut looks squashed or wraps | The window is smaller than 80×22. Enlarge it |
| Flickering | Try a GPU-accelerated terminal, and compile with `-O2` so each frame is built faster |
| Runs too fast | See [Frame rate](#frame-rate) above |

## Credits

- **Andy Sloane** ([a1k0n](https://www.a1k0n.net/)) — author of the original `donut.c` and the [Donut math](https://www.a1k0n.net/2011/07/20/donut-math.html) write-up this port is based on.

## License

Released under the [MIT License](LICENSE).
