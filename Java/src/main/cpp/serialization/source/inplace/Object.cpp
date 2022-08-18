#include "Object.h"

map<thread::id, Allocator> Object::allocator;
