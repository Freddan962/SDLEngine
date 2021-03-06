#include "PlayState.h"
#include "../Text.h"
#include "../Engine.h"
#include "../AssetLoader.h"
#include "../AssetContainer.h"
#include "../Centerer.h"
#include "../InputField.h"
#include "../StateManager.h"
#include "../pong/MenuState.h"
#include "../pong/PowerupSpeed.h"
#include "../Physics.h"
#include <vector>
#include <ctime>

PlayState::PlayState(Engine* engine)
	: State(engine, "PlayState"),
	player1Score(0), player2Score(0), bouncesForBallSpawn(3) 
{
	mPowerupSpawnTimer.setTime(10000);
	mPowerupSpawnTimer.start();
	srand(time(NULL));
}

void PlayState::update()
{
	State::update();
	removeTemporaryBalls();
	removeTemporaryPowerups();
	updateScore();
	spawnBall();
	spawnPowerup();
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
	mAssets->fonts.add("vertigoscore", loader.loadFont("vertigo.ttf", 60));
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
	mAssets->surfaces.add("gemblue", loader.loadPNG("gemBlue.png"));
	mAssets->surfaces.add("gemred", loader.loadPNG("gemRed.png"));
	mAssets->surfaces.add("physicsbuttonactive", loader.loadPNG("physicsbutton_active.png"));
	mAssets->surfaces.add("physicsbuttoninactive", loader.loadPNG("physicsbutton_inactive.png"));
}

void PlayState::setUp() {
	if (mPaddle1.get()) return;

	std::shared_ptr<Sprite> background(Sprite::getInstance(mAssets->surfaces.get("background"), mEngine->getRenderer()));
	sprites.add("background", background);
	
	// Left pud
	std::shared_ptr<Paddle> paddle1(new Paddle(mAssets->surfaces.get("paddle1"), mEngine->getRenderer()));
	mPaddle1 = paddle1;
	mPaddle1->id = 1;
	sprites.add("paddle1", mPaddle1);
	mPaddle1->scale(0.40, 0.60);
	Centerer::centerVertical(mPaddle1.get(), mEngine->getSize()->y);
	mPaddle1->getBody()->x = (mEngine->getSize()->x)*0.1;
	mPaddle1->setMovementRestriction(0, 146, 0, 709);
	mPaddle1->setCollidable(true);

	// Right pud
	std::shared_ptr<Paddle> paddle2(new Paddle(mAssets->surfaces.get("paddle2"), mEngine->getRenderer()));
	mPaddle2 = paddle2;
	mPaddle2->id = 2;
	sprites.add("paddle2", mPaddle2);
	mPaddle2->scale(0.40, 0.60);
	Centerer::centerVertical(mPaddle2.get(), mEngine->getSize()->y);
	mPaddle2->getBody()->x = (mEngine->getSize()->x)*0.9 - (mPaddle2->getBody()->w);
	mPaddle2->setMovementRestriction(0, 146, 0, 709);
	mPaddle2->setCollidable(true);

	// Ball
	mBall = createBall();
	sprites.add("ballmain", mBall);
	mBall->setCollidable(true);

	//Powerup Speed
	mPowerupSpawnTimer.forceReady();
	spawnPowerup();

	// UI
	std::shared_ptr<Button> mHomeButton(Button::getInstance(mAssets->surfaces.get("homeinactive"), mEngine->getRenderer()));
	mHomeButton->scale(0.4, 0.4);
	mHomeButton->getBody()->y = mEngine->getSize()->y * 0.015;
	mHomeButton->getBody()->x = mEngine->getSize()->x - mHomeButton->getBody()->w - (mEngine->getSize()->y * 0.015);
	mHomeButton->setSecondarySurface(mAssets->surfaces.get("homeactive"));
	mHomeButton->click = std::bind(&PlayState::homeButtonClick, this);
	mGUI.add("homebutton", mHomeButton);

	std::shared_ptr<Button> mResetButton(Button::getInstance(mAssets->surfaces.get("resetinactive"), mEngine->getRenderer()));
	mResetButton->scale(0.4, 0.4);
	mResetButton->getBody()->y = mEngine->getSize()->y * 0.015;
	mResetButton->getBody()->x = mHomeButton->getBody()->x - mResetButton->getBody()->w - (mEngine->getSize()->y * 0.015);
	mResetButton->setSecondarySurface(mAssets->surfaces.get("resetactive"));
	mResetButton->click = std::bind(&PlayState::resetButtonClick, this);
	mGUI.add("resetbutton", mResetButton);

	std::shared_ptr<Text> scoreTxt(Text::getInstance(mEngine->getRenderer()));
	scoreTxt->setFont(mAssets->fonts.get("vertigoscore"));
	scoreTxt->setText("0 - 0");
	Centerer::centerHorizontal(scoreTxt.get(), mEngine->getSize()->x);
	scoreTxt->getBody()->y = mEngine->getSize()->y * 0.015;
	mGUI.add("scoreTxt", scoreTxt);
	mScoreTxt = scoreTxt;

	std::shared_ptr<Button> mPhysicsButton(Button::getInstance(mAssets->surfaces.get("physicsbuttoninactive"), mEngine->getRenderer()));
	mPhysicsButton->scale(0.4, 0.4);
	mPhysicsButton->getBody()->y = mEngine->getSize()->y * 0.015;
	mPhysicsButton->getBody()->x = mEngine->getSize()->y * 0.015;
	mPhysicsButton->setSecondarySurface(mAssets->surfaces.get("physicsbuttonactive"));
	mPhysicsButton->click = std::bind(&PlayState::physicsButtonClick, this);
	mGUI.add("physicsbutton", mPhysicsButton);

	// Key hooks
	mKeyHooks.addHook(SDLK_w, std::bind(&PlayState::moveUpLeft, this), SDL_KEYDOWN);
	mKeyHooks.addHook(SDLK_s, std::bind(&PlayState::moveDownLeft, this), SDL_KEYDOWN);
	mKeyHooks.addHook(SDLK_w, std::bind(&PlayState::moveStopLeft, this), SDL_KEYUP);
	mKeyHooks.addHook(SDLK_s, std::bind(&PlayState::moveStopLeft, this), SDL_KEYUP);

	mKeyHooks.addHook(SDLK_UP, std::bind(&PlayState::moveUpRight, this), SDL_KEYDOWN);
	mKeyHooks.addHook(SDLK_DOWN, std::bind(&PlayState::moveDownRight, this), SDL_KEYDOWN);
	mKeyHooks.addHook(SDLK_UP, std::bind(&PlayState::moveStopRight, this), SDL_KEYUP);
	mKeyHooks.addHook(SDLK_DOWN, std::bind(&PlayState::moveStopRight, this), SDL_KEYUP);

	mKeyHooks.addHook(SDLK_SPACE, std::bind(&PlayState::startGame, this), SDL_KEYUP);
	mKeyHooks.addHook(SDLK_t, std::bind(&PlayState::debugModeToggle, this), SDL_KEYUP);

	updateScoreText();
}

