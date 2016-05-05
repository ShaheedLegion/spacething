#include "app/intro_screen.h"
#include "core/core.h"

namespace app {

// const std::string bg_img = "resources/background.jpg";
const std::string font_name = "resources/sansation.ttf";
const std::string texture_name = "resources/texture.png";

IntroScreen::~IntroScreen() {}

IntroScreen::IntroScreen(sf::RenderWindow *window)
    : core::Screen(), field(200) {
  core::States *states{core::States::getInstance()};

  // states->addTexture(bg_img);
  // background.setTexture(states->getTexture(bg_img));
  /*
  states->addFont(font_name);
  sf::Font &font = states->getFont(font_name);

  // Create some text to draw on top of our stuff.
  text = sf::Text("SpaceThing Demo", font);
  text.setColor(sf::Color(255, 255, 255, 170));
  text.setPosition(250.f, 450.f);

  states->addTexture(texture_name);
  texture.setTexture(states->getTexture(texture_name));
  */
}

StarField::StarField(int numStars) {
  // add stars here.
  // we will use some magic numbers here to make it look good ...
  srand(static_cast<unsigned int>(2635));
  for (int i = 0; i < numStars; ++i) {
    pos p{
        ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 70.f) -
            35.f,
        ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 70.f) -
            35.f,
        ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 100.f) -
            1.f,
        0.f, 0, 0};
    p.s = (p.z * 0.001f) + .2f;

    stars.push_back(p);
  }
}

void StarField::update(int w, int h) {
  for (int i = 0; i < stars.size(); ++i) {
    pos &p{stars[i]};

    p.y += p.s;

    // perspective projection.
    p.tx = (p.x / p.z) * w + (w >> 1);
    p.ty = (p.y / p.z) * h + (h >> 1);

    // clamp the star.
    if (p.tx < 10 || p.tx > w) {
      p.tx = 2;
      p.x =
          ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 70.f) -
          35.f;
    }
    // if (p.ty < -2)
    //  p.ty = h - 2;
    if (p.ty > h) {
      p.ty = 2;
      p.y = -37.f;
      p.x =
          ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 70.f) -
          35.f;
    }
  }
}

void IntroScreen::render(sf::Int32 elapsed, sf::RenderWindow *window) {
  /*
  std::pair<float, float> p;
  core::States::getInstance()->getMousePos(p);
  texture.setPosition(p.first, p.second);
  */
  field.update(window->getSize().x, window->getSize().y);

  // background.setColor(sf::Color());
  // define a circle with radius = 200
  sf::CircleShape circle(3);
  circle.setFillColor(sf::Color(255, 255, 255, 128));
  // change the radius to 40
  // circle.setRadius(40);

  // change the number of sides (points) to 100
  // circle.setPointCount(100);
  // sf::Texture& back{core::States::getInstance()->getTexture(bg_img)};
  std::vector<StarField::pos> &stars{field.getStars()};
  for (auto star : stars) {
    circle.setPosition(static_cast<float>(star.tx),
                       static_cast<float>(star.ty));
    window->draw(circle);
  }

  // window->draw(texture);
  // window->draw(text);
}
}
