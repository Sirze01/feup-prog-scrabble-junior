#include "Player.h"
#include "Move.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include "../common/ConsoleSetup.h"

Player::Player(Pool &pool, const std::string &name, int color, bool isBot):
    _name{ name }, _hasPassed{ false }, _score{ 0 }, _color{ color }, _exchangeCount{ 0 }, _isBot{ isBot }
{
    pool.shuffle();
    int handSize = 7;
    _hand.resize(handSize);
    while (handSize--) takeRandom(handSize,pool);
}

int Player::getScore() const {
    return _score;
}

std::string Player::getName() const {
    return _name;
}

void Player::showHand(std::ostream &output, bool color) const {
    if (!getHandSize()) {
        output << "Nothing on hand\n";
        return;
    }
    for (const auto &i : _hand) {
        if (color) outputBackColor(output, _color, i);
        else output << i;
        output << SPACE;
    }
    output << "\n";
}

void Player::addScore() {
    _score++;
}

bool Player::exchange(char letter, Pool& pool) {
    //if pool is empty, abort exchange operation
    if (!pool.getCurrentSize()) return false;

    int handPos = getHandPosition(letter);
    if (!takeRandom(handPos, pool)) return false;

    pool.include(letter);
    _exchangeCount++;
    return true;
}

bool Player::takeRandom(int handPos, Pool &pool) {
    int poolSize = pool.getCurrentSize();

    if (!poolSize) { //if pool is empty, remove from hand (endgame)
        _hand.erase(_hand.begin() + handPos);
        return false;
    }

    int randomPoolPos = randomBetween(0, poolSize - 1);
    _hand.at(handPos) = pool.getAllLetters().at(randomPoolPos);
    pool.take(randomPoolPos);
    return true;
}

void Player::resetExchangeCount() {
    _exchangeCount = 0;
}

int Player::getHandPosition(char letter) const {
    for (size_t i = 0; i < _hand.size(); ++i) {
        if (_hand.at(i) == letter) return i;
    }
    return -1;
}

bool Player::hasOnHand(char letter) const {
    for (const auto &i : _hand) {
        if (i == letter) return true;
    }
    return false;
}

bool Player::mayMove(const Board &board) const{
    coord pos = getPossibleMovePos(board);
    return pos.hColumn != IMPOSSIBLE_MOVE_COORD && pos.vLine != IMPOSSIBLE_MOVE_COORD;
}

coord Player::getPossibleMovePos(const Board& board) const {
    coord boardDim = board.getDimensions();
    std::vector<std::vector<char>> boardLetters = board.getLetters();

    for (size_t line = 0; line < boardDim.vLine; ++line) {
        for (size_t col = 0; col < boardDim.hColumn; ++col) {
            coord testPosition = { line,col };
            char letter = boardLetters.at(line).at(col);
            const Move moveToTest(testPosition, letter, board);

            if (!moveToTest.hasProblems(*this)) return testPosition;
        }
    }
    return { IMPOSSIBLE_MOVE_COORD,IMPOSSIBLE_MOVE_COORD };
}

int Player::getColor() const {
    return _color;
}

int Player::getExchangeCount() const {
    return _exchangeCount;
}

bool Player::getHasPassed() const {
    return _hasPassed;
}

void Player::forcePass() {
    _hasPassed = true;
}

void Player::doNotPass() {
    _hasPassed = false;
}

int Player::getHandSize() const {
    return _hand.size();
}

bool Player::isBot() const {
    return _isBot;
}

std::vector<char> Player::getHand() const {
    return _hand;
}