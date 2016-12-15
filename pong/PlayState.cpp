#include "PlayState.h"
#include "../Text.h"
#include "../Engine.h"
#include "../AssetLoader.h"
#include "../AssetContainer.h"
#include "../Centerer.h"
#include "../InputField.h"
#include "../StateManager.h"

void PlayState::update()
{
	State::update();
}

void PlayState::render()
{
	State::render();
}

void PlayState::handleEvent(SDL_Event* event)
{
	State::handleEvent(event);
}

void PlayState::load()
{
	State::load();
	loadAssets();
	setUp();
}

void PlayState::unload()
{
	State::unload();
}

void PlayState::loadAssets() {
	AssetLoader loader(mEngine->getRenderer(), "..\\SDLEngine\\source\\assets\\");
	mAssets->fonts.add("vertigo", loader.loadFont("vertigo.ttf", 40));
	mAssets->surfaces.add("paddle1", loader.loadPNG("pud_left1.png"));
	mAssets->surfaces.add("paddle2", loader.loadPNG("pud_right1.png"));
	mAssets->surfaces.add("background", loader.loadPNG("court_05.png"));
	mAssets->surfaces.add("ball1", loader.loadPNG("ball1.png"));
	
}

void PlayState::setUp() {
	std::shared_ptr<Sprite> background(new Sprite(mAssets->surfaces.get("background"), mEngine->getRenderer()));
	sprites.add("background", background);
	
	// Left pud
	std::shared_ptr<Paddle> paddle1(new Paddle(mAssets->surfaces.get("paddle1"), mEngine->getRenderer()));
	mPaddle1 = paddle1;
	mPaddle1->id = 1;
	sprites.add("paddle1", mPaddle1);
	mPaddle1->scale(0.40, 0.60);
	Centerer::centerVertical(mPaddle1.get(), mEngine->getSize()->y);
	mPaddle1->getBody()->x = (mEngine->getSize()->x)*0.1;
	mPaddle1->setMovementRestriction(0, 230, 0, 627);
	mPaddle1->setBodyOutline(true);

	// Right pud
	std::shared_ptr<Paddle> paddle2(new Paddle(mAssets->surfaces.get("paddle2"), mEngine->getRenderer()));
	mPaddle2 = paddle2;
	mPaddle2->id = 2;
	sprites.add("paddle2", mPaddle2);
	mPaddle2->scale(0.40, 0.60);
	Centerer::centerVertical(mPaddle2.get(), mEngine->getSize()->y);
	mPaddle2->getBody()->x = (mEngine->getSize()->x)*0.9 - (mPaddle2->getBody()->w);

	// Ball
	std::shared_ptr<Ball> ball(new Ball(mAssets->surfaces.get("ball1"), mEngine->getRenderer()));
	mBall = ball;
	sprites.add("ball", ball);
	Centerer::centerHorizontal(mBall.get(), mEngine->getSize()->x);
	Centerer::centerVertical(mBall.get(), mEngine->getSize()->y);
	mBall->setMovementRestriction(110, 133, 1187, 720);
	mBall->setBodyOutline(true);

	// Key hooks
	mKeyHooks.addHook(SDLK_UP, std::bind(&PlayState::moveUp, this), SDL_KEYDOWN);
	mKeyHooks.addHook(SDLK_DOWN, std::bind(&PlayState::moveDown, this), SDL_KEYDOWN);
	mKeyHooks.addHook(SDLK_UP, std::bind(&PlayState::moveStop, this), SDL_KEYUP);
	mKeyHooks.addHook(SDLK_DOWN, std::bind(&PlayState::moveStop, this), SDL_KEYUP);
	mKeyHooks.addHook(SDLK_SPACE, std::bind(&PlayState::startGame, this), SDL_KEYUP);
}

void PlayState::moveUp()
{
	mPaddle1->setSpeed(0, -4);
}

void PlayState::moveDown()
{
	mPaddle1->setSpeed(0, 4);
}

void PlayState::moveStop()
{
	mPaddle1->setSpeed(0, 0);
}

void PlayState::startGame()
{
	mBall->setSpeed(-3, -3);
}