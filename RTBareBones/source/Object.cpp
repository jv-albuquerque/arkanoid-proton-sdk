#include "PlatformPrecomp.h"
#include "Object.h"

uint32 Object::makeRGBA(CL_Vec4f _color)
{
	return MAKE_RGBA(_color.r, _color.g, _color.b, _color.a);
}
