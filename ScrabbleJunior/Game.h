#pragma once

#include "../common/Board.h"
#include "../common/consoleUtil.h"
#include "../common/containerUtil.h"
#include "Player.h"
#include "Pool.h"
#include "Command.h"
#include "Move.h"
#include <vector>
#include <string>

class Game{
public:
	Game(Board& board, const std::vector<std::string>& playerNames,
		const std::vector<int>& playerColors, const std::vector<bool>& botFlags, size_t firstToMove);
	void moveHandler(int turnNumber);
	void nextTurn();
	bool hasFinished() const;
	void showEndMessage() const;
private:
	void showBoardAndCardView(bool hands = true, bool turnInfo = true) const;
	void showPlayerInfo(bool hands = true, bool turnInfo = true) const;
	bool hasWinner() const;
	int getWinner() const;
    bool allHighlighted() const;
    void showHelp() const;
    void showPool() const;

	Board& _board;
	Pool _pool;
    size_t _nPlayers;
	std::vector<int> _playerColors;
	size_t _currentPlayerPos;
	std::vector<Player> _players;
	Player* _currentPlayer;
    bool _compactCardView;
};
