#include "contactListener.h"

#include <iostream>
#include <box2d/b2_contact.h>

#include "ball.h"
#include "bouncer.h"

void ContactListener::BeginContact(b2Contact* contact)
{
	std::cout << "Begin Contact" << std::endl;

	auto userDataA = contact->GetFixtureA()->GetUserData().pointer;
	auto userDataB = contact->GetFixtureB()->GetUserData().pointer;

	if (userDataA != 0 && userDataB != 0)
	{
		// Is the first object a ball?
		auto infoA = reinterpret_cast<ContactEvent*>(userDataA);
		auto infoB = reinterpret_cast<ContactEvent*>(userDataB);

		auto baballe = reinterpret_cast<Ball*>(userDataB);

		if (infoA->TypeOfContact == ContactType::Ball)
		{
			if (infoB->TypeOfContact == ContactType::Bouncer)
			{
				std::cout << "B is a bouncer and A is a ball" << std::endl;
				infoA->Ball->SetDead();
			}
			else
			{
				infoB->Ball->SetNewColor();
				infoA->Ball->SetNewColor();
			}
		}
		else if (infoB->TypeOfContact == ContactType::Ball)
		{
			if (infoA->TypeOfContact == ContactType::Bouncer)
			{
				std::cout << "A is a bouncer and B is a ball" << std::endl;
				infoB->Ball->SetDead();
			}
			else
			{
				infoA->Ball->SetNewColor();
				infoB->Ball->SetNewColor();
			}
		}

	}

}

void ContactListener::EndContact(b2Contact* contact)
{
	std::cout << "End Contact" << std::endl;
}