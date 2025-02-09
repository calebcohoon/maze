# Style Guide

### File Organization
1. Header Files
```c
/*
 * Component Name
 * 
 * Brief description of the component's purpose
 */

#ifndef COMPONENT_NAME_H
#define COMPONENT_NAME_H

/* Includes */

/* Constants and Macros */

/* Type Definitions */

/* Function Prototypes */

#endif /* COMPONENT_NAME_H */
```

2. Source Files
```c
/*
 * Component Name
 * 
 * Implementation details
 */

/* Includes */

/* File-scope Constants */

/* File-scope Variables */

/* Function Implementations */
```

### Naming Conventions
1. Functions:
   - Lower case with underscores
   - Verb first for actions
   - Example: `set_video_mode()`, `draw_triangle()`

2. Constants/Macros:
   - Upper case with underscores
   - Example: `SCREEN_WIDTH`, `MAX_ENTITIES`

3. Variables:
   - Lower case with underscores
   - Descriptive names
   - Example: `player_position`, `screen_buffer`

4. Types:
   - Snake case with _t suffix
   - Example: `vector3_t`, `entity_t`

### Documentation
1. File Headers:
```c
/*
 * Component Name
 * 
 * Detailed description of component purpose and functionality
 * Include any notable algorithms or techniques used
 */
```

2. Function Documentation:
```c
/*
 * function_name: Brief description of purpose
 * 
 * Parameters:
 *   param1 - Description of first parameter
 *   param2 - Description of second parameter
 * 
 * Returns:
 *   Description of return value
 * 
 * Notes:
 *   - Any important implementation details
 *   - Performance considerations
 *   - Limitations
 */
```

3. Constants and Macros:
```c
/* Group description */
#define CONSTANT_ONE   1    /* Description of constant */
#define CONSTANT_TWO   2    /* Description of constant */
```

### Code Organization
1. Indentation: 4 spaces (no tabs)
2. Maximum line length: 100 characters
3. Spacing:
   - Space after keywords (if, for, while)
   - Space after commas
   - Spaces around operators
   - No space between function name and parenthesis

### Example:
```c
/*
 * video.h
 * 
 * Video mode and graphics handling for Mode 13h
 */

#ifndef VIDEO_H
#define VIDEO_H

/* Screen dimensions */
#define SCREEN_WIDTH    320    /* Mode 13h width in pixels */
#define SCREEN_HEIGHT   200    /* Mode 13h height in pixels */
#define SCREEN_SIZE     (SCREEN_WIDTH * SCREEN_HEIGHT)

/*
 * set_video_mode: Changes the current video mode
 * 
 * Parameters:
 *   mode - Desired video mode (0x13 for 320x200, 0x03 for text)
 */
void set_video_mode(unsigned char mode);

#endif /* VIDEO_H */
```
