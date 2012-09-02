#include "animation.hpp"

Animation::Animation(int n){
    n_secs = n;
    sections = (sect *) malloc(n*sizeof(sect));
}

void Animation::setSection(int n, float dur, float wait_before, float wait_after, sf::Vector2f end, float t1, float t2){
    sections[n].duration    = dur;
    sections[n].wait_before = wait_before;
    sections[n].wait_after  = wait_after;
    sections[n].end         = end;
    sections[n].t1          = t1;
    sections[n].t2          = t2;

    loop = false;
    on   = false;

    duration += dur + wait_after + wait_before;
}

void Animation::setLoop(bool lp){
    loop = lp;
}

void Animation::start(float time){
    if(on == false){
        on = true;
        start_time = time;
    }
}

void Animation::stop(){
    if(on == true) on = false;
}

bool Animation::isOn(){
    return on;
}

sf::Vector2f Animation::getPosition(float time){
    int i;
    float sect_time;
    sf::Vector2f pos(0.0, 0.0);

    if(on == false) return pos;

    time -= start_time;

    if(loop){
        while(time > duration) time -= duration;
    }

    i = 0;
    sect_time = sections[i].wait_before + sections[i].duration + sections[i].wait_after;
    while(time > sect_time){
        pos += sections[i].end;
        time -= sect_time;
        i++;
        if(i == n_secs) return pos;
        sect_time = sections[i].wait_before + sections[i].duration + sections[i].wait_after;
    }

    float dur = sections[i].duration;
    float t1 = sections[i].t1;
    float t2 = sections[i].t2;
    float wait_before = sections[i].wait_before;
    sf::Vector2f end = sections[i].end;

    if(time > wait_before) time -= wait_before;
    else return pos;

    float vx = 2.0 * end.x/(dur * (1.0 + t2 - t1));
    float vy = 2.0 * end.y/(dur * (1.0 + t2 - t1));

    if(time > dur) pos += end;
    else if(time > dur * t2){
        pos.x += dur * t1 * dur * t1 * end.x/(dur * dur * t1 * (1.0 + t2 - t1));
        pos.y += dur * t1 * dur * t1 * end.y/(dur * dur * t1 * (1.0 + t2 - t1));

        pos.x += (dur * (t2 - t1)) * 2.0 * end.x/(dur * (1.0 + t2 - t1));
        pos.y += (dur * (t2 - t1)) * 2.0 * end.y/(dur * (1.0 + t2 - t1));

        pos.x += vx * (time - dur * t2) * (1.0 - (time - dur * t2)/(2.0 * dur * (1.0 - t2)));
        pos.y += vy * (time - dur * t2) * (1.0 - (time - dur * t2)/(2.0 * dur * (1.0 - t2)));
    }
    else if(time > dur * t1){
        pos.x += dur * t1 * dur * t1 *end.x/(dur * dur * t1 * (1.0 + t2 - t1));
        pos.y += dur * t1 * dur * t1 *end.y/(dur * dur * t1 * (1.0 + t2 - t1));

        pos.x += (time - (dur * t1)) * vx;
        pos.y += (time - (dur * t1)) * vy;
    }
    else{
        pos.x += time * time * end.x/(dur * dur * t1 * (1.0 + t2 - t1));
        pos.y += time * time * end.y/(dur * dur * t1 * (1.0 + t2 - t1));
    }

    return pos;
}
