#include "Scene.hpp"
#include "Board.hpp"

Scene::Scene(int pScreenWidth, int pScreenHeight) : screenWidth(pScreenWidth), screenHeight(pScreenHeight)
{
    
}

void Scene::init(const tBoardData pBoardData)
{
    mBoardData = pBoardData;
}

void Scene::update(const tBoardData pBoardData)
{
    
}

void Scene::draw()
{

}
