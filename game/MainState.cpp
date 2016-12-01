#include "MainState.h"
#include "../Engine.h"
#include "../AssetLoader.h"
#include "../AssetContainer.h"
#include "../EntitySprite.h"
#include "../Physics.h"
#include "../AnimatedSprite.h"
#include "../Button.h"
#include "../Centerer.h"

void MainState::update() 
{
	State::update();

	if (Physics::isRectangularCollision(box1->getBody().get(), box2->getBody().get()))
	{
		collisionText.get()->setColor(0, 255, 0);
		collisionText.get()->setText("Collision status: Colliding");
	} else
	{
		collisionText.get()->setColor(255, 0, 0);
		collisionText.get()->setText("Collision status: None");
	}

	if (box1->getBody()->x + box1->getSpeed().x < 0 || box1->getBody()->x + box1->getBody()->w + box1->getSpeed().x > mEngine->getSize()->x)
		box1->setSpeed(box1->getSpeed().x * -1, 0);

	if (box2->getBody()->x + box2->getSpeed().x < 0 || box2->getBody()->x + box2->getBody()->w + box2->getSpeed().x > mEngine->getSize()->x)
		box2->setSpeed(box2->getSpeed().x * -1, 0);
}

void MainState::render()
{
	State::render();
}

void MainState::handleEvent(SDL_Event* event)
{
	State::handleEvent(event);
}

void onClick()
{
	std::cout << "CLICKED" << std::endl;
}

void aClick()
{
	std::cout << "A CLICK" << std::endl;
}

void buttonClick()
{
	std::cout << "A BUTTON CLICK" << std::endl;
}

void MainState::load()
{
	std::string assetPath = "..\\engine\\source\\assets\\";
	AssetLoader loader(mEngine->getRenderer());

	mAssets->textures.add("buff", loader.loadBMP(assetPath + "iconbuff.bmp"));
	mAssets->textures.add("door1", loader.loadPNG(assetPath + "door1.png"));
	mAssets->textures.add("door2", loader.loadPNG(assetPath + "door2.png"));
	mAssets->textures.add("door3", loader.loadPNG(assetPath +  "door3.png"));
	mAssets->textures.add("door4", loader.loadPNG(assetPath +  "door4.png"));
	mAssets->textures.add("buttonblue", loader.loadPNG(assetPath + "buttonblue.png"));
	mAssets->fonts.add("vertigo", loader.loadFont(assetPath + "vertigo.ttf", 40));

	std::shared_ptr<EntitySprite> sprite(new EntitySprite(mAssets->textures.get("buff")));
	sprite->getBody()->h = 50;
	sprite->getBody()->w = 50;
	sprite->setSpeed((float)100 / mEngine->getFrameRate(), 0); 

	std::shared_ptr<EntitySprite> spriteRight(new EntitySprite(mAssets->textures.get("buff")));
	spriteRight->getBody()->h = 50;
	spriteRight->getBody()->w = 50;
	spriteRight->getBody()->x = mEngine->getSize()->x - spriteRight->getBody()->w;
	spriteRight->setSpeed((float)100 / mEngine->getFrameRate() * -1, 0);

	box1 = sprite;
	box2 = spriteRight;

	sprites.add("sprite", sprite);
	sprites.add("spriteRight", spriteRight);

	//AnimatedSprite
	std::shared_ptr<AnimatedSprite> animated(new AnimatedSprite(mAssets->textures.get("door1")));
	animated->addFrame(mAssets->textures.get("door2"));
	animated->addFrame(mAssets->textures.get("door3"));
	animated->addFrame(mAssets->textures.get("door4"));
	animated->getBody()->h = 24;
	animated->getBody()->w = 24;
	animated->getBody()->x = 300;
	animated->getBody()->y = 250;

	sprites.add("animated", animated);

	std::shared_ptr<InputField> inputField(new InputField(mAssets->textures.get("buttonblue"), mEngine->getRenderer()));
	Centerer::centerHorizontal(inputField.get(), mEngine->getSize()->x);
	inputField->getBody()->y = 300;
	inputField->text.setFont(mAssets->fonts.get("vertigo"));
	inputField->text.setText("Input Field");
	mGUI.add("input", inputField);

	std::shared_ptr<Button> button(new Button(mAssets->textures.get("buttonblue"), mEngine->getRenderer()));
	Centerer::centerHorizontal(button.get(), mEngine->getSize()->x);
	button->getBody()->y = 400;
	button->text.setFont(mAssets->fonts.get("vertigo"));
	button->text.setText("A Very Long Button Name");
	mGUI.add("button", button);

	std::shared_ptr<Button> buttonDoor(new Button(mAssets->textures.get("door1"), mEngine->getRenderer()));
	buttonDoor->getBody()->h = 20;
	buttonDoor->getBody()->w = 20;
	buttonDoor->getBody()->x = 500;
	buttonDoor->getBody()->y = 400;
	buttonDoor->click = &buttonClick;
	mGUI.add("play", buttonDoor);

	std::shared_ptr<Text> collisionStatus(new Text(mEngine->getRenderer()));
	collisionStatus->setFont(mAssets->fonts.get("vertigo"));
	collisionStatus->setText("Collision status: Unknown");
	collisionStatus->getBody()->y = 60;
	Centerer::centerHorizontal(collisionStatus.get(), mEngine->getSize()->x);
	collisionText = collisionStatus;
	mGUI.add("collisionText", collisionText);

	mKeyHooks.addHook(SDLK_a, std::function<void()>(aClick));
	mEventHooks.addHook(SDL_MOUSEBUTTONUP, &onClick);
}

void MainState::unload()
{
	
}


