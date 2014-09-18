TweakPNG-qt
===========

The cross-platform port of TweakPNG tool.

For usage instructions, see [a relative link](docs/tweakpng.txt).


LICENSE
----
Released under GPLv3 license.

Original code by Jason Summers [Web site](http://entropymine.com/jason/tweakpng/)

Please refer to [a relative link](docs/COPYING.txt).

TODO
----
- Split interface windows into separate ui .qml files
- Test the code to be error-free in Qt Creator (for younger folks to contribute)
- Full APNG/MNG/JNG support (including playing animation inside the viewer)
- Compatibility with Qt5
- Test on both Mac and Windows platforms
- Dynamic window icon
- Undo/Redo
- Tabbed interface
- Drag & Drop support of files and chunks (between the tabs?)
- Localization via Qt's .ts l18n framework
- support for stdin pipe (and maybe stdout > ?)
- "What you're about to save is not going to be an image file" confirmation window upon save.
