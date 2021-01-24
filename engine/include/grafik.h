#pragma once

#define _PS_EXPAND(arg) _PS_STRING(arg)
#define _PS_STRING(arg) #arg
#define PROJECT_SOURCE _PS_EXPAND(_PROJECT_SOURCE)


#include <string>
#include <iostream>

#include "core/application.h"

#include "scene/GameObject.h"