void PlayState::reset()
{
	Centerer::centerHorizontal(mBall.get(), mEngine->getSize()->x);
	Centerer::centerVertical(mBall.get(), mEngine->getSize()->y);
	mBall->reachedLeft = false;
	mBall->reachedRight = false;
}

void PlayState::moveUpLeft() { mPaddle1->setVelocity(0, -7); }
void PlayState::moveDownLeft() { mPaddle1->setVelocity(0, 7); }
void PlayState::moveStopLeft() { mPaddle1->setVelocity(0, 0); }
void PlayState::moveUpRight() { mPaddle2->setVelocity(0, -7); }
void PlayState::moveDownRight() { mPaddle2->setVelocity(0, 7); }
void PlayState::moveStopRight() { mPaddle2->setVelocity(0, 0); }

void PlayState::startGame()
{

	for (auto ball : mBalls)
		ball->launch();

	mBall->launch();
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
	//Pud 1
	Centerer::centerVertical(mPaddle1.get(), mEngine->getSize()->y);
	mPaddle1->getBody()->x = (mEngine->getSize()->x)*0.1;
	mPaddle1->setVelocity(0, 0);

	//Pud 2 
	Centerer::centerVertical(mPaddle2.get(), mEngine->getSize()->y);
	mPaddle2->getBody()->x = (mEngine->getSize()->x)*0.9 - (mPaddle2->getBody()->w);
	mPaddle2->setVelocity(0, 0);

	mBall->setVelocity(0, 0);
	
	for (auto ball : mBalls)
		ball->shouldDelete = true;

	removeTemporaryBalls();
	sprites.get("powerup")->clear(); 

	mPowerupSpawnTimer.reset();

	player1Score = 0;
	player2Score = 0;
	updateScoreText();
	reset();
}

void PlayState::updateScoreText()
{
	mScoreTxt->setText(std::to_string(player1Score) + " - " + std::to_string(player2Score));
}

void PlayState::score(int player, std::shared_ptr<Ball> ball)
{
	if (player == 1)
		player1Score += ball->getScoreWorth();
	else
		player2Score += ball->getScoreWorth();

	updateScoreText();

	if (mBall == ball)
		reset();
	else
		ball->shouldDelete = true;

	ball->launch();
}

