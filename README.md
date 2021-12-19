# MKXHook
A plugin for Mortal Kombat X.


# Installation

####  MKXHook only works with latest Steam version!

You can download binary files from [Releases](https://github.com/ermaccer/MKXHook/) page. Extract **mkxhook.zip**
to Binaries\Retail folder of Mortal Kombat X.

If you are not sure how to find your Mortal Kombat X folder, search for it in your Steam library then right click on the entry and select Manage->Browse local files.

Archive breakdown:

 - dinput8.dll - [Ultimate ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader/)
 - MKXHook.asi 
 - MKXHook.ini - configuration file



## NOTE
Since some people might use this plugin for 60 fps patch only, download the `_60only.zip` archive.

# Controller Support
Any XInput compatible gamepad should work.

## Gamepad Controls
| Button | Effect |
| --- | --- |
| L3 + R3 | Open/Close menu|
| X | Adjust menu|
| A | Select |
| B | Back |
| D-Pad | Move/ Scale menu in adjust mode |
| Left Stick | Move menu in adjust mode |

Gamepad support can be disabled in the .ini file by setting **bEnableGamepadSupport** to false.

**NOTE: You might need to turn off in-game V-Sync if 60 fps patch is not applied!**

**NOTE: This will work with DX11 (default) only! If you use DX10 or DX9 switches, please remove them.**


# Usage

If installed correctly, a notification will appear informing that the plugin was installed
and is ready to use. By default **F1** will open or close in-game menu.

![Preview](https://raw.githubusercontent.com/ermaccer/ermaccer.github.io/gh-pages/assets/mods/mkx/mkxhook/1.jpg)


## Features
| Feature | Description |
| --- | --- |
|60 FPS Patch| <ul><li>Removes 30 fps lock from X-Rays, intros and fatalities.</li><li>**If your PC does not have required hardware, turning this option on might have negative impact on perfomance!**</li></ul> |
|NPC Fixes | <ul><li>Female NPCs correctly play "Finish Her" and all NPCs can be finished.</li> <li>Rain now uses Kung Lao's victory pose.</li></ul> |
|Disable Sweat Effect | <ul><li>Disables the sweat effect that appears during fights</li></ul> |
| | **Menu Features**| 
|Character Modifier| <ul><li>Play as NPCs - Rain, Baraka, Sindel or Corrupted Shinnok.</li><li>Change forced character in story mode or other modes.</li></ul>|
|Stage Modifier| <ul><li>Change stage to anything in any game mode.</li></ul> |
|Variation Manager| <ul><li>Load multiple variations for one character.</li><li>Use other character variations (this will crash with certain variations!) </li></ul> |
|Player Control| <ul><li>Change speed and scale of players.</li><li> Scale setting is *visual* only!</li></ul> |
|Speed Modifier| <ul><li>Change game speed, enjoy fights in slowmotion!</li></ul> |
|Camera Control| <ul><li>Freeze camera position & rotation.</li><li>Freely move and rotate camera with keyboard hotkeys.</li><li>Play in predefined custom camera modes: <ul><li>3RD Person</li><li>1ST Person</li></ul> </ul></li> |
|Cheats| All cheats can be toggled for both P1 and P2<ul><li>Infinite Health</li><li>Zero Health</li><li>1 Health</li><li>Infinite Super Bar</li></ul> |
|Misc.| <ul><li>Unlock all costumes.</li><li>Disable combo scaling.</li></ul> |



![Preview](https://raw.githubusercontent.com/ermaccer/ermaccer.github.io/gh-pages/assets/mods/mkx/mkxhook/3.jpg)
![Preview](https://raw.githubusercontent.com/ermaccer/ermaccer.github.io/gh-pages/assets/mods/mkx/mkxhook/2.jpg)
![Preview](https://raw.githubusercontent.com/ermaccer/ermaccer.github.io/gh-pages/assets/mods/mkx/mkxhook/6.jpg)

# Building

MK11Hook was developed & tested using Visual Studio 2017.




# Credits/Used stuff

https://github.com/CookiePLMonster/ModUtils

https://github.com/ocornut/imgui

https://github.com/Rebzzel/kiero

D3D11 hook based on https://github.com/rdbo/ImGui-DirectX-11-Kiero-Hook
