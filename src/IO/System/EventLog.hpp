#pragma once
#include "Singleton.hpp"
#include "details/PrintFieldVisitor.hpp"
#include <iostream>

namespace sw::io
{
	class EventLog: public Singleton<EventLog>
	{
	public:

		template <class TEvent>
		void log(uint64_t tick, TEvent&& event)
		{
			std::cout << "[" << tick << "] " << TEvent::Name << " ";
			PrintFieldVisitor visitor(std::cout);
			event.visit(visitor);
			std::cout << std::endl;
		}
	};
}
