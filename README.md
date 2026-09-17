# Padma Bridge — Night Scene (C++ / OpenGL / GLUT)

A real-time animated night scene of the Padma Bridge, rendered with legacy
immediate-mode OpenGL and GLUT. Features a day-night cycle, a car and a
train that follow the deck's and railway's curve (with heading-based
rotation), and animated water.

## Features

- Cable-stayed bridge rendered with hand-placed OpenGL polygons
- Day/night lighting cycle (sky gradient, water color, lamp glow, star
  visibility) driven by keyboard input
- Car and train that translate along the bridge deck / railway and rotate
  to match the local slope of the path
- Animated sine-wave water surface

## Dependencies

- A C++11-capable compiler (`g++`)
- `freeglut3-dev` (provides `GL/glut.h`, `libglut`, `libGLU`, `libGL`)

On Debian/Ubuntu:

```bash
sudo apt-get update
sudo apt-get install -y freeglut3-dev
```

## Build

```bash
g++ -std=c++11 main.cpp -o bridge -lGL -lGLU -lglut
```

## Run

```bash
./bridge
```

## Controls

| Key | Effect          |
|-----|-----------------|
| `1` | Jump to midnight |
| `2` | Jump to dawn     |
| `3` | Jump to noon     |
| `4` | Jump to dusk     |

The car and train animate continuously; the water waves animate
continuously and move right to left.

## Known limitations

- The `gluOrtho2D` projection range isn't proportional to the 1080×720
  window, so rotated geometry (the car, the train) is very slightly
  skewed (~9–10%) on screen. Not yet corrected.
- Road/railway paths that the car and train follow are reconstructed by
  hand from the deck/rail polygon vertices, not derived from a single
  source of truth — they're a close approximation, not exact.

## License

MIT (or replace with your preferred license before publishing).
