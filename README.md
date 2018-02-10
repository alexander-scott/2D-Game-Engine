# GEAPA Game Engine #

This repository contains the source code for the GEPAA Game Engine, a team-developed Game Engine built for the Game Engine Programming and Architecture
module at Staffordshire University. 

Created by: Alex Scott, Myriam Sarah, Paul-Emile Kim.

### Useful Links ###

* [Module Page](http://www.staffs.ac.uk/current/student/modules/showmodule.php?code=COSE70635)
* [Private Trello Board](https://trello.com/b/jZPgM3R2/gepaa-group-1)

### Architecture Overview ###
There are two main parts to the engine: Systems and Messaging; and Scenes and GameObjects. I will briefly go over each.

## Systems and Messaging ##
Every significant part of the engine is classed as a system, and must inherit from ISystem. This includes things suchs a Graphics, Input, Networking,
file I/O etc. Currently there's only a few systems implemented, mainly to demonstrate their usage. To register a new system, make sure it inherits ISystem
and also make sure it is initalised in the SystemManager class. 

Systems can communicate with other systems by sending messages through the PostOffice, a singleton instance that has a job of delivering messages to
the correct recipiants. To do this, systems must subscribe to a certain message type (an enum) with the PostOffice. Once doing this the PostOffice
will deliver the messages to the system by calling the RecieveMessage() method in ISystem (which needs to be overriden). From here, the recieved
message can be statically cast to any other message type and data can be extracted from it.

## Scenes and GameObjects ##
At any one time there is a single active scene, managed by the SceneManager system and built by the SceneBuilder system. Scenes must inherit from IScene
and are esentially used to store all GameObjects and update/draw them. In the future multiple scene types will be added but for now there's no implementation
of it. GameObjects stored in scenes are used to hold components. 

Components are classes with custom functionality that is applied to the GameObject. Components must inherit IComponent and can optionally inherit 
IDrawable, IUpdateable and IMessageable. These additional interfaces are called at certain times and require the component to do certain things. 
For example, IDrawable components are required to send drawing information to the Graphics system. IUpdateable components have an Update function 
that is called every frame. IMessagable components can recieve messages from other GameObjects/components. 

Currently only one component has been implemented: TransformComponent. This is a special component as every GameObject needs a transform. Component files
should also contain a function in the ComponentFactory namespace that builds and returns an instance of the component.