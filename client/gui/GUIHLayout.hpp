#pragma once

#include "GUILayout.hpp"

class GUIHLayout : public GUILayout
{
public:
  GUIHLayout(int x, int y, int width, int height, int padding, GUILayout *layout, int nbElements = 100);
  GUIHLayout(int x, int y, int width, int height, int padding, int nbElements = 100);
  ~GUIHLayout();

  virtual void draw(double elapseTime);
  virtual void draw(int x, int y, double elapseTime);

  virtual bool handleGUICommand(InputCommand const &command);
};
