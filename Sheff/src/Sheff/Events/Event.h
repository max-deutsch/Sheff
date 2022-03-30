#pragma once

#include "shpch.h"
#include "Sheff/Core.h"


namespace Sheff {

	// Events are currently blocking
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	// event types can be part of multiple categories
	// e.g. MouseButtonPressed is in the categories Input, Mouse and MouseButton
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};


	// This defines the standard implementations of the three given methods
	// This is handy because the same code does not have to be written multiple times.
	// The # is the stringify operator.
	// The ## is the concatinating operator.	
	// static function to retrieve the EventType is needed to call with a template type T (e.g. in EventDispatcher)
	// regular function to retrieve the EventType is needed to call with an Event instance.
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() {return EventType::##type; } \
								virtual EventType GetEventType() const override { return GetStaticType(); } \
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category;  }

	class SHEFF_API Event
	{
		friend class EventDispatcher;
	public:
		bool Handled = false;
		// these have to be implemented
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		// this has a default implementation, but can be overridden
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	};

	// This is a utility class to easily just subscribe to the desired Event Types.
	// The Dispatch function only handles the Events of the desired types.
	// This prevents the called from needing to implement the if condition.
	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		template<typename T>
			bool Dispatch(EventFn<T> func)
			{
				if (m_Event.GetEventType() == T::GetStaticType())
				{
					m_Event.Handled = func(*(T*)&m_Event);
					return true;
				}
				return false;
			}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

}