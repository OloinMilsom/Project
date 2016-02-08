#include "Scene.h"

Scene::Scene(){

}
Scene::~Scene(){

}

void Scene::buttonsStop(){
	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i].setSelected(false);
	}
}
