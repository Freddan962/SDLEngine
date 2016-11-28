#include "PlayState.h"
#include "../AssetContainer.h"
#include "../Engine.h"
#include "../ImageLoader.h"
#include "../Sprite.h"
#include "Player.h"
#include "../SpriteCenterer.h"
#include "Projectile.h"
#include "../SoundLoader.h"
#include "../Sound.h"

PlayState::PlayState(Engine * engine)
	: State(engine, "PlayState"),
	mPlayLogic(this)
{
	
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
	State::load();
	loadAssets();
	prepareEntities();
	bindHooks();
}

void PlayState::unload()
{
	State::unload();
}

void PlayState::loadAssets()
{
	std::string assetPath = "..\\engine\\source\\assets\\";

	ImageLoader loader(mEngine->getRenderer());
	mAssets->addTexture("bgPurple", loader.loadPNG(assetPath + "bgpurple.png"));
	mAssets->addTexture("player", loader.loadPNG(assetPath + "player.png"));
	mAssets->addTexture("laserBlue", loader.loadPNG(assetPath + "laserblue.png"));

	SoundLoader soundLoader;
	mAssets->addChunk("laser", soundLoader.loadOGG(assetPath + "laser.ogg"));
}

void PlayState::prepareEntities()
{
	std::shared_ptr<Sprite> background(new Sprite(mAssets->getTexture("bgPurple")));
	background->getBody()->h = mEngine->getSize()->y;
	background->getBody()->w = mEngine->getSize()->x;

	std::shared_ptr<Player> player(new Player(mAssets->getTexture("player")));
	SpriteCenterer::centerHorizontal(player.get(), mEngine->getSize()->x);
	player.get()->getBody()->y = mEngine->getSize()->y - player.get()->getBody()->h - player.get()->getBody()->h * 0.1;
	
	std::shared_ptr<Vector4<int>> restriction (new Vector4<int>);
	restriction->x = 0;
	restriction->y = 0;
	restriction->z = mEngine->getSize()->x;
	restriction->o = mEngine->getSize()->y;
	player.get()->setMovementRestriction(restriction);

	std::shared_ptr<Projectile> projectile(new Projectile(mAssets->getTexture("laserBlue")));
	projectile->getBody()->h *= 0.7;
	projectile->getBody()->w *= 0.7;
	player->setProjectile(projectile);

	std::shared_ptr<Sound> laserSound(new Sound(mAssets->getChunk("laser")));
	player->setProjectileFiringSound(laserSound);

	mPlayer = player;

	sprites.add("background", background);
	sprites.add("player", mPlayer);
	sounds.add("playerLaser", laserSound);
}

void PlayState::bindHooks()
{
	mKeyHooks.addHook(SDLK_a, std::bind(&Player::moveLeft, mPlayer.get()), SDL_KEYDOWN);
	mKeyHooks.addHook(SDLK_d, std::bind(&Player::moveRight, mPlayer.get()), SDL_KEYDOWN);
	mKeyHooks.addHook(SDLK_a, std::bind(&Player::stopMoveHorizontal, mPlayer.get()), SDL_KEYUP);
	mKeyHooks.addHook(SDLK_d, std::bind(&Player::stopMoveHorizontal, mPlayer.get()), SDL_KEYUP);
	mKeyHooks.addHook(SDLK_SPACE, std::bind(&PlayLogic::playerShoot, mPlayLogic), SDL_KEYDOWN);
}
