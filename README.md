# TP Shooter
Third person shooter game demo project in Unreal Engine 5

![ScreenShot00000](https://github.com/sinamhdn/unreal-tpshooter/assets/34884156/d21e86f9-b8b5-4bfb-8be8-cd8fbfb3084e)

## Unreal Engine Version
5.3

## Asset Packs
- Paragon: Wraith
- Modular SciFi Season 1 Starter Bundle
- Modular Scifi Season 2 Starter Bundle
- Shooter Game only project assets

## Concepts
- Game Design architecture
- Migrating assets from a project to other
- Setting a map as default map of the editor
- Difference between Pawn and Character
- Adding a new c++ class and creating a blueprint based on it
- Adding mesh to character blueprint
- Setting default pawn inside game mode blueprint
- How to do input binding
- How to use UPROPERTY for variables to be editable in editor and garbage collected
- Adding camera and spring arm to the character blueprint
- Animations that act as a bridge between Mesh and Skeletons
- How to edit collision box of assets
- Creating variables in Blueprint
- Blending multiple animations using blend node and trigger them with boolean value
- Using 2D Blend Spaces assets to blend animations easier
- Convert Local transformation to Global and vice versa
- Direction vs Position vector
- Spawning an actor from other actor
- Hiding skeleton to hide part of the asset
- Spawning actors on asset sockets
- Spaning particle effects on sockets
- Creating debug helpers for camera direction using DebugCameraHelper
- Linetracing and Trace Channels
- FPointDamageEffect and FRadialDamageEffect
- Create blueprint callable functions
- AIController to create AI
- AI focal points
- AI pathfinding using Nav Mesh Bounds Volume
- Using Behavioral Trees and Blckboards to create AI
- Using behavioral tree decorators to add conditions
- Using behavioral tree decorators to add logic to a node
- Creating custom behavioral trees task in c++
- Creating custom behavioral trees service in c++
- Implementing games general logic in a game mode blueprint based on c++ blueprint
- Creating UI in unreal
- Adding a wav file as audio to an asset
- Using Audio Cue asset to add multiple audios to an asset or world
- Randomize audios in Audio Cue
- Sound Attunement and Spatialization is sound cue
- AnimOffset assets to accumulate animation over other animations
- Animation state machines
- Adding ambience sound to the game
- Adding sound to a socket on skeleton
- Creating health system
- Creating aim system
- Adding and using tags on blueprint and c++
- Changing collision and trace channel reaction type on a specific blueprint

## Important Note
IF YOUR GAME GLITCHES IN SOME POINTS OF MAP \
SOME ASSETS IN ASSET PACKS CAUSE COLLISION MESH ERROR \
TO FIX IT CHANGE TO VISIBILITY COLLISION OR PLAYER COLLISION \
TO SEE COLLISION BOX OF OBJECTS AND EDIT THE COLLIION BOXES THAT ARE STICKING OUT

EDIT SM_Ceilling_Ring_A2 ASSET AND REMOVE STICKING OUT PART FROM ITS COLLISION BOX

TO DISABLE DEFAULT GUN OF PARAGON WRAITH OPEN PLAYER ASSET YOU USE > SELECT SKELETON > HIDE weapon_r AND weapon_l \
YOU CAN DO THIS ALSO IN CODE IN CHARACTER BLUEPRINT OR ANIMATION BLUEPRINT \
IN THIS PROJECT WE HIDE BONES IN SCRIPT

OPEN PLAYER CHARACTER ASSET > GO TO SKELETONS SECTION > SELECT weapon_r (OR weapon_l) bone > ADD weapon_r_socket to it (socket name is important)

OPEN GUN ASSET YOU USE AND ADD muzzle_flash_socket SOCKET AT THE TIP FOR PARTICLE EFFECT TO SPAWN
