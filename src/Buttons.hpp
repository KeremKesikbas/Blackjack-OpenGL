#ifndef BUTTONS_HPP
#define BUTTONS_HPP

#include "Transform.hpp"
#include "Card.hpp"

#include "stats.hpp"

class StandButton {
    public:
        StandButton();

        void renderStand();
        void eventStand(CardManager* cm);

    private:
        Shape* rect;

        int w = 150;
        int h = 60;

        int x = WIDTH/2 - 100 - w;
        int y = HEIGHT/2 - h/2;

        int tX;
        int tY;
};

class HitButton {
    public:
        HitButton();

        void renderHit();
        void eventHit(CardManager* cm);

    private:
        Shape* rect;

        int w = 150;
        int h = 60;

        int x = WIDTH/2 + 100;
        int y = HEIGHT/2 - h/2;

        int tX;
        int tY;
};

class RestartButton {
    public:
        RestartButton();

        void renderRestart();
        void eventRestart(CardManager* cm);

    private:
        Shape* icon;
        Shape* rect;

        int w = 60;
        int h = 60;

        int x = WIDTH/2 - 270 - w;
        int y = HEIGHT/2 - h/2;
};

#endif