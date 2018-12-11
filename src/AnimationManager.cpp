#include "AnimationManager.hpp"

// Map definitions
map<string, Texture> AnimationManager::m_textures;
map<string, Vector2i> AnimationManager::m_indicies;
map<string, Vector2i> AnimationManager::m_startingIndicies;
map<string, Vector2i> AnimationManager::m_endingIndicies;
map<string, Vector2i> AnimationManager::m_sheetSizes;
map<string, Vector2i> AnimationManager::m_spriteSizes;
map<string, int> AnimationManager::m_frequencies;
map<string, int> AnimationManager::m_timesUpdated;


/*
update(string animation, Sprite& sprite)

animation - This is the string key that corresponds to the animation we are updating

sprite - This sprite will have its texture changed to the next one in its
  animation sequence
*/
void AnimationManager::update(string animation, Sprite &sprite) {
  // First, we want to locate our animation in the map
  // We look at the sheet size because that is the easiest indicator to tell if
  // there is actually an entry
  if (m_sheetSizes[animation] != Vector2i(0, 0)) {
    // We want to do a few calculations to find the coordinates of the next frame
    IntRect rect(m_indicies[animation].x * m_spriteSizes[animation].x,
       m_indicies[animation].y * m_spriteSizes[animation].y,
        m_spriteSizes[animation].x, m_spriteSizes[animation].y);

    // Now we want to update the indicies based on the format of our sheet
    // If we are not at the bottom of a column, we just move down one in y
    if (m_indicies[animation].y < m_sheetSizes[animation].y) {
      m_indicies[animation].y++;
    } else {
      // Otherwise, we move over one column and go back to the top
      m_indicies[animation].y = 0;
      m_indicies[animation].x++;
      // And then reset the sheet if we are past the width of the sheet
      if (m_indicies[animation].x >= m_sheetSizes[animation].x)
        m_indicies[animation].x = 0;
    }

    // Now we update the texture on our sprite reference
    sprite.setTexture(m_textures[animation]);
    sprite.setTextureRect(rect);

  } else {
    // If we didn't find an entry
    cout << "No animation entry found for \"" << animation << "\"!" << endl;
  }
}

/*
updateAll(map<string, Sprite> &map)

map - This should be a map of string and sprite pairs, all of which that are found
  in the local map will be updated

This is essentially just an extension of the previous method, in that it just
iterates through
*/
void AnimationManager::updateAll(map<string, Sprite> &map) {
  // Really not much to do here, most is in the previous method
  for (auto element: map) {
    update(element.first, element.second);
  }
}

/*
ADDING & DELETING
The following methods are for adding and deleting entries and animations
*/

/*
addAnimation(string animation, Texture texture)

animation - The string key for the animation we are adding
texture - The spritesheet that will be associated with our animation
sheetSize - The vector containing the number of animation frames in our image
  - NOTE: all sheets must be rectangular
*/
void AnimationManager::addAnimation(string animation, Texture texture,
   Vector2i sheetSize, Vector2i spriteSize, Vector2i index, int frequency,
   Vector2i startingIndex) {
  // First, we want to make an entry in the texture map
  m_textures[animation] = texture;
  // Next, we make sheet size entry
  m_sheetSizes[animation].x = sheetSize.x;
  m_sheetSizes[animation].y = sheetSize.y;

  // Next, we make sprite size entry
  m_spriteSizes[animation].x = spriteSize.x;
  m_spriteSizes[animation].y = spriteSize.y;

  // Our index vector
  m_indicies[animation].x = index.x;
  m_indicies[animation].y = index.y;

  // Our starting index vector
  m_startingIndicies[animation].x = startingIndex.x;
  m_startingIndicies[animation].y = startingIndex.y;

  // Our ending index vector
  m_endingIndicies[animation].x = sheetSize.x;
  m_endingIndicies[animation].y = sheetSize.y;

  // Our update rate (frequency)
  m_frequencies[animation] = frequency;
  // We don't need to initialize the times udpated because its default is 0
}

/*
deleteAnimation(string animation)

animation - The string key for the animation set we are removing

Essentially this method just removes all entries for the animation provided
If this is not called, there won't be a functional difference, but it *may*
speed up the time it takes to run certain methods
*/

void AnimationManager::deleteAnimation(string animation) {
  // We just erase each entry in every map
  m_textures.erase(animation);
  m_indicies.erase(animation);
  m_startingIndicies.erase(animation);
  m_sheetSizes.erase(animation);
  m_spriteSizes.erase(animation);
  m_frequencies.erase(animation);
  m_timesUpdated.erase(animation);
  m_endingIndicies.erase(animation);
  // Ez pz
}

/*
Here are a whole bunch of setters for any given animation instance
Nothing too special about any of them in particular, and they all follow the
same form
*/

void AnimationManager::setAnimationFrequency(string animation, int frequency) {
  m_frequencies[animation] = frequency;
}

void AnimationManager::setAnimationIndex(string animation, Vector2i index) {
  m_indicies[animation].x = index.x;
  m_indicies[animation].y = index.y;
}

void AnimationManager::setAnimationSheetSize(string animation, Vector2i size) {
  m_sheetSizes[animation].x = size.x;
  m_sheetSizes[animation].y = size.y;
}

void AnimationManager::setAnimationSpriteSize(string animation, Vector2i size) {
  m_spriteSizes[animation].x = size.x;
  m_spriteSizes[animation].y = size.y;
}

void AnimationManager::setAnimationTexture(string animation, Texture texture) {
  m_textures[animation] = texture;
}

void AnimationManager::resetAnimationIndex(string animation) {
  m_indicies[animation].x = m_startingIndicies[animation].x;
  m_indicies[animation].y = m_startingIndicies[animation].y;
}

void AnimationManager::setAnimationStartingIndex(string animation, Vector2i index) {
  m_startingIndicies[animation].x = index.x;
  m_startingIndicies[animation].y = index.y;
}

void AnimationManager::setAnimationEndingIndex(string animation, Vector2i index) {
  m_endingIndicies[animation].x = index.x;
  m_endingIndicies[animation].y = index.y;
}
