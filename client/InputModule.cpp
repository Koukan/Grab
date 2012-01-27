#include <map>
#include <SFML/Graphics.hpp>
#include <cstring>
#include "RendererManager.hpp"
#include "Game.hpp"
#include "GameStateManager.hpp"
#include "CommandDispatcher.hpp"
#include "InputModule.hpp"

InputModule::InputModule() : Module("InputModule", 20)
{
	#if (SFML_VERSION_MAJOR != 2)
	_dict[sf::Key::A] = Keyboard::A;
	_dict[sf::Key::B] = Keyboard::B;
	_dict[sf::Key::C] = Keyboard::C;
	_dict[sf::Key::D] = Keyboard::D;
	_dict[sf::Key::E] = Keyboard::E;
	_dict[sf::Key::F] = Keyboard::F;
	_dict[sf::Key::G] = Keyboard::G;
	_dict[sf::Key::H] = Keyboard::H;
	_dict[sf::Key::I] = Keyboard::I;
	_dict[sf::Key::J] = Keyboard::J;
	_dict[sf::Key::K] = Keyboard::K;
	_dict[sf::Key::L] = Keyboard::L;
	_dict[sf::Key::M] = Keyboard::M;
	_dict[sf::Key::N] = Keyboard::N;
	_dict[sf::Key::O] = Keyboard::O;
	_dict[sf::Key::P] = Keyboard::P;
	_dict[sf::Key::Q] = Keyboard::Q;
	_dict[sf::Key::R] = Keyboard::R;
	_dict[sf::Key::S] = Keyboard::S;
	_dict[sf::Key::T] = Keyboard::T;
	_dict[sf::Key::U] = Keyboard::U;
	_dict[sf::Key::V] = Keyboard::V;
	_dict[sf::Key::W] = Keyboard::W;
	_dict[sf::Key::X] = Keyboard::X;
	_dict[sf::Key::Y] = Keyboard::Y;
	_dict[sf::Key::Z] = Keyboard::Z;
	_dict[sf::Key::Num0] = Keyboard::Num0;
	_dict[sf::Key::Num1] = Keyboard::Num1;
	_dict[sf::Key::Num2] = Keyboard::Num2;
	_dict[sf::Key::Num3] = Keyboard::Num3;
	_dict[sf::Key::Num4] = Keyboard::Num4;
	_dict[sf::Key::Num5] = Keyboard::Num5;
	_dict[sf::Key::Num6] = Keyboard::Num6;
	_dict[sf::Key::Num7] = Keyboard::Num7;
	_dict[sf::Key::Num8] = Keyboard::Num8;
	_dict[sf::Key::Num9] = Keyboard::Num9;
	_dict[sf::Key::Escape] = Keyboard::Escape;
    _dict[sf::Key::LControl] = Keyboard::LControl;
	_dict[sf::Key::LShift] = Keyboard::LShift;
	_dict[sf::Key::LAlt] = Keyboard::LAlt;
	_dict[sf::Key::LSystem] = Keyboard::LSystem;
	_dict[sf::Key::RControl] = Keyboard::RControl;
	_dict[sf::Key::RShift] = Keyboard::RShift;
	_dict[sf::Key::RAlt] = Keyboard::RAlt;
	_dict[sf::Key::RSystem] = Keyboard::RSystem;
	_dict[sf::Key::Menu] = Keyboard::Menu;
	_dict[sf::Key::LBracket] = Keyboard::LBracket;
	_dict[sf::Key::RBracket] = Keyboard::RBracket;
	_dict[sf::Key::SemiColon] = Keyboard::SemiColon;
	_dict[sf::Key::Comma] = Keyboard::Comma;
	_dict[sf::Key::Period] = Keyboard::Period;
	_dict[sf::Key::Quote] = Keyboard::Quote;
	_dict[sf::Key::Slash] = Keyboard::Slash;
	_dict[sf::Key::BackSlash] = Keyboard::BackSlash;
	_dict[sf::Key::Tilde] = Keyboard::Tilde;
	_dict[sf::Key::Equal] = Keyboard::Equal;
	_dict[sf::Key::Dash] = Keyboard::Dash;
	_dict[sf::Key::Space] = Keyboard::Space;
	_dict[sf::Key::Return] = Keyboard::Return;
	_dict[sf::Key::Back] = Keyboard::Back;
	_dict[sf::Key::Tab] = Keyboard::Tab;
	_dict[sf::Key::PageUp] = Keyboard::PageUp;
	_dict[sf::Key::PageDown] = Keyboard::PageDown;
	_dict[sf::Key::End] = Keyboard::End;
	_dict[sf::Key::Home] = Keyboard::Home;
	_dict[sf::Key::Insert] = Keyboard::Insert;
	_dict[sf::Key::Delete] = Keyboard::Delete;
	_dict[sf::Key::Add] = Keyboard::Add;
	_dict[sf::Key::Subtract] = Keyboard::Subtract;
	_dict[sf::Key::Multiply] = Keyboard::Multiply;
	_dict[sf::Key::Divide] = Keyboard::Divide;
	_dict[sf::Key::Left] = Keyboard::Left;
	_dict[sf::Key::Right] = Keyboard::Right;
	_dict[sf::Key::Up] = Keyboard::Up;
	_dict[sf::Key::Down] = Keyboard::Down;
	_dict[sf::Key::Numpad0] = Keyboard::Numpad0;
	_dict[sf::Key::Numpad1] = Keyboard::Numpad1;
	_dict[sf::Key::Numpad2] = Keyboard::Numpad2;
	_dict[sf::Key::Numpad3] = Keyboard::Numpad3;
	_dict[sf::Key::Numpad4] = Keyboard::Numpad4;
	_dict[sf::Key::Numpad5] = Keyboard::Numpad5;
	_dict[sf::Key::Numpad6] = Keyboard::Numpad6;
	_dict[sf::Key::Numpad7] = Keyboard::Numpad7;
	_dict[sf::Key::Numpad8] = Keyboard::Numpad8;
	_dict[sf::Key::Numpad9] = Keyboard::Numpad9;
	_dict[sf::Key::F1] = Keyboard::F1;
	_dict[sf::Key::F2] = Keyboard::F2;
	_dict[sf::Key::F3] = Keyboard::F3;
	_dict[sf::Key::F4] = Keyboard::F4;
	_dict[sf::Key::F5] = Keyboard::F5;
	_dict[sf::Key::F6] = Keyboard::F6;
	_dict[sf::Key::F7] = Keyboard::F7;
	_dict[sf::Key::F8] = Keyboard::F8;
	_dict[sf::Key::F9] = Keyboard::F9;
	_dict[sf::Key::F10] = Keyboard::F10;
	_dict[sf::Key::F11] = Keyboard::F11;
	_dict[sf::Key::F12] = Keyboard::F12;
	_dict[sf::Key::F13] = Keyboard::F13;
	_dict[sf::Key::F14] = Keyboard::F14;
	_dict[sf::Key::F15] = Keyboard::F15;
	_dict[sf::Key::Pause] = Keyboard::Pause;
	_dict[sf::Key::Count] = Keyboard::KeyCount;
#endif
}

InputModule::~InputModule()
{
}

void		InputModule::init()
{
}

void		InputModule::update(double)
{
 sf::Event  ev;

 sf::RenderWindow *ptr = RendererManager::get().getWindow();
 #if (SFML_VERSION_MAJOR == 2)
 while (ptr->PollEvent(ev))
 #else
 while (ptr->GetEvent(ev))
 #endif
 {
	InputCommand *tmp = new InputCommand();

	tmp->Type = static_cast<InputCommand::EventType>(ev.Type);
	::memcpy(&tmp->Size, &ev.Size, 12);
	if (tmp->Type == InputCommand::Closed)
	  Game::get().quit();
	#if (SFML_VERSION_MAJOR != 2)
	if ((tmp->Type == InputCommand::KeyPressed || tmp->Type == InputCommand::KeyReleased) && this->_dict.find(ev.Key.Code) != this->_dict.end())
	  tmp->Key.Code = this->_dict[ev.Key.Code];
	#endif
 	CommandDispatcher::get().pushCommand(*tmp);
 }
}

void        InputModule::destroy()
{
}
