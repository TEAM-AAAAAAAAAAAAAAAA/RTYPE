<h1 style="text-align: center">ECS MANUAL</h1>
--------------------------------------------------------------------------------------------

Before explaining systems and components' methods, lets have a look on the architecture diagram of the ECS. 

>Just note that there is no trash struct called Entity_t containing the whole of the data. 
>Entity are only represented by ID/index and which component is assigned on this ID
	  
First of all, let's define the terms in an increasing architectural way

-----------------------------------------------------------------------
<h3 style="text-align: center; color:orange">Components</h3>
--------------------------------------------------------------------------------------------


They are most of the time struct/class containing some obvious fact.
As example, Component Position : 
```Cpp
struct Position {  
	int x;  
	int y;  
};
```

-----------------------------------------------------------------------
<h3 style="text-align: center; color:orange">Sparse Array</h3>
--------------------------------------------------------------------------------------------


It's a wrapper around a std::vector used to store components of Entities.
It got all the utility as a normal vector (end(),  begin()...).
The special feature of the SparseArray class is that its size never gets smaller.
Even if an Entity disapears or is deleted, we only put a `std::nullopt` at his component location, in this way it could be reused after.
Sparse array Class private members : 

```c++
std::vector<std::optional<Component>> _data
```

It represents the vector of each component in the current world.


-----------------------------------------------------------------------

<h3 style="text-align: center; color:orange">Systems</h3>
--------------------------------------------------------------------------------------------

Systems are the things that directly interacts with components.
They actually get all the associated components in order to actualize Entities' values.
They are generated in lambda format and pushed in the private vector of the current world.
They look like this : 

```c++
std::function<void(World &)> movement = [](World &world) {  

	// Get all the components related to the system
    auto &positions = world.registry.getComponents<component::Position>();  
    auto const &velocities = world.registry.getComponents<component::Velocity>();  
    auto &directions = world.registry.getComponents<component::Direction>();  
    using chrono = std::chrono::high_resolution_clock;
    static auto clock = chrono::now();
    
    // Loop on every components and apply the logic of the system
    for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {  
        auto &pos = positions[i];  
        auto const &vel = velocities[i];  
        auto &dir = directions[i];  
        if (pos && vel) {
 
        // The goal of this is to update Entities values
            if (std::chrono::duration<double, std::milli>(chrono::now() - clock).count() > 10) {  
                pos.value().x += vel.value().x * (dir.value().x);  
                pos.value().y += vel.value().y * dir.value().y;  
                dir.value().x = 0;  
                dir.value().y = 0;  
                clock = chrono::now();  
            }  
        }  
    };  
};
```


-----------------------------------------------------------------------

<h3 style="text-align: center; color:orange">Registry</h3>
--------------------------------------------------------------------------------------------

This is the most interesting part if we talk about managing components because it's the **Components Manager** by definition.
It consists of two main methods :

``` c++
template <class Component> SparseArray<Component> &registerComponent()
```

This function is not used by the developper but it allows, in back end, a new type of components in the registry.
In the same way, the component stores a self delete methods as a lambda in a `_eraseFunc` private vector.
		
```c++
typename SparseArray<Component>::referenceType addComponent(Entity const &to, Component &&c)
```

If your objective is to add a new component to the Sparse Array, you are at the right place.
Let's just define what a world is before giving you a good example of adding a component and making it run properly.

Registry Class Private Member

```cpp
std::unordered_map<std::type_index, std::any> _componentsArrays;
```

It represents the group of components already registred by the registerComponent method

``` c++
std::vector<std::function<void(Registry &, Entity const &)>> _eraseFunctions;  
```

It represents the vector of self erase lambda of each component


```c++
std::vector<std::size_t> _entitiesBin;  
```

It represents the bin of every deleted entities, used to recover an entity instead of creating another one

```c++
std::size_t _lastEntity;
```

It represents the current number of entities used or able to be used in the Registry Class

-----------------------------------------------------------------------
<h3 style="text-align: center; color:orange">Worlds</h3>
--------------------------------------------------------------------------------------------
It is at the top of the architecture because it contains all the terms seen before.
In a more concrete way, we can see worlds as scene.
For example, in the Game part, we can see different worlds : 

- World Menu
- World GameLogic

In this way, world contains every useful component & system which is associated with it.
For example, we'll not use component Position or Velocity in the server world.

```c++
std::unique_ptr<sf::RenderWindow> &_window;  
```

The window used to display any information by the World class

``` c++
std::vector<std::function<void(World &)>> _systems;  
```

Private system's vector of the World class 

```c++
std::stack<ecs::Event> _events;
```

Private events' stack of the World class

-----------------------------------------------------------------------
<h3 style="text-align: center; color:orange">Example</h3>
--------------------------------------------------------------------------------------------

Now that we have a better visualization of what composes the ecs, we can see how we can use it.

Now let's decompose our main function who's actually creating a world, spawn two entities and gives the player the possibility to move  and shoot :
```c++
int main()  
{  
    ecs::Engine engine;
    
    // initialization of the world
    ecs::World ourNewWorld = getGameWorld(engine);
    
    // set the world as ready to use
    engine.setWaitingWorld(ourNewWorld);  

	// run the engine
    engine.run();  
    return 0;  
}
```

<h3 style="text-align: center"> Initialization of the world</h3>

```c++
ecs::World getGameWorld(ecs::Engine &engine)  
{  
	// In this example just below, to begin we can see a creation of a new world
    ecs::World world(engine.getWindow());  

	// After that we are able to create our first entity
    ecs::Entity player = world.registry.spawn_entity();
    
	// it's now time to create a new entity and to add its associated components
    world.registry.addComponent<ecs::component::Position>(player, {10, 10});  
    world.registry.addComponent<ecs::component::Velocity>(player, {5, 5});  
    world.registry.addComponent<ecs::component::Size>(player, {2, 2});  
    world.registry.addComponent<ecs::component::Direction>(player, {1, 0});
    
	// To finish, we now want to add associated systems
    world.addSystem(ecs::systems::positionLogger);  
    world.addSystem(ecs::systems::movement);   
    return world;  
}
```

<h3 style="text-align: center">Set the world</h3>

```c++
void setWaitingWorld(ecs::World world, bool worldSwitchReady = true)  
{  
	// Delete the previous world in waiting mode
    if (_waitingWorld)  
        _waitingWorld.release();
    
    // Set the \_waitingWorld with the world given as parameters
    _waitingWorld = std::make_unique<ecs::World>(world);

	// Set the \_worldSwitchReady, true by default
    _worldSwitchReady = worldSwitchReady;  
}
```

<h3 style="text-align: center">Run the Engine</h3>

```c++
void run()  
{  
    while (_window->isOpen()) {
    
	    // Simply loop on every systems and run them
        _currentWorld->runSystems();
        
        // if the current world is ready to switch, an automaticaly switch occure
        if (isWorldSwitchReady())  
            switchWorlds();  
    }  
}
```