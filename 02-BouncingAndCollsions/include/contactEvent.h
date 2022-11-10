#pragma once
#include <iostream>
#include <box2d/b2_settings.h>

class Bouncer;
class Ball;

// Event Type -------------------------------------------
enum class ContactType
{
	Ball, Bouncer, None
};

class ContactEvent
{
public:

	ContactType TypeOfContact = ContactType::None;

	ContactEvent(Ball& ball) :
	TypeOfContact(ContactType::Ball),
	Ball(&ball)
	{
		
	};
	Ball* Ball = nullptr;

	ContactEvent(Bouncer& bouncer) :
	TypeOfContact(ContactType::Bouncer),
	Bouncer(&bouncer)
	{
		
	};
	Bouncer* Bouncer = nullptr;

	

};
