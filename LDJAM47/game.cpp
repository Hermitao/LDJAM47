#include "game.h"
#include "sprite_renderer.h"
#include "resource_manager.h"

SpriteRenderer  *Renderer;

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
}

void Game::Update(float dt)
{
    
}

void Game::ProcessInput(float dt)
{
   
}

void Game::Render()
{
    Texture2D minotaurTexture = ResourceManager::GetTexture("minotaur");
    Renderer->DrawSprite(minotaurTexture, glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
}  
