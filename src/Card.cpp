#include "Card.hpp"

#include <iostream>

#include "stats.hpp"

int cardX = 118;
int cardY = 166;

int xOffset = 10;

Card::Card(Shape* shape, const char* cardName, int cardValue) {
    texture = shape;
    name = cardName;
    value = cardValue;
}

Shape* Card::getTexture() {
    return texture;
}

std::string Card::getName() {
    return name;
}

int Card::getValue() {
    return value;
}

//////////////////
// CardManager
//////////////////

#include "Graphics.hpp"
#include "TextureManager.hpp"
#include "Fonts.hpp"
#include "Timer.hpp"

timer::ID gameOverTimer = timer::createTimer();

using namespace graphics;

Card* createCard(const char* cardName, int cardValue) {
    Shape* texture = g->createRectangle(cardX, cardY);

    texture->setX(-200);
    texture->setY(-200);

    texture->setColorMode(TEXTURE);

    std::string root = "data/images/";
    std::string ext = ".png";

    texture->addTexture(textureManager::loadTexture((root + std::string(cardName) + ext).c_str()));

    return new Card(texture, cardName, cardValue);
}

CardManager::CardManager() {
    std::string types = "cdhs"; // club, diamond, heart, spade
    std::string extras = "jkq"; // jack, king, queen

    std::string type;
    std::string extra;

    std::string name = "";

    for (int i = 0; i < 4; i++) {
        type = types.at(i);

        for (int n = 2; n <= 10; n++) {
            name = type + std::to_string(n);

            loadedCards.insert(std::pair<std::string, Card*>(name, createCard(name.c_str(), n)));
        }

        for (int l = 0; l < 3; l++) {
            extra = extras.at(l);

            name = type + extra;

            loadedCards.insert(std::pair<std::string, Card*>(name, createCard(name.c_str(), 10)));
        }

        name = type + "a"; // ace

        loadedCards.insert(std::pair<std::string, Card*>(name, createCard(name.c_str(), 11)));
    }

    //////////////////////////////////////////

    blankCard = g->createRectangle(cardX, cardY);

    blankCard->setX(WIDTH/2 - cardX - xOffset);
    blankCard->setY(20);

    blankCard->setColorMode(TEXTURE);

    blankCard->addTexture(textureManager::loadTexture("data/images/blank.png"));

    ////////////////////////////////////////

    circDealer = g->createOval(70, 70);

    circDealer->setX(WIDTH/2 - 35);
    circDealer->setY(35 + cardY);

    circDealer->setColor(255, 255, 255, 100);

    circPlayer = g->createOval(70, 70);

    circPlayer->setX(WIDTH/2 - 35);
    circPlayer->setY(HEIGHT - 110 - cardY);

    circPlayer->setColor(255, 255, 255, 100);

    ////////////////////////////////////////

    for (int i = 0; i < 52; i++) {
        useableNums.push_back(i);
    }
}

Card* CardManager::random() {
    int index = rand() % useableNums.size();

    auto num_it = useableNums.begin() + index;

    auto it = loadedCards.begin();

    std::advance(it, useableNums.at(index));

    useableNums.erase(num_it);

    return it->second;
}

void CardManager::renderCards() {
    float w;
    float h;

    circDealer->draw();
    circPlayer->draw();

    fonts::open_sans->getTextSize(std::to_string(playerScore), w, h, 1);

    g->setColor(0, 0, 0, 255);

    g->setPosition(WIDTH/2 - w/2, h/2 + HEIGHT - 75 - cardY);
    g->renderText(std::to_string(playerScore), 1);

    //////////////

    fonts::open_sans->getTextSize(std::to_string(dealerScore), w, h, 1);

    g->setPosition(WIDTH/2 - w/2, h/2 + 70 + cardY);
    g->renderText(std::to_string(dealerScore), 1);

    if (gameOver) {
        if (timer::getTime(gameOverTimer) > 1 && !timed) {
            timed = true;
        }

        if (timed) {

            if (scoreless) {
                Scorless();
            }

            else if (playerWon) {
                PlayerWins();
            }

            else {
                DealerWins();
            }

            return;
        }
    }

    for (int i = 0; i < dealerCards.size(); i++) {
        dealerCards.at(i)->getTexture()->draw();
    }

    for (int i = 0; i < playerCards.size(); i++) {
        playerCards.at(i)->getTexture()->draw();
    }

    if (!open) {
        blankCard->draw();
    }
}

