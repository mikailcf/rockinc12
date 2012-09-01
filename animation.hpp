#include <SFML/Graphics.hpp>

#ifndef ANIMATIO_HPP
#define ANIMATION_HPP

typedef struct{
    float duration, wait_before, wait_after;
    sf::Vector2f end;
    float t1, t2;
} sect;

class Animation{
    int n_secs;
    bool loop, on;
    float duration, start_time;
    sect *sections;

public:
    Animation(int n);

    void setSection(int n, float dur, float wait_before, float wait_after, sf::Vector2f end, float t1, float t2);
    void setLoop(bool lp);

    void start(float time);
    void stop();
    bool isOn();

    sf::Vector2f getPosition(float time);
};

#endif