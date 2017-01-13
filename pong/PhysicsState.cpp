#include "PhysicsState.h"
#include "../AssetLoader.h"
#include "../Engine.h"
#include "../AssetContainer.h"
#include "../StateManager.h"
#include "../Sprite.h"
#include "../Button.h"
#include "../Centerer.h"
#include "Ball.h"

#include <ctime>

PhysicsState::PhysicsState(Engine* engine)
	: State(engine, "PhysicsState")
{
}

void PhysicsState::update()
{
	State::update();
}

void PhysicsState::render()
{
	State::render();
}

void PhysicsState::handleEvent(SDL_Event* event)
{
	State::handleEvent(event);
}

void PhysicsState::load()
{
	State::load();
	loadAssets();
	setUp();
}

void PhysicsState::unload()
{
	State::unload();
}

void PhysicsState::loadAssets() {
	AssetLoader loader(mEngine->getRenderer(), "..\\SDLEngine\\source\\assets\\");
	mAssets->fonts.add("vertigo", loader.loadFont("vertigo.ttf", 40));
	mAssets->fonts.add("vertigoscore", loader.loadFont("vertigo.ttf", 60));
	mAssets->surfaces.add("background", loader.loadPNG("court_05.png"));
	mAssets->surfaces.add("homeactive", loader.loadPNG("homebutton_active.png"));
	mAssets->surfaces.add("homeinactive", loader.loadPNG("homebutton_inactive.png"));
	mAssets->surfaces.add("resetactive", loader.loadPNG("resetbutton_active.png"));
	mAssets->surfaces.add("resetinactive", loader.loadPNG("resetbutton_inactive.png"));
	mAssets->surfaces.add("ballwhite", loader.loadPNG("ball_white.png"));
	mAssets->surfaces.add("spawnactive", loader.loadPNG("spawnactive.png"));
	mAssets->surfaces.add("spawninactive", loader.loadPNG("spawninactive.png"));
}

void PhysicsState::setUp() {
	std::shared_ptr<Button> mReturnButton(Button::getInstance(mAssets->surfaces.get("homeinactive"), mEngine->getRenderer()));
	mReturnButton->scale(0.4, 0.4);
	mReturnButton->getBody()->y = mEngine->getSize()->y * 0.015;
	mReturnButton->getBody()->x = mEngine->getSize()->x - mReturnButton->getBody()->w - (mEngine->getSize()->y * 0.015);
	mReturnButton->setSecondarySurface(mAssets->surfaces.get("homeactive"));
	mReturnButton->click = std::bind(&PhysicsState::returnButtonClick, this);
	mGUI.add("returnbutton", mReturnButton);

	std::shared_ptr<Button> mResetButton(Button::getInstance(mAssets->surfaces.get("resetinactive"), mEngine->getRenderer()));
	mResetButton->scale(0.4, 0.4);
	mResetButton->getBody()->y = mEngine->getSize()->y * 0.015;
	mResetButton->getBody()->x = mReturnButton->getBody()->x - mResetButton->getBody()->w - (mEngine->getSize()->y * 0.015);
	mResetButton->setSecondarySurface(mAssets->surfaces.get("resetactive"));
	mResetButton->click = std::bind(&PhysicsState::resetButtonClick, this);
	mGUI.add("resetbutton", mResetButton);

	std::shared_ptr<Button> mPhysicsButton(Button::getInstance(mAssets->surfaces.get("spawninactive"), mEngine->getRenderer()));
	mPhysicsButton->scale(0.4, 0.4);
	mPhysicsButton->getBody()->y = mEngine->getSize()->y * 0.015;
	mPhysicsButton->getBody()->x = mEngine->getSize()->y * 0.015;
	mPhysicsButton->setSecondarySurface(mAssets->surfaces.get("spawnactive"));
	mPhysicsButton->click = std::bind(&PhysicsState::spawnButtonClick, this);
	mGUI.add("physicsbutton", mPhysicsButton);

	std::shared_ptr<Text> scoreTxt(Text::getInstance(mEngine->getRenderer()));
	scoreTxt->setFont(mAssets->fonts.get("vertigoscore"));
	scoreTxt->setText("Physics Simulation");
	Centerer::centerHorizontal(scoreTxt.get(), mEngine->getSize()->x);
	scoreTxt->getBody()->y = mEngine->getSize()->y * 0.015;
	mGUI.add("scoreTxt", scoreTxt);

	mKeyHooks.addHook(SDLK_t, std::bind(&PhysicsState::debugModeToggle, this), SDL_KEYUP);
}

void PhysicsState::reset()
{
	sprites.get("ball")->clear();
}

void PhysicsState::returnButtonClick()
{
	mEngine->getStateManager()->prevState();
}

void PhysicsState::resetButtonClick()
{
	reset();
}

void PhysicsState::spawnButtonClick()
{
	std::shared_ptr<Ball> ball(new Ball(mAssets->surfaces.get("ballwhite"), mEngine->getRenderer()));

	ball->getBody()->x = rand() % mEngine->getSize()->x;
	ball->getBody()->y = rand() % mEngine->getSize()->y * 0.65 + (mEngine->getSize()->y * 0.11);

	ball->setMovementRestriction(116, -500, 1167, 720);
	ball->setAnimationSpeed(10);
	ball->enableAnimation();
	ball->setAffectedByGravity(true);

	sprites.add("ball", ball);
}

void PhysicsState::debugModeToggle()
{
	if (Sprite::mBodyOutline)
		Sprite::setBodyOutline(false);
	else
		Sprite::setBodyOutline(true);
}

