#include <map>
#include <SFML/Graphics.hpp>
#include <cstring>
#include "RendererManager.hpp"
#include "Game.hpp"
#include "GameStateManager.hpp"
#include "CommandDispatcher.hpp"
#include "InputModule.hpp"

InputModule::InputModule() : Core::Module("InputModule", 20)
{
	#if (SFML_VERSION_MAJOR != 2)
	_dict[sf::Key::A] = Core::Keyboard::A;
	_dict[sf::Key::B] = Core::Keyboard::B;
	_dict[sf::Key::C] = Core::Keyboard::C;
	_dict[sf::Key::D] = Core::Keyboard::D;
	_dict[sf::Key::E] = Core::Keyboard::E;
	_dict[sf::Key::F] = Core::Keyboard::F;
	_dict[sf::Key::G] = Core::Keyboard::G;
	_dict[sf::Key::H] = Core::Keyboard::H;
	_dict[sf::Key::I] = Core::Keyboard::I;
	_dict[sf::Key::J] = Core::Keyboard::J;
	_dict[sf::Key::K] = Core::Keyboard::K;
	_dict[sf::Key::L] = Core::Keyboard::L;
	_dict[sf::Key::M] = Core::Keyboard::M;
	_dict[sf::Key::N] = Core::Keyboard::N;
	_dict[sf::Key::O] = Core::Keyboard::O;
	_dict[sf::Key::P] = Core::Keyboard::P;
	_dict[sf::Key::Q] = Core::Keyboard::Q;
	_dict[sf::Key::R] = Core::Keyboard::R;
	_dict[sf::Key::S] = Core::Keyboard::S;
	_dict[sf::Key::T] = Core::Keyboard::T;
	_dict[sf::Key::U] = Core::Keyboard::U;
	_dict[sf::Key::V] = Core::Keyboard::V;
	_dict[sf::Key::W] = Core::Keyboard::W;
	_dict[sf::Key::X] = Core::Keyboard::X;
	_dict[sf::Key::Y] = Core::Keyboard::Y;
	_dict[sf::Key::Z] = Core::Keyboard::Z;
	_dict[sf::Key::Num0] = Core::Keyboard::Num0;
	_dict[sf::Key::Num1] = Core::Keyboard::Num1;
	_dict[sf::Key::Num2] = Core::Keyboard::Num2;
	_dict[sf::Key::Num3] = Core::Keyboard::Num3;
	_dict[sf::Key::Num4] = Core::Keyboard::Num4;
	_dict[sf::Key::Num5] = Core::Keyboard::Num5;
	_dict[sf::Key::Num6] = Core::Keyboard::Num6;
	_dict[sf::Key::Num7] = Core::Keyboard::Num7;
	_dict[sf::Key::Num8] = Core::Keyboard::Num8;
	_dict[sf::Key::Num9] = Core::Keyboard::Num9;
	_dict[sf::Key::Escape] = Core::Keyboard::Escape;
    _dict[sf::Key::LControl] = Core::Keyboard::LControl;
	_dict[sf::Key::LShift] = Core::Keyboard::LShift;
	_dict[sf::Key::LAlt] = Core::Keyboard::LAlt;
	_dict[sf::Key::LSystem] = Core::Keyboard::LSystem;
	_dict[sf::Key::RControl] = Core::Keyboard::RControl;
	_dict[sf::Key::RShift] = Core::Keyboard::RShift;
	_dict[sf::Key::RAlt] = Core::Keyboard::RAlt;
	_dict[sf::Key::RSystem] = Core::Keyboard::RSystem;
	_dict[sf::Key::Menu] = Core::Keyboard::Menu;
	_dict[sf::Key::LBracket] = Core::Keyboard::LBracket;
	_dict[sf::Key::RBracket] = Core::Keyboard::RBracket;
	_dict[sf::Key::SemiColon] = Core::Keyboard::SemiColon;
	_dict[sf::Key::Comma] = Core::Keyboard::Comma;
	_dict[sf::Key::Period] = Core::Keyboard::Period;
	_dict[sf::Key::Quote] = Core::Keyboard::Quote;
	_dict[sf::Key::Slash] = Core::Keyboard::Slash;
	_dict[sf::Key::BackSlash] = Core::Keyboard::BackSlash;
	_dict[sf::Key::Tilde] = Core::Keyboard::Tilde;
	_dict[sf::Key::Equal] = Core::Keyboard::Equal;
	_dict[sf::Key::Dash] = Core::Keyboard::Dash;
	_dict[sf::Key::Space] = Core::Keyboard::Space;
	_dict[sf::Key::Return] = Core::Keyboard::Return;
	_dict[sf::Key::Back] = Core::Keyboard::Back;
	_dict[sf::Key::Tab] = Core::Keyboard::Tab;
	_dict[sf::Key::PageUp] = Core::Keyboard::PageUp;
	_dict[sf::Key::PageDown] = Core::Keyboard::PageDown;
	_dict[sf::Key::End] = Core::Keyboard::End;
	_dict[sf::Key::Home] = Core::Keyboard::Home;
	_dict[sf::Key::Insert] = Core::Keyboard::Insert;
	_dict[sf::Key::Delete] = Core::Keyboard::Delete;
	_dict[sf::Key::Add] = Core::Keyboard::Add;
	_dict[sf::Key::Subtract] = Core::Keyboard::Subtract;
	_dict[sf::Key::Multiply] = Core::Keyboard::Multiply;
	_dict[sf::Key::Divide] = Core::Keyboard::Divide;
	_dict[sf::Key::Left] = Core::Keyboard::Left;
	_dict[sf::Key::Right] = Core::Keyboard::Right;
	_dict[sf::Key::Up] = Core::Keyboard::Up;
	_dict[sf::Key::Down] = Core::Keyboard::Down;
	_dict[sf::Key::Numpad0] = Core::Keyboard::Numpad0;
	_dict[sf::Key::Numpad1] = Core::Keyboard::Numpad1;
	_dict[sf::Key::Numpad2] = Core::Keyboard::Numpad2;
	_dict[sf::Key::Numpad3] = Core::Keyboard::Numpad3;
	_dict[sf::Key::Numpad4] = Core::Keyboard::Numpad4;
	_dict[sf::Key::Numpad5] = Core::Keyboard::Numpad5;
	_dict[sf::Key::Numpad6] = Core::Keyboard::Numpad6;
	_dict[sf::Key::Numpad7] = Core::Keyboard::Numpad7;
	_dict[sf::Key::Numpad8] = Core::Keyboard::Numpad8;
	_dict[sf::Key::Numpad9] = Core::Keyboard::Numpad9;
	_dict[sf::Key::F1] = Core::Keyboard::F1;
	_dict[sf::Key::F2] = Core::Keyboard::F2;
	_dict[sf::Key::F3] = Core::Keyboard::F3;
	_dict[sf::Key::F4] = Core::Keyboard::F4;
	_dict[sf::Key::F5] = Core::Keyboard::F5;
	_dict[sf::Key::F6] = Core::Keyboard::F6;
	_dict[sf::Key::F7] = Core::Keyboard::F7;
	_dict[sf::Key::F8] = Core::Keyboard::F8;
	_dict[sf::Key::F9] = Core::Keyboard::F9;
	_dict[sf::Key::F10] = Core::Keyboard::F10;
	_dict[sf::Key::F11] = Core::Keyboard::F11;
	_dict[sf::Key::F12] = Core::Keyboard::F12;
	_dict[sf::Key::F13] = Core::Keyboard::F13;
	_dict[sf::Key::F14] = Core::Keyboard::F14;
	_dict[sf::Key::F15] = Core::Keyboard::F15;
	_dict[sf::Key::Pause] = Core::Keyboard::Pause;
	_dict[sf::Key::Count] = Core::Keyboard::KeyCount;
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
 while (ptr->pollEvent(ev))
 #else
 while (ptr->GetEvent(ev))
 #endif
 {
   Core::InputCommand *tmp = new Core::InputCommand();

	#if (SFML_VERSION_MAJOR == 2)
   tmp->Type = static_cast<Core::InputCommand::EventType>(ev.type);
	::memcpy(&tmp->Size, &ev.size, 12);
	#else
   tmp->Type = static_cast<Core::InputCommand::EventType>(ev.Type);
	::memcpy(&tmp->Size, &ev.Size, 12);
	#endif
   if (tmp->Type == Core::InputCommand::Closed)
	  Game::get().quit();
	#if (SFML_VERSION_MAJOR != 2)
   if ((tmp->Type == Core::InputCommand::KeyPressed || tmp->Type == Core::InputCommand::KeyReleased) && this->_dict.find(ev.Key.Code) != this->_dict.end())
	  tmp->Key.Code = this->_dict[ev.Key.Code];
	#endif
   Core::CommandDispatcher::get().pushCommand(*tmp);
 }
}

void        InputModule::destroy()
{
}
