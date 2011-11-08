#include <SPK.h>
#include <SPK_GL.h>
#include <ClanLib/gui.h>
#include <GL/glu.h>
#include "RendererManager.hpp"
#include "Loading.hpp"
#include "Game.hpp"
#include "bulletmlparser-tinyxml.h"
#include "Bullet.hpp"

SPK::System* gl_system;
SPK::Model	*gl_model;
double			gl_time;

Loading::Loading() : GameState("Loading")
{
  //  AudioManager::get().load("intro", "resource/sound/06-multiplayer-mouse-mania.ogg");
  //AudioManager::get().play("intro", "test", "intro");

  //AudioManager::get().setVolume("intro", "test", 1.0f);
}

Loading::~Loading()
{}

void	Loading::escape(const CL_InputEvent &)
{
  Game::get().popState();
  Game::get().quit();
}

void	Loading::click(const CL_InputEvent &event)
{
}

void	Loading::update(double time)
{
	  using namespace SPK;
	  using namespace SPK::GL;
	  gl_system->update(time * 0.001);
	  gl_system->render();
	  gl_model->setParam(PARAM_RED,0.6f + 0.4f * sin(gl_time * 0.001));
	  gl_model->setParam(PARAM_BLUE,0.6f + 0.4f * sin(gl_time * 0.001 + 3.14 * 4 / 3));
	  gl_model->setParam(PARAM_GREEN,0.6f + 0.4f * sin(gl_time * 0.001 + 3.14  * 2 / 3));
	  gl_time += time;
}

void	Loading::slowTest(const CL_InputEvent &event)
{
  if (event.id == CL_MOUSE_WHEEL_DOWN)
  {
    double timeEffect = this->getTimeEffect() - 0.1;
    this->setTimeEffect("default", (timeEffect < 0) ? 0 : timeEffect);
  }
  else
    this->setTimeEffect("default", this->getTimeEffect() + 0.1);
}

void	Loading::buttonClick()
{
  std::cout << "clicked" << std::endl;
}

void	Loading::onStart()
{
  this->load("resource/intro.xml");
  this->addGroup("ship", 10);
  this->addGroup("shot", 5);
  this->addBulletResource("default", "bullet", "shot", "ship", "shot");
  this->addBulletResource("weak", "shot", "shot", "ship", "shot");
  this->addBulletResource("dummybit", "weapon", "bullet", "ship", "shot");
  this->addBulletResource("pillarbit", "weapon", "shot", "ship", "shot");
  _parser = new BulletMLParserTinyXML("resource/test.xml");
  _parser->build();
  _bullet = new BulletCommand(_parser, *this, "default", 512, 360);
  this->addGameObject(_bullet, "ship", 10);

  CL_PushButton *button1 = this->create<CL_PushButton>("button1");
  button1->set_geometry(CL_Rect(100, 200, 200, 320));
  this->getGUIComponent<CL_PushButton>("button1")->set_text("Okay!");
  button1->func_clicked() = CL_Callback_v0(this, &Loading::buttonClick);
  CL_LineEdit *lineedit =  this->create<CL_LineEdit>("lineedit");
  lineedit->set_geometry(CL_Rect(100, 100, 200, 120));

  this->registerInputCallback(CL_InputEvent::pressed, *this, &Loading::escape, CL_InputDevice::keyboard, CL_KEY_ESCAPE);
  this->registerInputCallback(CL_InputEvent::pressed, *this, &Loading::slowTest, CL_InputDevice::pointer, CL_MOUSE_WHEEL_UP);
  this->registerInputCallback(CL_InputEvent::pressed, *this, &Loading::slowTest, CL_InputDevice::pointer, CL_MOUSE_WHEEL_DOWN);
  this->registerInputCallback(CL_InputEvent::released, *this, &Loading::click, CL_InputDevice::pointer, CL_MOUSE_LEFT);

  this->addGroup("poly1", 12);
  this->addGroup("poly2", 11);

  using namespace SPK;
  using namespace SPK::GL;
  randomSeed = static_cast<unsigned int>(time(NULL));
  gl_model = Model::create
  (
  FLAG_RED | FLAG_GREEN | FLAG_BLUE | FLAG_ALPHA,
  FLAG_ALPHA
  );
  gl_model->setParam(PARAM_ALPHA,1.0f,0.0f);
  gl_model->setLifeTime(1.0f,5.0f);
  //glTranslatef(0.0f,0.0f,-1);
  // Creates the zone
  Sphere* source =Sphere::create();
  source->setRadius(0.05);
  // Creates the emitter
  SphericEmitter* emitter = SphericEmitter::create();
  emitter->setDirection (Vector3D(0, 1, 0));
  emitter->setAngles(0,6.28);
  emitter->setZone(source);
  emitter->setForce(1.0f, 1.0f);
  emitter->setTank(-1);
  emitter->setFlow(40000);
  GLPointRenderer* renderer = GLPointRenderer::create();
  renderer->setType(SPK::POINT_CIRCLE);
  GLPointRenderer::setPixelPerUnit(45.0f * 3.14159f / 180.f, 768);
  renderer->setSize(5.0f);
  renderer->setTextureBlending(GL_MODULATE);
  renderer->enableRenderingHint(DEPTH_WRITE,false);
  renderer->setBlending(BLENDING_ALPHA);
  SPK::Group* group = SPK::Group::create(gl_model,40000);
  group->addEmitter(emitter);
  group->setRenderer(renderer);
  group->setFriction(0.0f);
  /*emitter = SphericEmitter::create();
  emitter->setDirection (Vector3D(0, 1, 0));
  emitter->setAngles(0,1);
  emitter->setZone(source);
  emitter->setForce(0.4f, 0.4f);
  emitter->setTank(40000000);
  emitter->setFlow(500);
  group->addEmitter(emitter);*/
  gl_system = System::create();
  gl_system->addGroup(group);
  gl_system->getGroup(0)->getEmitter(0)->getZone()->setPosition(Vector3D(0.5,0.5, 0));
}
