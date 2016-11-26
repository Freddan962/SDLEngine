#include "PlayState.h"
#include "../AssetContainer.h"
#include "../Engine.h"
#include "../ImageLoader.h"
#include "../Sprite.h"
#include "Player.h"
#include "../SpriteCenterer.h"
#include "Projectile.h"

PlayState::PlayState(Engine * engine)
	: State(engine, "PlayState"),
	mPlayLogic(this)
{
	load();
}


void PlayState::update()
{
	State::update();
	mPlayLogic.update();
}

void PlayState::render()
{
	State::render();
	mPlayLogic.render(mEngine->getRenderer());
}

void PlayState::handleEvent(SDL_Event * event)
{
	State::handleEvent(event);
}

void PlayState::load()
{
	loadAssets();
	prepareEntities();
	bindHooks();
}

void PlayState::unload()
{

}

void PlayState::loadAssets()
{
	ImageLoader loader(mEngine->getRenderer());
	mAssets->addTexture("bgPurple", loader.loadPNG("..\\engine\\source\\assets\\bgpurple.png"));
	mAssets->addTexture("player", loader.loadPNG("..\\engine\\source\\assets\\player.png"));
	mAssets->addTexture("laserBlue", loader.loadPNG("..\\engine\\source\\assets\\laserblue.png"));
}

void PlayState::prepareEntities()
{
	std::shared_ptr<Sprite> background(new Sprite(mAssets->getTexture("bgPurple")));
	background->getBody()->h = mEngine->getSize()->y;
	background->getBody()->w = mEngine->getSize()->x;

	std::shared_ptr<Player> player(new Player(mAssets->getTexture("player")));
	SpriteCenterer::centerHorizontal(player.get(), mEngine->getSize()->x);
	player.get()->getBody()->y = mEngine->getSize()->y - player.get()->getBody()->h - player.get()->getBody()->h * 0.1;
	Vector4<int> restriction;
	restriction.x = 0;
	restriction.y = 0;
	restriction.z = mEngine->getSize()->x;
	restriction.o = mEngine->getSize()->y;
	player.get()->setMovementRestriction(restriction);

	std::shared_ptr<Projectile> projectile(new Projectile(mAssets->getTexture("laserBlue")));
	projectile->getBody()->h *= 0.7;
	projectile->getBody()->w *= 0.7;
	player->setProjectile(projectile);

	mPlayer = player;

	addSprite("background", background);
	addSprite("player", mPlayer);
}

void PlayState::bindHooks()
{
	mKeyHooks.addHook(SDLK_a, std::bind(&Player::moveLeft, mPlayer.get()), SDL_KEYDOWN);
	mKeyHooks.addHook(SDLK_d, std::bind(&Player::moveRight, mPlayer.get()), SDL_KEYDOWN);
	mKeyHooks.addHook(SDLK_SPACE, std::bind(&PlayLogic::playerShoot, mPlayLogic), SDL_KEYDOWN);
}
