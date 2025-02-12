#include "D3DFramework.h"
#include <directxcolors.h>
#include <vector>
#include "Resource.h"
#include <string>
#include <sstream>
#include <algorithm>
#include <set>
#include "DDSTextureLoader.h"
#include <unordered_map>
#include <iostream>
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "directxcollision.h"
//Can be final but want scene changes first.

/*Need to Do list:
---Updated---
-Correctly made it so that the game can determin when the player is looking at an object and lets them be able to use the launch (Need to make sure i set the distance properly.


---Priority---
-Need to not make the scope too huge this is meant to be a very small project that i can remake or edit in the future.
Next Milestone >> --Very Simple Demo--
-Need a very basic menu to start the game, this will be the first thing that the player sees.
-Need a simple level for testing purposes, this will be the first level that the player will play, this will be given in the demo for people to test for me.
-Need to add a way for the game to end like a win condition probably will be an object they hit thagt gives them a you win screen?
--Need to have it tested want the game to actually be fun to play, if needed to change things do so but keep it simple.

--Need to add a way to load different levels without errors, either through doing it in a menu and stopping the player or loading everything and only setting the specific shader when the player loads the level?
- Need to work on redoing everything seperating it all into different files, this could help efficiency and make it easier to read, will also help with the fact that the code is getting very long.
- Need to refine the shaders (if i am keeping them) as the way they are loaded and managed currently is not efficient.
- File manager, for simplicity of being able to find parts of code easier, as in files for shaders etc etc.

-- Maps could be done by having a map loader that loads in the objects and textures, the map loader would be built from config files that would be loaded in at the start of the game, menu would pick between them.


- Remember to Update the README everytime i push a new change.
---Secondary---
- FPS limiter, need to add one as i can hear my fans crying every time i run this. (Maybe find a way to load faster(Or it could be just how DX11 loads?))
- Fix Collision as the player can still currently warp up through the floor.

- Need to think more about how the game will work, while the baseline is okay need more idea on it like multiple guns? More maps? Enemines? and general feeling for the game.
-- Am liking the idea of a base parkour game for the beginning, can add multiple guns with a switch statment to change the way they fire,(And maybe their model) Enemies would be a long way off if not impossible because of the way the game is designed. 

-- Have Implemented new movement as a way around, this movement is only controlled by the W key and the player moving the mouse the player loses controller of the W key while in air and has to reply on the launching to get to the end.
- Add in a way to let the player have in air controls to make teh movement while falling feel smoother, can also change gravity if needed as it right now is strange.
- change the wya the shaders are loaded should be able to be done in a loop.
- Change the way they are added to an object should be able to do that inside of where we create the object.
*/

std::unique_ptr<D3DFramework> D3DFramework::_instance = std::make_unique<D3DFramework>();
//Config can stay as a way of loading objects can be changed later on though if can think of better method. Also see if Objects can be laoded that aren't an obj / are more efficient.
bool D3DFramework::LoadConfig(const std::string& pathname) {

	//Left here for simplicity of loading in objects and textures, can be changed later on.
	std::ifstream fin(pathname);
	if (!fin) {
		return false;
	}

	std::string tag;
	while (fin >> tag) {
		if (tag == "name") {
			ObjModel tempObject;
			std::string objectName;
			fin >> objectName;
			objectNames.push_back(objectName);
			_modelLoader.LoadOBJ(objectName, tempObject);
			_models.push_back(tempObject);
		}
		else if (tag == "texture") {
			std::string texturePath;
			fin >> texturePath;
			textureNames.push_back(texturePath);
		}
		else if (tag == "position") {
			XMFLOAT3 vertex;
			fin >> vertex.x >> vertex.y >> vertex.z;
			objectPositions.push_back(vertex);
		}
		else if (tag == "player_position") {
			fin >> _firstObjectPosition.x >> _firstObjectPosition.y >> _firstObjectPosition.z;
		}
		else if (tag == "light_direction") {
			fin >> _initialSunLightDirection.x >> _initialSunLightDirection.y >> _initialSunLightDirection.z;
			_lightDirection = _initialSunLightDirection;
		}
		else {
			std::string line;
			std::getline(fin, line);
		}
	}
	return true;
}

//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
D3DFramework::~D3DFramework() {
	try {
		if (_pImmediateContext)
			_pImmediateContext->ClearState();
	}
	catch (...) {

	}
}


void D3DFramework::zoomIn() {
	if (_zoomFactor > 0.1f) {
		_zoomFactor -= 0.1f; // Decrease zoom factor, but not less than 0.1
		updateViewMatrix();
	}
}
size_t i = 0;
void D3DFramework::zoomOut() {
	if (_zoomFactor < 10.0f) {
		_zoomFactor += 0.1f; // Increase zoom factor, but not more than 10.0
		updateViewMatrix();
	}
}
