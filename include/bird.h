#ifndef BIRD_H
#define BIRD_H

#include <ariamis/object.h>

class Bird : public Ariamis::Object{
	public:
		Bird();

		glm::vec3 velocity;
};

#endif
