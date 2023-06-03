#include <iostream>
#include <fstream>
#include "SFML/Graphics.hpp"
#include "Math.h"
#include <random>
#include "Object.h"
#include "Camera.h"

int main() {
    Camera<400, 400> camera;
    std::vector<Object *> objects;
    Sphere sphere({0, 0, 0}, 1);
    Sphere sphere2({-0.6, 0.6, 0.6}, 0.5f);
    Sphere sphere3({-0.6, 0.6, -0.6}, 0.5f);
    Sphere sphere4({-0.6, -0.6, 0.6}, 0.5f);
    Sphere sphere5({-0.6, -0.6, -0.6}, 0.5f);
    objects.push_back(&sphere);
    objects.push_back(&sphere2);
    objects.push_back(&sphere3);
    objects.push_back(&sphere4);
    objects.push_back(&sphere5);

    camera.setPos({-3, 0, 0});
    camera.setDir({0, Math::dtor(90)});

    sf::Texture texture;
    texture.create(camera.getSize().x, camera.getSize().y);
    sf::Sprite sprite(texture);
    sf::RenderWindow window(sf::VideoMode(camera.getSize().x, camera.getSize().y), "Ray Marching");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        camera.frame(objects);
        texture.update(camera.getScreen());
        window.clear();
        window.draw(sprite);
        window.display();
    }
}
