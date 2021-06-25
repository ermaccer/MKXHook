# MKXHook
A plugin for Mortal Kombat X.


# Installation

*Release section files already have UAL, use them if you have no idea what to do here, just drag'n'drop .zip contents to MortalKombatXDirectory\Binaries\Retail.*



**NOTE: You might need to turn off in-game V-Sync if 60 fps patch is not applied!**

**NOTE: This will work with DX11 (default) only! If you use DX10 or DX9 switches, please remove them.**

MKXHook requires Ultimate ASI Loader(https://github.com/ThirteenAG/Ultimate-ASI-Loader/releases). Download **Ultimate-ASI-Loader_x64.zip**
, extract dinput8.dll from the archive to MortalKombatXDirectory\Binaries\Retail. Extract MKXHook.asi and .ini to the same directory.


ImGui settings (position, size) are saved in imgui.ini in root folder.

Some plugin features can be toggled on or off in the .ini.

## Features

### Playable NPCS
 - You can play as Rain, Baraka, Corrupted Shinnok or original Tanya.
 - Using this plugin, NPCs can be finished and have correct announcer (finish him/her)
 
### Camera Control
 - Free Camera
 - Manual Camera Position
 - Pre-set Camera modes: 1ST and 3RD person cameras
 
### Player Control
 - You can modify speed of player action
 - You can change visual scale
 
### Stage Control
 - You can play on any stage you like - even Red Jinsei stage.
 - You can reset stage objects (throwable stuff)

### 60 FPS Patch
 - MKX has a 30 fps cap for frontend menus, X-Rays, intros and fatalities, with this plugin it can be unlocked to 60
 - **If your PC does not meet requirement specs, turning this option on might have negative impact on perfomance!**
 

### Skip Asset Hash Check 
 - You can use custom skins without the need to update TOC tables.
 - **Enabling this feature will lock you out of Faction Wars and Online games! (of course disabling it restores the ability)**
 
### Misc. Tweaks 
 - You can disable sweat effect generation on characters.
 - You can disable combo damage scaling.


### Variation Manager
 - You can load multiple variations for one character
 - You can mix various variations (this will crash with some!)



![Preview](https://raw.githubusercontent.com/ermaccer/ermaccer.github.io/gh-pages/assets/mods/mkx/mkxhook/1.jpg)

# Used stuff
DirectX11 Hook based on:
https://github.com/rdbo/ImGui-DirectX-11-Kiero-Hook

https://github.com/CookiePLMonster/ModUtils

https://github.com/ocornut/imgui

https://github.com/Rebzzel/kiero


MKXHook was compiled & tested using Visual Studio 2017.

 
