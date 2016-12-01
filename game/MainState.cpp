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

void MainState::staticButtonClick()
{
	if (mStaticAnimatedFrame + 1 > 3)
		mStaticAnimatedFrame = -1;

	mStaticAnimatedFrame += 1;
	mStaticAnimated->setFrameIndex(mStaticAnimatedFrame);
	std::cout << "Updated Frame Index: " << mStaticAnimatedFrame << std::endl;
}

void MainState::load()
{
	std::string assetPath = "..\\engine\\source\\assets\\";
	AssetLoader loader(mEngine->getRenderer());

	mAssets->surfaces.add("buff", loader.loadBMP(assetPath + "iconbuff.bmp"));
	mAssets->surfaces.add("door1", loader.loadPNG(assetPath + "door1.png"));
	mAssets->surfaces.add("door2", loader.loadPNG(assetPath + "door2.png"));
	mAssets->surfaces.add("door3", loader.loadPNG(assetPath +  "door3.png"));
	mAssets->surfaces.add("door4", loader.loadPNG(assetPath +  "door4.png"));
	mAssets->surfaces.add("buttonblue", loader.loadPNG(assetPath + "buttonblue.png"));
	mAssets->fonts.add("vertigo", loader.loadFont(assetPath + "vertigo.ttf", 40));

	//Collision Sprite Left
	std::shared_ptr<EntitySprite> sprite(new EntitySprite(mAssets->surfaces.get("buff"), mEngine->getRenderer()));
	sprite->getBody()->h = 50;
	sprite->getBody()->w = 50;
	sprite->setSpeed((float)100 / mEngine->getFrameRate(), 0); 

	//Collision Sprite Right
	std::shared_ptr<EntitySprite> spriteRight(new EntitySprite(mAssets->surfaces.get("buff"), mEngine->getRenderer()));
	spriteRight->getBody()->h = 50;
	spriteRight->getBody()->w = 50;
	spriteRight->getBody()->x = mEngine->getSize()->x - spriteRight->getBody()->w;
	spriteRight->setSpeed((float)100 / mEngine->getFrameRate() * -1, 0);

	box1 = sprite;
	box2 = spriteRight;

	sprites.add("sprite", sprite);
	sprites.add("spriteRight", spriteRight);

	//AnimatedSprite
	std::shared_ptr<AnimatedSprite> animated(new AnimatedSprite(mAssets->surfaces.get("door1"), mEngine->getRenderer()));
	animated->addFrame(mAssets->surfaces.get("door2"));
	animated->addFrame(mAssets->surfaces.get("door3"));
	animated->addFrame(mAssets->surfaces.get("door4"));
	animated->getBody()->h = 24;
	animated->getBody()->w = 24;
	animated->getBody()->x = 100;
	animated->getBody()->y = 200;

	sprites.add("animated", animated);

	//AnimatedSprite Text
	std::shared_ptr<Text> animatedText(new Text(mEngine->getRenderer()));
	animatedText->setFont(mAssets->fonts.get("vertigo"));
	animatedText->setText("Animated Sprite");
	animatedText->getBody()->y = 140;
	Centerer::centerHorizontal(animatedText.get(), 230);
	mGUI.add("animatedText", animatedText);

	//Static AnimatedSprite
	std::shared_ptr<AnimatedSprite> staticAnimated(new AnimatedSprite(mAssets->surfaces.get("door1"), mEngine->getRenderer()));
	staticAnimated->addFrame(mAssets->surfaces.get("door2"));
	staticAnimated->addFrame(mAssets->surfaces.get("door3"));
	staticAnimated->addFrame(mAssets->surfaces.get("door4"));
	staticAnimated->getBody()->h = 24;
	staticAnimated->getBody()->w = 24;
	staticAnimated->getBody()->x = 450;
	staticAnimated->getBody()->y = 200;
	staticAnimated->disableAnimation();
	mStaticAnimated = staticAnimated;

	sprites.add("animated", staticAnimated);

	//Static AnimatedSprite Text
	std::shared_ptr<Text> staticAnimatedText(new Text(mEngine->getRenderer()));
	staticAnimatedText->setFont(mAssets->fonts.get("vertigo"));
	staticAnimatedText->setText("Static Animated Sprite");
	staticAnimatedText->getBody()->x = 350;
	staticAnimatedText->getBody()->y = 140;
	mGUI.add("animatedText2", staticAnimatedText);


	//Static Animated Button
	std::shared_ptr<Button> staticButton(new Button(mAssets->surfaces.get("buttonblue"), mEngine->getRenderer()));
	staticButton->getBody()->y = 240;
	staticButton->getBody()->x = 415;
	staticButton->getBody()->w = staticButton->getBody()->w * 0.5;
	staticButton->getBody()->h = staticButton->getBody()->h * 0.85;
	staticButton->text.setFont(mAssets->fonts.get("vertigo"));
	staticButton->text.setText("Click me!");
	staticButton->click = std::bind(&MainState::staticButtonClick, this);
	mGUI.add("staticbutton", staticButton);

	//Input Field
	std::shared_ptr<InputField> inputField(new InputField(mAssets->surfaces.get("buttonblue"), mEngine->getRenderer()));
	Centerer::centerHorizontal(inputField.get(), mEngine->getSize()->x);
	inputField->getBody()->y = 300;
	inputField->text.setFont(mAssets->fonts.get("vertigo"));
	inputField->text.setText("Input Field");
	mGUI.add("input", inputField);

	//Long Button
	std::shared_ptr<Button> button(new Button(mAssets->surfaces.get("buttonblue"), mEngine->getRenderer()));
	Centerer::centerHorizontal(button.get(), mEngine->getSize()->x);
	button->getBody()->y = 400;
	button->text.setFont(mAssets->fonts.get("vertigo"));
	button->text.setText("A Very Long Button Name");
	mGUI.add("button", button);

	//Collision Status Text
	std::shared_ptr<Text> collisionStatus(new Text(mEngine->getRenderer()));
	collisionStatus->setFont(mAssets->fonts.get("vertigo"));
	collisionStatus->setText("Collision status: Unknown");
	collisionStatus->getBody()->y = 60;
	Centerer::centerHorizontal(collisionStatus.get(), mEngine->getSize()->x);
	collisionText = collisionStatus;
	mGUI.add("collisionText", collisionText);

	//Hooks
	mKeyHooks.addHook(SDLK_a, std::function<void()>(aClick));
	mEventHooks.addHook(SDL_MOUSEBUTTONUP, &onClick);
}

void MainState::unload()
{
	
}


