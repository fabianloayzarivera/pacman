#include "Dot.h"
#include <stdio.h>
Dot::Dot(Vector2f aPosition)
: StaticGameEntity(aPosition, "Small_Dot_32.png", ETextureId::DOT)
{
}

Dot::~Dot(void)
{
}
