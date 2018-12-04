
# SFML Animation Manager

This is a pretty simple class that allows for an easy way to animate sprites in a game based on the SFML Graphics library. An example of its usage is shown below, though essentially the player will create an instance of animation manager and can add their own unique entries to it, with the option to update every frame (or some other frequency).

# Example code:

This code below will create an instance of the animation manager, and add an entry called "Walking". We will then set some conditions for the animation, and update it in some game loop

```
#include "AnimationManager.hpp"
...

// Load our animation sheet texture
Texture animationSpritesheet;
animationSpritesheet.loadFromFile("path/to/file.png");

// Set the number of frames in the sheet
Vector2i frameRectange(4, 4); // A total of 16 frames

// Set the size of each frame of our animation
Vector2i spriteSize(64, 64);

// Create our animation manager instance
AnimationManager am;
am.addAnimation("Walking", animationSpritesheet, frameRectangle, spriteSize);
/*
This would be the same as adding each section individually:
am.setAnimationTexture("Walking", animationSpritesheet);
am.setAnimationSheetSize("Walking", frameRectangle);
am.setAnimationSpriteSize("Walking", spriteSize);
*/

...
// Our game loop somewhere else in the code
while (window.isOpen()) {
  ...
  am.update("Walking"); // Change to the next frame in the animation
  ...
}
```

# Optional fields

There are four other fields that we did not include in the example code above: frequency, starting/ending index, and current index. As is, the code above will update the sprite by one frame every iteration through the game loop. If we wanted the sprite to only update every other frame (and therefore be animated slower) we could add:
`am.setAnimationFrequency("Walking", 2); // Update every other call`

or

`am.setAnimationFrequency("Walking", 3) // Update every 3rd call`

If we wanted to start the animation halfway through the process, we could also set the index of the animation (either through the constructor or setter below):
`am.setAnimationIndex("Walking", Vector2i(2, 0)) // Start halfway through our 4x4 sheet`

In this same vein, we can also reset the index to start the animation over:
`am.resetAnimationIndex("Walking");`

No need to do this often though, as the animation automatically resets once it reaches the last frame!

If we have a single sprite sheet with more than one animation in it, we can also specify where the animation will start and end. These have there own separate setters, shown below!
`am.setAnimationStartingIndex("Walking", Vector2i(4, 4)); // Maybe we have another animation set in the same file as before, after the other set`

and

`am.setAnimationEndingIndex("Walking", Vector2i(8, 4))``

Finally, we can remove entries from the manager, using the `am.deleteAnimation("Walking")` method. This isn't entirely crucial, as it shouldn't interfere with other animations, though it may improve performance time.

# Full constructor:

```
void addAnimation(string animation, Texture texture, Vector2i sheetSize,
   Vector2i spriteSize, Vector2i index = Vector2i(0, 0), int frequency = 0,
   Vector2i startingIndex = Vector2i(0, 0));
```
