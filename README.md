# UnrealCon — Construction Simulator

A new Unreal Engine project for a mobile-first, realistic construction equipment simulator. This repository is intentionally separate from the browser-game repositories.

## Current prototype work

- Unreal Engine 5.5 C++ project scaffold and game module.
- Prototype wheel loader silhouette with cab, chassis, wheels, lift arms and bucket.
- Follow camera with mouse/gamepad orbit input.
- Basic keyboard/gamepad driving controls.
- Runtime-generated construction yard: ground, access road, workshop, parts store, material bays, aggregate piles and equipment pad.
- Basic directional and sky lighting.
- Android and Windows are the initial target platforms.

## Current limitations

This is still an early source prototype. The loader uses Unreal's built-in primitive meshes; it does not yet have production machine models, Chaos vehicle physics, articulated hydraulics, touch controls, mission systems, or an Android package. The GitHub Actions workflow currently validates project files only; it does not compile Unreal Engine.

## Open the project

Open `UnrealCon.uproject` with Unreal Engine 5.5 or a compatible 5.x installation. Generate IDE project files if prompted, then build the `UnrealConEditor` target and press Play. The game mode spawns the yard and the prototype loader when the level starts.

## Controls (prototype)

- W / S: forward / reverse
- A / D: steer
- Mouse: orbit camera
- Gamepad left stick: drive / steer
- Gamepad right stick: orbit camera

## Next playable milestones

1. Replace primitive placeholder geometry with realistic loader and site assets.
2. Implement proper vehicle physics and articulated loader hydraulics.
3. Add mobile touch joysticks, camera orbit and pinch zoom.
4. Add equipment yard interaction, loading and unloading tasks.
5. Build and test an Android package on a real device.

## Android

Enable Android platform support in the installed Unreal Engine version and configure the Android SDK/NDK required by that engine release before packaging. No APK has been produced or device-tested yet.
