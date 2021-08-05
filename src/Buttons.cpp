#include "Buttons.hpp"

#include "Graphics.hpp"
#include "Input.hpp"
#include "TextureManager.hpp"

using namespace graphics;

bool controlStand = false;
bool controlHit = false;
bool controlRestart = false;

bool isGameOver = false;

StandButton::StandButton() {
    rect = g->createRectangle(w, h);

    rect->setX(x);
    rect->setY(y);

    rect->setColor(0, 150, 20, 255);

    float tW;
    float tH;

    fonts::open_sans->getTextSize("Dur", tW, tH, 0.7);

    tX = x + w/2 - tW/2;
    tY = y + h/2 + tH/2;
}

void StandButton::renderStand() {
    rect->draw();

    g->setPosition(tX, tY);
    g->renderText("Dur", 0.7);
}

void StandButton::eventStand(CardManager* cm) {
    if (inputManager::mouse_input->x > x && inputManager::mouse_input->x < x + w 
        && inputManager::mouse_input->y > y && inputManager::mouse_input->y < y + h) {

            rect->setColor(0, 100, 10, 255);

            if (inputManager::buttonPressed(GLFW_MOUSE_BUTTON_1) && !controlStand) {
                cm->openCard();

                while (cm->getDealerScore() < cm->getPlayerScore()) {
                    cm->addDealerCard(cm->random());
                }

                controlStand = true;
                controlHit = true;
                
                isGameOver = true;
            }

            if (inputManager::buttonReleased(GLFW_MOUSE_BUTTON_1) && !isGameOver) {
                controlStand = false;
            }
        }

    else {
        rect->setColor(0, 150, 20, 255);
    }

    cm->check(isGameOver);
}

//

HitButton::HitButton() {
    rect = g->createRectangle(w, h);

    rect->setX(x);
    rect->setY(y);

    rect->setColor(0, 150, 20, 255);

    float tW;
    float tH;

    fonts::open_sans->getTextSize("Kart Cek", tW, tH, 0.7);

    tX = x + w/2 - tW/2;
    tY = y + h/2 + tH/2;
}

void HitButton::renderHit() {
    rect->draw();

    g->setPosition(tX, tY);
    g->renderText("Kart Cek", 0.7);
}

void HitButton::eventHit(CardManager* cm) {
    if (inputManager::mouse_input->x > x && inputManager::mouse_input->x < x + w 
        && inputManager::mouse_input->y > y && inputManager::mouse_input->y < y + h) {

            rect->setColor(0, 100, 10, 255);

            if (inputManager::buttonPressed(GLFW_MOUSE_BUTTON_1) && !controlHit) {
                cm->addPlayerCard(cm->random());

                controlHit = true;
            }

            if (inputManager::buttonReleased(GLFW_MOUSE_BUTTON_1) && cm->getPlayerScore() < 21 && !controlStand) {
                controlHit = false;
            }
        }

    else {
        rect->setColor(0, 150, 20, 255);
    }
}

//

RestartButton::RestartButton() {
    icon = g->createRectangle(w, h);

    icon->setX(x);
    icon->setY(y);

    icon->addTexture(textureManager::loadTexture("data/images/restart.png"));
    icon->setColorMode(TEXTURE);

    rect = g->createRectangle(w, h);

    rect->setX(x);
    rect->setY(y);

    rect->setColor(0, 150, 20, 255);
}

void RestartButton::renderRestart() {
    rect->draw();
    icon->draw();
}

void RestartButton::eventRestart(CardManager* cm) {
    if (inputManager::mouse_input->x > x && inputManager::mouse_input->x < x + w 
        && inputManager::mouse_input->y > y && inputManager::mouse_input->y < y + h) {

            rect->setColor(0, 100, 10, 255);

            if (inputManager::buttonPressed(GLFW_MOUSE_BUTTON_1) && !controlRestart) {
                controlRestart = true;

                cm->reset();

                controlHit = false;
                controlStand = false;

                isGameOver = false;
            }

            if (inputManager::buttonReleased(GLFW_MOUSE_BUTTON_1)) {
                controlRestart = false;
            }
        }

    else {
        rect->setColor(0, 150, 20, 255);
    }
}