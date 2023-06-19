#include <iostream>
#include <fstream>
#include "SFML/Graphics.hpp"
#include "Math.h"
#include <random>
#include "Shape.h"
#include "Camera.h"

int main() {
    Camera<3840, 2160> camera;
    std::vector<Shape *> objects;
//    Sphere sphere({0, 0, 0}, 0.7);
//    objects.push_back(&sphere);
    CubeWithoutSphereCicled cube({0, 0, 0}, 3, 0.69);
//    CubeWithoutSphereCicled cube({0, 4, 0}, 1);
    objects.push_back(&cube);
//    Floor floor(-10);
//    objects.push_back(&floor);
//RandomSphere randomSphere({4, 0, 0}, 1);
//    objects.push_back(&randomSphere);
//    BasicMandelbrot bm(0);
//    objects.push_back(&bm);
//    CycledThorus thorus({0,0,0}, 3, 1);
//    objects.push_back(&thorus);

    camera.setPos({-8, 0.5, 20});
    camera.setDir({Math::dtor(20), Math::dtor(120)});

    sf::Texture texture;
    texture.create(camera.getSize().x, camera.getSize().y);
    sf::Sprite sprite(texture);
    camera.frame(objects);
    texture.update(camera.getScreen());
    texture.copyToImage().saveToFile("../gallery/" + std::to_string(std::time(0)) + ".png");
//    sf::RenderWindow window(sf::VideoMode(camera.getSize().x, camera.getSize().y), "Ray Marching");
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//        }
//        window.clear();
//        window.draw(sprite);
//        window.display();
//    }
}
