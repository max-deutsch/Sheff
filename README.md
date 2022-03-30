# Sheff
Sheff Engine based on https://github.com/TheCherno/Hazel

## How to get and initialize the Sheff Engine

1. `git clone https://github.com/max-deutsch/Sheff.git`

2. execute `Initialize.bat`

    Initialize pulls the submodules and generates the VS2019 Projects including a Sandbox Project that uses the Sheff engine.

3. Open `Sheff.sln`
4. Start Sandbox Project or implement your own Application using the Sheff Engine

## How to use the engine

An Example implementation can be found with the Sandbox Project. A subclass of Sheff::Application is required. The entry point of the application lies within the Engine.

## What has been implemented beyond the mandatory Cherno Videos?

### TheCherno videos
* Layers
    * Layers are used to define an order for updating and drawing application elements. e.g. A Game World Layer and an User Interface Layer. Overlays are always on top of the other layers.
* Modern OpenGL (Glad)
    * OpenGL 4.6 has been integrated
* ImGui
    * An ImGuiLayer is provides which tests the ImGui integration by drawing a demo window with the application window.