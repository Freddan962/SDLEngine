#include "PlayState.h"
#include "../Text.h"
#include "../Engine.h"
#include "../AssetLoader.h"
#include "../AssetContainer.h"
#include "../Centerer.h"
#include "../InputField.h"
#include "../StateManager.h"
#include "../pong/MenuState.h"

void PlayState::update()
{
	State::update();

	if (mBall->getBody()->x + mBall->getBody()->w / 2 > mEngine->getSize()->x / 2)
	{
		if (mPaddle1Active)
		{
			moveStop();
			mPaddle1Active = false;
		}
	}
	else if (mBall->getBody()->x + mBall->getBody()->w / 2 < mEngine->getSize()->x) 
	{
		if (!mPaddle1Active)
		{
			moveStop();
			mPaddle1Active = true;
		}
	}
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
	mAssets->surfaces.add("ball2", loader.loadPNG("ball2.png"));
	mAssets->surfaces.add("ball3", loader.loadPNG("ball3.png"));
	mAssets->surfaces.add("ball4", loader.loadPNG("ball4.png"));
	mAssets->surfaces.add("ball5", loader.loadPNG("ball5.png"));
	mAssets->surfaces.add("ball6", loader.loadPNG("ball6.png"));
	mAssets->surfaces.add("homeactive", loader.loadPNG("homebutton_active.png"));
	mAssets->surfaces.add("homeinactive", loader.loadPNG("homebutton_inactive.png"));
	mAssets->surfaces.add("resetactive", loader.loadPNG("resetbutton_active.png"));
	mAssets->surfaces.add("resetinactive", loader.loadPNG("resetbutton_inactive.png"));
}

void PlayState::setUp() {
	if (mPaddle1.get()) return;

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
	mPaddle2->setMovementRestriction(0, 230, 0, 627);

	// Ball
	std::shared_ptr<Ball> ball(new Ball(mAssets->surfaces.get("ball1"), mEngine->getRenderer()));
	mBall = ball;
	sprites.add("ball", ball);
	Centerer::centerHorizontal(mBall.get(), mEngine->getSize()->x);
	Centerer::centerVertical(mBall.get(), mEngine->getSize()->y);
	mBall->setMovementRestriction(116, 133, 1167, 720);
	mBall->setBodyOutline(true);
	mBall->addFrame(mAssets->surfaces.get("ball2"));
	mBall->addFrame(mAssets->surfaces.get("ball3"));
	mBall->addFrame(mAssets->surfaces.get("ball4"));
	mBall->addFrame(mAssets->surfaces.get("ball5"));
	mBall->addFrame(mAssets->surfaces.get("ball6"));
	mBall->setAnimationSpeed(10);
	mBall->enableAnimation();

	// UI
	std::shared_ptr<Button> mHomeButton(new Button(mAssets->surfaces.get("homeinactive"), mEngine->getRenderer()));
	mHomeButton->scale(0.4, 0.4);
	mHomeButton->getBody()->y = mEngine->getSize()->y * 0.015;
	mHomeButton->getBody()->x = mEngine->getSize()->x - mHomeButton->getBody()->w - (mEngine->getSize()->y * 0.015);
	mHomeButton->setSecondarySurface(mAssets->surfaces.get("homeactive"));
	mHomeButton->click = std::bind(&PlayState::homeButtonClick, this);
	mGUI.add("homebutton", mHomeButton);

	std::shared_ptr<Button> mResetButton(new Button(mAssets->surfaces.get("resetinactive"), mEngine->getRenderer()));
	mResetButton->scale(0.4, 0.4);
	mResetButton->getBody()->y = mEngine->getSize()->y * 0.015;
	mResetButton->getBody()->x = mHomeButton->getBody()->x - mResetButton->getBody()->w - (mEngine->getSize()->y * 0.015);
	mResetButton->setSecondarySurface(mAssets->surfaces.get("resetactive"));
	mResetButton->click = std::bind(&PlayState::resetButtonClick, this);
	mGUI.add("resetbutton", mResetButton);

	// Key hooks
	mKeyHooks.addHook(SDLK_UP, std::bind(&PlayState::moveUp, this), SDL_KEYDOWN);
	mKeyHooks.addHook(SDLK_DOWN, std::bind(&PlayState::moveDown, this), SDL_KEYDOWN);
	mKeyHooks.addHook(SDLK_UP, std::bind(&PlayState::moveStop, this), SDL_KEYUP);
	mKeyHooks.addHook(SDLK_DOWN, std::bind(&PlayState::moveStop, this), SDL_KEYUP);
	mKeyHooks.addHook(SDLK_SPACE, std::bind(&PlayState::startGame, this), SDL_KEYUP);
}

void PlayState::reset()
{
	//Ball
	Centerer::centerHorizontal(mBall.get(), mEngine->getSize()->x);
	Centerer::centerVertical(mBall.get(), mEngine->getSize()->y);
	mBall->setSpeed(0, 0);

	//Pud 1
	Centerer::centerVertical(mPaddle1.get(), mEngine->getSize()->y);
	mPaddle1->getBody()->x = (mEngine->getSize()->x)*0.1;
	mPaddle1->setSpeed(0, 0);

	//Pud 2 
	Centerer::centerVertical(mPaddle2.get(), mEngine->getSize()->y);
	mPaddle2->getBody()->x = (mEngine->getSize()->x)*0.9 - (mPaddle2->getBody()->w);
	mPaddle2->setSpeed(0, 0);

}

void PlayState::moveUp()
{
	if (mPaddle1Active)
		mPaddle1->setSpeed(0, -4);
	else
		mPaddle2->setSpeed(0, -4);
}

void PlayState::moveDown()
{
	if (mPaddle1Active)
		mPaddle1->setSpeed(0, 4);
	else
		mPaddle2->setSpeed(0, 4);
}

void PlayState::moveStop()
{
	if (mPaddle1Active)
		mPaddle1->setSpeed(0, 0);
	else
		mPaddle2->setSpeed(0, 0);
}

void PlayState::startGame()
{
	mBall->setSpeed(-3, -3);
}

void PlayState::homeButtonClick()
{
	if (MenuState* menuState = dynamic_cast<MenuState*>(mEngine->getStateManager()->getPrevState()))
	{
		menuState->setPlayButtonText("Resume");
		mEngine->getStateManager()->prevState();
	}
}

void PlayState::resetButtonClick()
{
	reset();
}