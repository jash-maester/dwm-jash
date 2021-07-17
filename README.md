# This one is for my Ubuntu (21.04) System

## dwm - dynamic window manager
============================
dwm is an extremely fast, small, and dynamic window manager for X.

## Requirements
------------
In order to build dwm you need the Xlib header filesr, make, gcc

### Important !!!
  - `nobody` group is required for `slock` to work
    ```bash
    sudo groupadd nobody
    ```    

### Fonts:
  - FiraCode Nerd Font
  - Noto Sans Font
  - Font Awesome (Optional for weather and all)

### Dependencies:
  - Xlib, libXft, and Xinerama header files
  - Clipmenu: https://github.com/cdown/clipmenu
  - Clipnotify: https://github.com/cdown/clipnotify
    - libxfixes-dev, libxfixes3, x11proto-core-dev, libx11-dev 
  - Slock: https://github.com/khuedoan/slock
  - Skippy (For the Overview) : https://github.com/jash-maester/skippy-xd
    - Ubuntu: libjpeg-dev, libgif-dev
  - Flameshot : Screenshot tool
  - Xbanish : TO hide mouse pointer while typing


## Installation
------------
Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm:

    sudo make clean install


## Running dwm
-----------
Add the following line to your .xinitrc to start dwm using startx:

    exec dwm

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec dwm

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
    	sleep 1
    done &
    exec dwm


## Configuration
-------------
The configuration of dwm is done by creating a custom config.def.h
and (re)compiling the source code.
