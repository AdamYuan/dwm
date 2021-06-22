# AdamYuan's DWM build
## Features
* Integrate xfce4-panel (perfectly) for systray and status.
* **WINDOW ICONS** (use stb_image_resize.h to resize icons to the required size).
* Title bar is transformed to tab bar in monocle mode.
* Other small [patches](https://github.com/AdamYuan/dwm/tree/master/patches)
## Screenshots
![](https://raw.githubusercontent.com/AdamYuan/dwm/master/screenshots/1.png)
![](https://raw.githubusercontent.com/AdamYuan/dwm/master/screenshots/2.png)
## Notes
For performance considerations, the code is compiled in 32-bit mode (with **-m32** in [config.mk](https://github.com/AdamYuan/dwm/blob/master/config.mk)), which can ensure that *sizeof(unsigned long) == 4* and improves window icon processing speed. You can remove the **-m32** flag if preferring an 64-bit build.
