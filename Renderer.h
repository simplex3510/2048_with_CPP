#pragma once

#include "SingletonBase.h"

class Renderer : public SingletonBase<Renderer>
{
public:
	void RenderingTitle();
	void RenderingFrame();
};
