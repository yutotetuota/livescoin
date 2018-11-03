
Debian
====================
This directory contains files used to package livescoind/livescoin-qt
for Debian-based Linux systems. If you compile livescoind/livescoin-qt yourself, there are some useful files here.

## livescoin: URI support ##


livescoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install livescoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your livescoinqt binary to `/usr/bin`
and the `../../share/pixmaps/livescoin128.png` to `/usr/share/pixmaps`

livescoin-qt.protocol (KDE)

