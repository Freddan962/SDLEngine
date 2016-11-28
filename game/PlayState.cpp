#include "PlayState.h"
#include "../AssetContainer.h"
#include "../Engine.h"
#include "../AssetLoader.h"
#include "../Sprite.h"
#include "Player.h"
#include "../SpriteCenterer.h"
#include "Projectile.h"
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

	
	AssetLoader loader(mEngine->getRenderer());
	mAssets->textures.add("bgPurple", loader.loadPNG(assetPath + "bgpurple.png"));
	mAssets->textures.add("player", loader.loadPNG(assetPath + "player.png"));
	mAssets->textures.add("laserBlue", loader.loadPNG(assetPath + "laserblue.png"));

	mAssets->chunks.add("laser", loader.loadOGG(assetPath + "laser.ogg"));
}

void PlayState::prepareEntities()
{
	std::shared_ptr<Sprite> background(new Sprite(mAssets->textures.get("bgPurple")));
	background->getBody()->h = mEngine->getSize()->y;
	background->getBody()->w = mEngine->getSize()->x;

	std::shared_ptr<Player> player(new Player(mAssets->textures.get("player")));
	SpriteCenterer::centerHorizontal(player.get(), mEngine->getSize()->x);
	player.get()->getBody()->y = mEngine->getSize()->y - player.get()->getBody()->h - player.get()->getBody()->h * 0.1;
	
	std::shared_ptr<Vector4<int>> restriction (new Vector4<int>);
	restriction->x = 0;
	restriction->y = 0;
	restriction->z = mEngine->getSize()->x;
	restriction->o = mEngine->getSize()->y;
	player.get()->setMovementRestriction(restriction);

	std::shared_ptr<Projectile> projectile(new Projectile(mAssets->textures.get("laserBlue")));
	projectile->getBody()->h *= 0.7;
	projectile->getBody()->w *= 0.7;
	player->setProjectile(projectile);

	std::shared_ptr<Sound> laserSound(new Sound(mAssets->chunks.get("laser")));
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
