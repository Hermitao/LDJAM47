#include "game.h"
#include "sprite_renderer.h"
#include "resource_manager.h"
#include "box2d/box2d.h"

// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(200.0f, 200.0f);

SpriteRenderer  *Renderer;
GameObject* Player;

Game::Game(unsigned int width, unsigned int height) 
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{ 
	
}

Game::~Game()
{
    delete Renderer;
}
  
void Game::Init()
{
    // load shaders
    ResourceManager::LoadShader("shaders/sprite.vert", "shaders/sprite.frag", nullptr, "sprite");
    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), 
        static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // set render-specific controls
    Shader spriteShader = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(spriteShader);
    // load textures
    ResourceManager::LoadTexture("textures/minotaur.png", true, "minotaur");
    ResourceManager::LoadTexture("textures/block.png", false, "block");
    ResourceManager::LoadTexture("textures/block_solid.png", false, "block_solid");
	// load levels
    GameLevel one; one.Load("levels/one.lvl", this->Width, this->Height / 2);
    this->Levels.push_back(one);
    this->Level = 0;
    // player
	glm::vec2 playerPos = glm::vec2(
        this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, 
        this->Height - PLAYER_SIZE.y
    );
    Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("minotaur"));


}

void Game::Update(float dt)
{
}

void Game::ProcessInput(float dt)
{
   
}

void Game::Render()
{
    if(this->State == GAME_ACTIVE)
    {
        // draw level
        this->Levels[this->Level].Draw(*Renderer);

        Player->Draw(*Renderer);
    }
}  
