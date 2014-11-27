/*
 * game_engine.h
 *
 *  Created on: Nov 26, 2014
 *      Author: frejo105
 */

#ifndef INCLUDE_GAME_ENGINE_H_
#define INCLUDE_GAME_ENGINE_H_

class GameEngine
{
	AbstractGameState* activate_state;

	IntroState is;
	PlayState ps;
	GameOverState gos;

	GameEngine()
	{
		activate_state = &is;
	}

	void run()
	{
		state->update();
		if ( ... )
		{
			activate_state = &ps;
		}
	}
};



#endif /* INCLUDE_GAME_ENGINE_H_ */