std::shared_ptr<Ball> PlayState::createBall()
{
	std::shared_ptr<Ball> ball(new Ball(mAssets->surfaces.get("ball1"), mEngine->getRenderer()));
	Centerer::centerHorizontal(ball.get(), mEngine->getSize()->x);
	Centerer::centerVertical(ball.get(), mEngine->getSize()->y);
	ball->setMovementRestriction(116, 133, 1167, 720);
	ball->addFrame(mAssets->surfaces.get("ball2"));
	ball->addFrame(mAssets->surfaces.get("ball3"));
	ball->addFrame(mAssets->surfaces.get("ball4"));
	ball->addFrame(mAssets->surfaces.get("ball5"));
	ball->addFrame(mAssets->surfaces.get("ball6"));
	ball->setAnimationSpeed(10);
	ball->enableAnimation();
	ball->setCollidable(true);

	return ball;
}

std::shared_ptr<Powerup> PlayState::createPowerupTemporary()
{
	int randomNr = rand() % 2 + 1;
	Powerup* powerUp = nullptr;

	if (randomNr == 1)
		powerUp = PowerupSpeed::getInstance(mAssets->surfaces.get("gemblue"), mEngine->getRenderer());
	else
		powerUp = PowerupWorth::getInstance(mAssets->surfaces.get("gemred"), mEngine->getRenderer());

	std::shared_ptr<Powerup> powerUpPtr(powerUp);
	Centerer::centerHorizontal(powerUpPtr.get(), mEngine->getSize()->x);
	powerUpPtr->getBody()->x = powerUpPtr->getBody()->x * 1.25;
	Centerer::centerVertical(powerUpPtr.get(), mEngine->getSize()->y);
	sprites.add("powerup", powerUpPtr);

	return powerUpPtr;
}

void PlayState::createBallTemporary()
{
	std::shared_ptr<Ball> ball = createBall();
	sprites.add("ball", ball);
	mBalls.push_back(ball);
	ball->launch();
}

void PlayState::removeTemporaryBalls()
{
	for (std::vector<std::shared_ptr<Ball>>::iterator it = mBalls.begin(); it != mBalls.end(); )
	{
		std::shared_ptr<Ball> ball = *it;
		if (ball->shouldDelete)
		{
			removeTemporaryPowerups(ball);
			sprites.remove("ball", ball);
			it = mBalls.erase(it);
		}
		else
			it++;
	}
}

void PlayState::removeTemporaryPowerups(std::shared_ptr<Ball> ball)
{
	std::vector<std::shared_ptr<Sprite>>* powerups = sprites.get("powerup");
	std::vector<std::shared_ptr<Sprite>>::iterator it = powerups->begin();

	for ( it; it != powerups->end(); )
	{
		std::shared_ptr<Powerup> powerup = std::dynamic_pointer_cast<Powerup>(*it);
		if (powerup)
		{
			if (powerup->getTarget() && powerup->getTarget() == ball.get())
			{
				it = powerups->erase(it);
			}
			else
			{
				it++;
			}
		}
	}
}

void PlayState::updateScore()
{
	for (auto ball : mBalls)
	{
		if (ball->reachedLeft)
			score(2, ball);
		else if (ball->reachedRight)
			score(1, ball);
	}

	if (mBall->reachedLeft)
		score(2, mBall);
	else if (mBall->reachedRight)
		score(1, mBall);
}

void PlayState::spawnBall()
{
	if (mBall->getBounces() == bouncesForBallSpawn)
	{
		createBallTemporary();
		mBall->setBounces(0);
	}
}

void PlayState::debugModeToggle()
{
	if (Sprite::mBodyOutline)
		Sprite::setBodyOutline(false);
	else
		Sprite::setBodyOutline(true);
}

void PlayState::spawnPowerup()
{
	if (mPowerupSpawnTimer.isReady() && mBall->isMoving())
	{
		auto powerup = createPowerupTemporary();
		powerup->setCollidable(true);
		powerup->getBody()->x = rand() % (1051 - powerup->getBody()->w) + 116;
		powerup->getBody()->y = rand() % (587 - powerup->getBody()->h) + 133;
		mPowerupSpawnTimer.reset();
	}
}

void PlayState::removeTemporaryPowerups()
{
	std::vector<std::shared_ptr<Sprite>>* collection = sprites.get("powerup");
	std::vector<std::shared_ptr<Sprite>>::iterator it = collection->begin();

	for ( ; it != collection->end(); )
	{
		std::shared_ptr<Sprite> sprite = *it;
		std::shared_ptr<Powerup> powerup = std::dynamic_pointer_cast<Powerup>(sprite);

		if (powerup && powerup->isOver())
			it = collection->erase(it);
		else
			it++;
	}
}

void PlayState::physicsButtonClick()
{
	mEngine->getStateManager()->nextState();
}
