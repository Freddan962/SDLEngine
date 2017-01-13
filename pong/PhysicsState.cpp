#include "PhysicsState.h"
#include "../AssetLoader.h"
#include "../Engine.h"
#include "../AssetContainer.h"
#include "../StateManager.h"
#include "../Sprite.h"
#include "../Button.h"
#include "../Centerer.h"

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

}

void PhysicsState::start()
{

}

void PhysicsState::returnButtonClick()
{
	mEngine->getStateManager()->prevState();
}

void PhysicsState::resetButtonClick()
{
	reset();
}

void PhysicsState::debugModeToggle()
{
	if (Sprite::mBodyOutline)
		Sprite::setBodyOutline(false);
	else
		Sprite::setBodyOutline(true);
}