# GUI

## GUIComponents
Widgets use components just like Actors called GUIComponents. GUIComponent classes are prefixed with a G

GUIComponents give Widgets different properties.
For example, GButton makes the Widget clickable, and GText gives the Widget text.

## Z-Depth
The Z-Depth of a Widget represents how far back the Widget is from the front of the screen.

A Widget with a lower Z-Depth will be drawn over Widgets with a higher Z-Depth.
The lowest Z-Depth value is 0. Negative numbers will be converted to 0 by the Renderer2D.
