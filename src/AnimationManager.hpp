/*
MIT License

Copyright (c) 2018 Jack Featherstone

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

DEPENDENCIES:
std::string
std::map
sf::Sprite
sf::Texture
sf::Vector2i/f

*/

#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <iostream>

using namespace std;
using namespace sf;
/*

SPECIFICATIONS:
SFML 2.5.1
2018 Q4

This class, which is to be used in conjunction with the SFML framework, will
help to smoothly integrate animation into a large scale game or other application.

Many of the functions of this class will not be especially complicated, though
they will hopefully simplify and increase readability for simple actions such
as character walking/moving animations, jumping animatimations, etc.

The basis of the code below will be the sf::Sprite class, the current documentation
for which is linked below:

https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Sprite.php

*/

class AnimationManager {
/*
The majority of information in this class will be contained in map types,
where the key will be a user defined string identifying what type of animation
is defiend there (walking, jumping, etc.)
*/
private:
  /*
  Since we don't know exactly what actions will be animated with this class, we
  will allow the user to define their own identifiable sprite sheets
  */
  map<string, Texture> m_textures;
  /*
  We will want to keep track of where we are in the spritesheet, again for each
  user-defined sheet
  We use a vector such that >1 column spritesheets can be used easily
  In the case that we are using a 1 column sheet, we should be able to tell through
  the size, and ignore the second index
  */
  map<string, Vector2i> m_indicies;

  /*
  Since some spritesheets will contain multiple sets of animations, we want to
  define a start index for all of our entries (though it may just be (0,0) for most)
  We also define where they end (which will usually just be the size of the sheet)
  */
  map<string, Vector2i> m_startingIndicies;
  map<string, Vector2i> m_endingIndicies;

  // The former will be for the number of frames in a sheet, while the latter
  // is the actual size of each frame in the sheets
  map<string, Vector2i> m_sheetSizes;
  map<string, Vector2i> m_spriteSizes;

  /*
  Since we will assume that every sheet will be updated every frame, we will
  allow for a frequency to be set such that we can control the speed of animations

  This values will be integers of the form where 1 (or 0) means it is updated
  every call, 2 is updated every other call, etc.
  */
  map<string, int> m_frequencies;

  /*
  Because of the frequency issue, we also have to keep track of how many times
  we have updated our sprites
  */
  map<string, int> m_timesUpdated;
public:
  AnimationManager();

  void update(string animation, Sprite& sprite);

  /*
  This method may not be used, as it would require the game to organize all of
  the animated sprites in a map, though it could be useful in a few situations,
  so there's no harm in programming it now (it shouldn't be that hard)
  */
  void updateAll(map<string, Sprite>& map);

  /*
  The overloaded methods below will be the main functionality as far as adding
  animations to the manager. The first will take in all necessary variables and
  create the entry at the same time, while the second will require supplementation
  by the setter methods below, otherwise they will maintain default values
  */
  void addAnimation(string animation, Texture texture, Vector2i sheetSize,
     Vector2i spriteSize, Vector2i index = Vector2i(0, 0), int frequency = 0,
    Vector2i startingIndex = Vector2i(0, 0));

  void deleteAnimation(string animation);

  void setAnimationFrequency(string animation, int frequency);
  void setAnimationSpriteSize(string animation, Vector2i size);
  void setAnimationSheetSize(string animation, Vector2i size);
  void setAnimationIndex(string animation, Vector2i index);
  void setAnimationTexture(string animation, Texture texture);
  void setAnimationStartingIndex(string animation, Vector2i index);
  void setAnimationEndingIndex(string animation, Vector2i index);


  void resetAnimationIndex(string animation);
};
