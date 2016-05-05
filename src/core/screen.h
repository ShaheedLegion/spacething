#ifndef _CORE_SCREEN_
#define _CORE_SCREEN_

#include <SFML/Graphics.hpp>

namespace core {
class Screen {
public:
  Screen() {}

  virtual void render(sf::Int32 elapsed, sf::RenderWindow *window) = 0;
};
}
#endif // _CORE_SCREEN_