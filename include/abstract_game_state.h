/*
 * abstract_game_state.h
 *
 *  Created on: Dec 5, 2014
 *      Author: vakz
 */

#ifndef ABSTRACT_GAME_STATE_H_
#define ABSTRACT_GAME_STATE_H_

#include <vector>
#include "gameinput.h"

class AbstractGameState
{
	virtual void update(std::vector<GameInput> const&) = 0;
};


#endif /* ABSTRACT_GAME_STATE_H_ */
