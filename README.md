TweakPNG-qt
===========

The cross-platform port of TweakPNG tool.

For usage instructions, see [tweakpng.txt](docs/tweakpng.txt).


LICENSE
----
Released under GPLv3 license.

Original code by Jason Summers [Web site](http://entropymine.com/jason/tweakpng/)

Please refer to [COPYING.txt](docs/COPYING.txt).

TODO
----
- Split interface windows into separate ui .qml files
- Test the code to be error-free in Qt Creator (for younger folks to contribute)
- Full APNG/MNG/JNG support (including playing animation inside the viewer)
- Compatibility with Qt5
- Test on both Mac and Windows platforms
- Dynamic window icon
- Undo/Redo
- Drag & Drop support of files and chunks (between the tabs?)
- Tabbed interface
- Localization via Qt's .ts i16n framework
- support for stdin pipe (and maybe stdout > ?)
- "What you're about to save is not going to be an image file" confirmation window upon save.
