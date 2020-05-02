#pragma once

#include "Pool.h"
#include "Command.h"
#include "../common/Board.h"
#include <vector>
#include <string>

class Player {
public:
	Player(Pool *pool, std::string name);
	int getScore() const;
	std::string getName() const;
	void showHand() const;
	void showScore() const;
	void addScore();
	bool exchange(int pos1, Pool *pool);
	bool takeRandom(Pool *pool, int handPosition);
	bool mayMove(const Board *board, const Pool *pool) const;
	bool hasOnHand(char letter) const;
	int getHandPosition(char letter) const;
private:
	char getLetterOnHand(int handPosition) const;
	int _colorCode;
	std::string _colorName;
	std::string _name;
	int _score;
	bool _turn;
	std::vector<char> _hand;
};

