# UnrealCon — Construction Simulator

A new Unreal Engine project for a mobile-first, realistic construction equipment simulator. This repository is intentionally separate from the browser-game repositories.

## Project status

- Unreal Engine project descriptor and C++ runtime module scaffolded.
- Initial vehicle pawn and spring-arm follow camera added.
- Basic keyboard/gamepad movement mappings included.
- Android and Windows are the initial target platforms.
- This is a foundation, not yet a packaged or playable APK. No Unreal Engine installation is available in the GitHub runner by default, so a successful GitHub source check must not be mistaken for an Unreal compile or Android package.

## Open the project

Open `UnrealCon.uproject` with Unreal Engine 5.5 or a compatible later 5.x release. Generate IDE project files if prompted, then build the `UnrealConEditor` target.

## First playable milestone

1. Create a construction yard test map and lighting.
2. Add realistic machine meshes and wheel/track physics.
3. Replace the prototype pawn movement with Chaos Vehicles where appropriate.
4. Add mobile touch controls, camera orbit and pinch zoom.
5. Build and test an Android package on a real device.

## Android

Enable Android platform support in the installed Unreal Engine version and configure the Android SDK/NDK required by that engine release before packaging. The project has not yet been packaged or device-tested.
