#ifndef CARD_HPP
#define CARD_HPP

#include <string>
#include <vector>
#include <map>

#include "Transform.hpp"

class Card {
    public:
        Card(Shape* shape, const char* cardName, int cardValue);

        Shape* getTexture();

        std::string getName();

        int getValue();

    private:
        Shape* texture;

        std::string name;

        int value;
};

class CardManager {
    public:
        CardManager();

        void renderCards();

        void addPlayerCard(Card* card);
        void addDealerCard(Card* card);

        Card* random();

        int getPlayerScore();
        int getDealerScore();

        void PlayerWins();
        void DealerWins();
        void Scorless();

        void openCard();

        void reset();

        void check(bool control);

    private:
        std::map<std::string, Card*> loadedCards;

        std::vector<Card*> dealerCards;
        std::vector<Card*> playerCards;

        std::vector<int> useableNums;

        Shape* blankCard;

        bool open = false;

        bool gameOver = false;

        bool playerWon = false;
        bool scoreless = false;

        bool timed = false;

        int playerScore = 0;
        int dealerScore = 0;

        Shape* circPlayer;
        Shape* circDealer;
};

#endif