void CardManager::addPlayerCard(Card* card) {
    card->getTexture()->setX(WIDTH/2 - cardX/2 + (xOffset + cardX/2) * playerCards.size());
    card->getTexture()->setY(HEIGHT - cardY - 20);

    for (int i = 0; i < playerCards.size(); i++) {
        playerCards.at(i)->getTexture()->translateX(-(xOffset + cardX/2));
    }

    playerCards.push_back(card);

    int currentValue = card->getValue();

    if (currentValue == 11 && playerScore + currentValue > 21) {
        currentValue = 1;
    }

    playerScore += currentValue;
}

void CardManager::addDealerCard(Card* card) {
    card->getTexture()->setX(WIDTH/2 - cardX/2 + (xOffset + cardX/2) * dealerCards.size());
    card->getTexture()->setY(20);

    for (int i = 0; i < dealerCards.size(); i++) {
        dealerCards.at(i)->getTexture()->translateX(-(xOffset + cardX/2));
    }

    dealerCards.push_back(card);

    int currentValue = card->getValue();

    if (currentValue == 11 && dealerScore + currentValue > 21) {
        currentValue = 1;
    }

    if (dealerCards.size() == 1 && !open) {
        return;
    }

    dealerScore += currentValue;
}

int CardManager::getPlayerScore() {
    return playerScore;
}

int CardManager::getDealerScore() {
    return dealerScore;
}

void CardManager::openCard() {
    open = true;

    dealerScore += dealerCards.at(0)->getValue();
}

void CardManager::reset() {
    dealerCards.clear();
    playerCards.clear();

    useableNums.clear();

    for (int i = 0; i < 52; i++) {
        useableNums.push_back(i);
    }

    playerScore = 0;
    dealerScore = 0;

    open = false;
    gameOver = false;
    scoreless = false;
    timed = false;

    addPlayerCard(random());
    addPlayerCard(random());

    addDealerCard(random());
    addDealerCard(random());
}

void CardManager::PlayerWins() {
    float w;
    float h;

    fonts::open_sans->getTextSize("Kazanan", w, h, 1);
    g->setPosition(WIDTH/2 - w/2, HEIGHT - (cardY - 20)/2 + h/2);
    g->renderText("Kazanan", 1);

    fonts::open_sans->getTextSize("Kaybeden", w, h, 1);
    g->setPosition(WIDTH/2 - w/2, (cardY + 20)/2 + h/2);
    g->renderText("Kaybeden", 1);
}

void CardManager::DealerWins() {
    float w;
    float h;

    fonts::open_sans->getTextSize("Kaybeden", w, h, 1);
    g->setPosition(WIDTH/2 - w/2, HEIGHT - (cardY - 20)/2 + h/2);
    g->renderText("Kaybeden", 1);

    fonts::open_sans->getTextSize("Kazanan", w, h, 1);
    g->setPosition(WIDTH/2 - w/2, (cardY + 20)/2 + h/2);
    g->renderText("Kazanan", 1);
}

void CardManager::Scorless() {
    float w;
    float h;

    fonts::open_sans->getTextSize("Berabere", w, h, 1);
    g->setPosition(WIDTH/2 - w/2, HEIGHT - (cardY - 20)/2 + h/2);
    g->renderText("Berabere", 1);

    g->setPosition(WIDTH/2 - w/2, (cardY + 20)/2 + h/2);
    g->renderText("Berabere", 1);
}

void CardManager::check(bool control) {
    if (gameOver) {
        return;
    }

    if (playerScore > 21) {
        playerWon = false;
        gameOver = true;

        timer::updateTimer(gameOverTimer);
    }

    if (playerScore == 21) {
        playerWon = true;
        gameOver = true;

        timer::updateTimer(gameOverTimer);
    }

    if (!control) {
        return;
    }

    if (dealerScore == playerScore) {
        scoreless = true;
    }

    if (dealerScore > 21) {
        playerWon = true;
    }

    else if (playerScore > dealerScore) {
        playerWon = true;
    }

    else if (dealerScore > playerScore) {
        playerWon = false;
    }

    else if (dealerScore == 21) {
        playerWon = false;
    }

    gameOver = true;

    timer::updateTimer(gameOverTimer);
}