# cub3D - My First RayCaster with miniLibX

## Summary

cub3D is a project focused on creating a 3D graphical representation of a maze from a first-person perspective using Ray-Casting principles and the miniLibX library.

## Version

Version: 1.0

## Contents

- [Chapter I - Introduction](#chapter-i-introduction)
- [Chapter II - Common Instructions](#chapter-ii-common-instructions)
- [Chapter III - Mandatory Part](#chapter-iii-mandatory-part)
- [Chapter IV - Bonus Part](#chapter-iv-bonus-part)
- [Chapter V - Submission and Peer-evaluation](#chapter-v-submission-and-peer-evaluation)

## Chapter I - Introduction

cub3D allows you to create a 3D maze visualization with realistic rendering techniques using Ray-Casting. It's an introductory project into graphical programming and game development concepts.

## Chapter II - Common Instructions

- Your project must be written in C.
- Adhere to the Norm for coding style and conventions.
- Functions should handle errors gracefully without crashing.
- All dynamically allocated memory must be freed appropriately to avoid leaks.
- Use a Makefile to compile your project with flags `-Wall -Wextra -Werror`.
- Makefile must include: `all`, `clean`, `fclean`, `re`, `bonus`.
- Include a `bonus` rule in Makefile for additional functionalities.
- If applicable, include a `libft` folder with its Makefile to compile the library.
- Create test programs to validate project functionality (not graded but useful for defense).
- Submit your work to the assigned git repository. Only contents of the repository are graded.

## Chapter III - Mandatory Part

### Program Details

Program name: `cub3D`

### Turn in files

- All your files

### Makefile Requirements

- `all`, `clean`, `fclean`, `re`, `bonus`

### Arguments

- A map in format `*.cub`

### External functions allowed

- `open`, `close`, `read`, `write`, `printf`, `malloc`, `free`, `perror`, `strerror`, `exit`, `gettimeofday`
- All functions of the math library (`-lm`)

### Libft authorized

Yes

### Description

cub3D functionalities:
- Create a 3D representation of a maze using Ray-Casting techniques.
- Use miniLibX for graphical output.
- Display different wall textures based on orientation.
- Set floor and ceiling colors.
- Allow user interaction:
  - Use arrow keys to look left/right.
  - Use W, A, S, D keys to move through the maze.
  - ESC key and window closing to exit the program.
- Parse scene description from a `.cub` file specifying textures, colors, and map layout.

### Evaluation

Ensure the program handles all specified functionalities correctly and gracefully handles errors.

## Chapter IV - Bonus Part

### Additional Features (Optional)

- Implement additional functionalities if the mandatory part is perfect:
  - Wall collisions.
  - Minimap system.
  - Interactive doors.
  - Animated sprites.
  - Mouse-based point of view rotation.
  
### Note

Bonus part evaluated only if mandatory part is perfect.

## Chapter V - Submission and Peer-evaluation

Submit your work to the assigned git repository. Peer evaluations may follow before final grading.

