# GEPAA Game Engine #

This repository contains the source code for the GEPAA Game Engine, a team-developed Game Engine built for the 
Game Engine Programming and Architecture module at Staffordshire University. 

Created by: Alex Scott, Myriam Sarah, Paul-Emile Kim.

## Useful Links ##

* [Module Page](http://www.staffs.ac.uk/current/student/modules/showmodule.php?code=COSE70635)
* [Private Trello Board](https://trello.com/b/jZPgM3R2/gepaa-group-1)

## Running the application ##
Ideally run the solution in Visual Studio 2017. Make sure the build configuration is set to StandaloneDebug
and the platform is any CPU or x64. If you want to run tests make sure the test processor architecture is
set to x64.

## Architecture Overview ##
There are two main parts to the engine: Systems and Messaging; and Scenes and GameObjects. 
I will briefly go over each.

### Systems and Messaging ###
Every significant part of the engine is classed as a system, and must inherit from ISystem. 
This includes things suchs as Graphics, Input, Networking, file I/O etc. Currently there's only a 
few systems implemented, mainly to demonstrate their usage. To register a new system, make sure it 
inherits ISystem and also make sure it is initalised in the SystemManager class. 

Systems can communicate with other systems by sending messages through the SystemMessageDispatcher, a 
singleton instance that has a job of delivering messages to the correct recipiants. To do this, 
systems must subscribe to a certain message type (an enum) with the SystemMessageDispatcher. Once doing 
this the SystemMessageDispatcher will deliver the messages to the system by calling the RecieveMessage() 
method in ISystem (which needs to be overriden). From here, the recieved message can be statically cast 
to any other message type and data can be extracted from it.

### Scenes and GameObjects ###
At any one time there is a single active scene, managed by the SceneManager system and built by the 
SceneBuilder system. Scenes must inherit from IScene and are esentially used to store all GameObjects 
and update/draw them. In the future multiple scene types will be added but for now there's no implementation
of it. GameObjects stored in scenes are used to hold components. 

Components are classes with custom functionality that is applied to the GameObject. Components must inherit 
from IComponent and can optionally inherit  IDrawable, IUpdateable and IMessageable. These additional 
interfaces are called at certain times and require the component to do certain things. For example, 
IDrawable components are required to send drawing information to the Graphics system. IUpdateable 
components have an Update function  that is called every frame. IMessagable components can recieve 
messages from other GameObjects/components. 

Currently only one component has been implemented: TransformComponent. This is a special component as 
every GameObject needs a transform. Component files should also contain a function in the 
ComponentFactory namespace that builds and returns an instance of the component.

## Code Flow ##
The application is initalised in Main.cpp. Here an instance of SystemManager is created. The purpose
of SystemManager is simply to initalise all other systems. First off the MainWindow is initalised, as
this is a slightly special system that requires arguments generated from WinMain and for the instance
to be updated regularly. Then all the other systems are initalised in the InitaliseSystems() function.

The Engine system is probably the highest level system. It controls when the Graphics system gets
initalised, when the current active scene gets built and when to draw/update the scene.

The Graphics system deals with what to draw each frame. It recieves start and end frame messages from
the Engine system and in the future will recieve drawing data from IDrawable components.

The SceneBuilder system deals with parsing scene XML files from disk and building a scene instance from it.

The SceneManagement system holds and stores the current scene and recieves draw/update messages from the engine.

## Future Features ##
### Input ###
An Input system will need to be created in the future. This system will inherit from ISystem and will need to
be added to the SystemManager initalisation function. Currently, the MainWindow system is sending input messages
to the SystemMessageDispatcher when it recieves them from the windows application, such as key or mouse press. 
The Input system will need to subscribe to this message type and then perform logic based on what it recieves.
The MainWindow system can also be improved to translate more message types and then also send those to the 
SystemMessageDispatcher, such as Xbox conntroller inputs or distinction between input methods (to allow for multiplayer).

### Graphics ###
The Graphics system can be extended to implement different graphics APIs such as DirectX or OpenGL. These new
APIs would need to inherit from IGraphics and implement all the required virtual functions. And in SystemsManager
the Graphics system instance would be created from this new API such as DX11Graphics.

The drawing functionality is currently incomplete. There is nothing calling the DrawSprite or DrawText functions
within IGraphics (or any implementation of it). The way this needs to be achieved is by creating a drawing
GameObject component, such as SpriteRendererComponent. This component would inherit IDrawableComponent and override
the Draw virtual function. Inside this function the component would send a DrawSpriteMessage containing
all the required drawing information. The Graphics system would need to be extended to recieve this message
and then add the sprite to the graphic API's draw list (sprite batch in DX11).