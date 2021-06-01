#include "hlpch.h"
#include "Input.h"

namespace Heirloom
{
	Event<KeyPressedEventArgs> Input::KeyPressedEvent                   = Event<KeyPressedEventArgs>();
	Event<KeyReleasedEventArgs> Input::KeyReleasedEvent                 = Event<KeyReleasedEventArgs>();
	Event<KeyTypedEventArgs> Input::KeyTypedEvent                       = Event<KeyTypedEventArgs>();
	Event<MouseButtonPressedEventArgs> Input::MouseButtonPressedEvent   = Event<MouseButtonPressedEventArgs>();
	Event<MouseButtonReleasedEventArgs> Input::MouseButtonReleasedEvent = Event<MouseButtonReleasedEventArgs>();
	Event<MouseMovedEventArgs> Input::MouseMovedEvent                   = Event<MouseMovedEventArgs>();
	Event<MouseScrolledEventArgs> Input::MouseScrolledEvent             = Event<MouseScrolledEventArgs>();
}
