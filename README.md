## A3Engine

My personal project that I've been working on to learn and improve my technical skills.

### Why?

While commercial engines like Unreal, Unity, or Godot are incredibly powerful, they are designed as general-purpose tools. This generality often comes with layers of abstraction and overhead that can hinder the development of highly specialized systems.

This project is driven by the need for architectural control and workflow efficiency. My goal is to build an environment where:
- Deep Tool Integration: Instead of fighting a generic editor, I can build native tools tailored to specific mechanics—such as complex crowd systems or custom AI behaviors that feel like a core part of the engine rather than a plugin.
- Native Debugging: Having the ability to implement low-level debugging visualizers that are deeply integrated with the engine's internal state.
- Performance: Designing the core architecture (memory management, task scheduling) specifically for the types of games I want to create, removing the "black box" limitations of commercial software.

This is a journey to improve my knowledge in game development, practical optimization, project architecture, and to use this project as a portfolio piece because it seems interesting to me. Is it a difficult project? Yes. Am I trying to reinvent the wheel? Maybe. But I like to challenge myself.

### Design Inspirations
This engine's architecture isn't built in a vacuum. It is the result of extensive research into industry-leading proprietary technologies. I have spent significant time analyzing how AAA studios solve complex problems to implement similar philosophies here:
- Decima Engine (Guerrilla Games): My primary inspiration. I’ve deeply studied their public technical presentations and GDC talks regarding their world-building tools and systemic approach to game design.
- RE Engine (Capcom): A major reference for the engine's internal structure. Its efficiency in first-person titles and modular design heavily influences how my engine handles camera systems and tight gameplay loops.
- Northlight (Remedy Entertainment): Studied for its advanced integration of storytelling tools and physics-based interactions.
- RAGE (Rockstar Games): Analyzed through available technical insights (and historical data) to understand high-performance data streaming and world management.

By synthesizing the best practices from these different architectures, I am building a focused environment that prioritizes the workflow of specific genres rather than trying to be a "jack of all trades."

### Features

My focus isn't on working with the renderer, doing lighting, shadows... No. My focus is solely on its usefulness for creating gameplay systems and developing native tools within the engine to conduct experiments I might want to do in the future.

### What has already been done

#### Engine
- Input System
- Asset System
- ImGui Layer

#### Editor
- Content Browser
- File System handling
- Tab Systems

#### General
- PCH

### Planned to be implemented
- RTTI (Run-Time Type Information)
- Threading
- Resource Managing
- Custom memory allocations
- Event Queue

### Libraries used
```md
- glad
- GLFW
- glm
- ImGui
- ImGuizmo
- Jolt
- nlohmann-json
- yaml-cpp
- stb
- tiny_gltf
```