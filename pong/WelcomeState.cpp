#include "WelcomeState.h"
#include "../Text.h"
#include "../Engine.h"
#include "../AssetLoader.h"
#include "../AssetContainer.h"
#include "../Centerer.h"
#include "../InputField.h"
#include "../StateManager.h"

void WelcomeState::update()
{
	State::update();
}

void WelcomeState::render()
{
	State::render();
}

void WelcomeState::handleEvent(SDL_Event* event)
{
	State::handleEvent(event);
}

void WelcomeState::load()
{
	State::load();
	loadAssets();
	setUp();
}

void WelcomeState::unload()
{
	State::unload();
}

void WelcomeState::loadAssets() {
	AssetLoader loader(mEngine->getRenderer(), "..\\SDLEngine\\source\\assets\\");
	mAssets->fonts.add("vertigo", loader.loadFont("vertigo.ttf", 40));
	mAssets->surfaces.add("buttonblue", loader.loadPNG("buttonblue.png"));
	mAssets->surfaces.add("buttonblueinactive", loader.loadPNG("buttonblue_inactive.png"));
	mAssets->surfaces.add("background", loader.loadPNG("bg_purple.png"));
	mAssets->surfaces.add("logo", loader.loadPNG("logo.png"));
}

void WelcomeState::setUp() {
	std::shared_ptr<Sprite> background(new Sprite(mAssets->surfaces.get("background"), mEngine->getRenderer()));
	background->scale(5, 5);
	sprites.add("background", background);

	std::shared_ptr<Sprite> logo(new Sprite(mAssets->surfaces.get("logo"), mEngine->getRenderer()));
	logo->scale(0.60, 0.60);
	logo->getBody()->y = mEngine->getSize()->y * 0.3;
	Centerer::centerHorizontal(logo.get(), mEngine->getSize()->x);
	sprites.add("logo", logo);

	std::shared_ptr<Player> player(new Player(NULL, mEngine->getRenderer()));
	mPlayer = player;

	std::shared_ptr<Text> welcomeTxt(new Text(mEngine->getRenderer()));
	welcomeTxt->setFont(mAssets->fonts.get("vertigo"));
	welcomeTxt->setText("Enter name");
	Centerer::centerHorizontal(welcomeTxt.get(), mEngine->getSize()->x);
	Centerer::centerVertical(welcomeTxt.get(), mEngine->getSize()->y);
	welcomeTxt->getBody()->y = welcomeTxt->getBody()->y + mEngine->getSize()->y * 0.1;
	mGUI.add("welcomeTxt", welcomeTxt);

	std::shared_ptr<InputField> inputField(new InputField(mAssets->surfaces.get("buttonblueinactive"), mEngine->getRenderer()));
	Centerer::centerHorizontal(inputField.get(), mEngine->getSize()->x);
	inputField->getBody()->y = welcomeTxt->getBody()->y + welcomeTxt->getBody()->h + 20;
	inputField->text.setFont(mAssets->fonts.get("vertigo"));
	inputField->text.setText("");
	inputField->setSecondarySurface(mAssets->surfaces.get("buttonblue"));
	mGUI.add("input", inputField);
	mInputField = inputField;

	std::shared_ptr<Button> okButton(new Button(mAssets->surfaces.get("buttonblueinactive"), mEngine->getRenderer()));
	Centerer::centerHorizontal(okButton.get(), mEngine->getSize()->x);
	okButton->getBody()->y = inputField->getBody()->y + inputField->getBody()->h + 20;
	okButton->text.setFont(mAssets->fonts.get("vertigo"));
	okButton->text.setText("OK");
	okButton->click = std::bind(&WelcomeState::okButtonClick, this);
	okButton->setSecondarySurface(mAssets->surfaces.get("buttonblue"));
	mGUI.add("OKbutton", okButton);
}

void WelcomeState::okButtonClick()
{
	if (mInputField->text.isEmpty()) return;

	mPlayer->setName(mInputField->text.getText());
	mEngine->getStateManager()->getNextState()->savedSprites.add("player", mPlayer);
	mEngine->getStateManager()->nextState();
}