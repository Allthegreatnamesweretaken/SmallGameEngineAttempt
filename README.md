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