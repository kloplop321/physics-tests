#include "object.hpp"
#include "pentity.hpp"
#include "gentity.hpp"
#include "math.hpp"
#include "testenvironment.hpp"
#include <iostream>
namespace World {
	class ObjectContents {
	public:
		Entity_Types _type;
		Graphical::Entity * _g;
		Physical::Entity * _p;
		World::Earth * _earth;
		Graphical::Engine * _engine;
		bool _static;
		ObjectContents():
		_g(0), _p(0), _static(false) {
		}
		~ObjectContents(){
			if(_p) delete _p;
			if(_g) delete _g;
		}
	};
	Object::Object(TestEnvironment * env){
		_contents = new ObjectContents();
        {
            _contents->_earth = env->getPhysics();
            _contents->_engine = env->getGraphics();
            _contents->_engine->manager();
        }
	}
	void Object::init(
		const Entity_Types type,
		const char * mesh,
		const MassProperties mass,
		const Transform t){
		_contents->_type = type;
		_contents->_g = new Graphical::Entity(_contents->_engine);
		_contents->_g->init(type, mesh);
		_contents->_g->setOrientation(t.second);
		_contents->_g->setPosition(t.first);
		_contents->_p = new Physical::Entity(type, _contents->_static, _contents->_earth);
		_contents->_p->init(_contents->_g->getMesh(), mass, t);
	}
	void Object::init(
		const Entity_Types type,
		const Vec4 data,
		const MassProperties mass,
		const Transform t){
		_contents->_type = type;
		_contents->_g = new Graphical::Entity(_contents->_engine);
		_contents->_g->init(type, Math::Vec4ToVec3(data));
		_contents->_g->setOrientation(t.second);
		_contents->_g->setPosition(t.first);
		_contents->_p = new Physical::Entity(type, _contents->_static, _contents->_earth);
		_contents->_p->init(Math::Vec4ToVec3(data), mass, t, Math::VecLast(data));

	}
	void Object::init(
		ShapeList & list,
		const MassProperties mass,
        const Transform t){
		_contents->_type = E_COMPOUND;
		_contents->_g = new Graphical::Entity(_contents->_engine);
		_contents->_g->init(list);
		_contents->_g->setOrientation(t.second);
		_contents->_g->setPosition(t.first);
		_contents->_p = new Physical::Entity(_contents->_type, _contents->_static, _contents->_earth);
		_contents->_p->init(list, mass, t);
	}
	Object::~Object(){
		delete _contents;
	}
	
	const Vec3 Object::getPosition() const{
		if(_contents->_p){
			return _contents->_p->getPosition();
		}
		if(_contents->_g){
			return _contents->_g->getPosition();
		}
		Vec3 v;
		return v;
	}
	const Vec4 Object::getQuatOrientation() const{
		if(_contents->_p){
			return _contents->_p->getQuatOrientation();
		}
		if(_contents->_g){
			return _contents->_g->getQuatOrientation();
		}
		Vec4 v;
		return v;
	}
	const Vec3 Object::getEulerOrientation() const{
		if(_contents->_p){
			return _contents->_p->getEulerOrientation();
		}
		if(_contents->_g){
			return _contents->_g->getEulerOrientation();
		}
		Vec3 v;
		return v;
	}
	void Object::setPosition(const Vec3 vec){
		if(_contents->_p){
			_contents->_p->setPosition(vec);
		}
		if(_contents->_g){
			_contents->_g->setPosition(vec);
		}
	}
	void Object::setOrientation(const Vec4 vec){
		if(_contents->_p){
			_contents->_p->setOrientation(vec);
		}
		if(_contents->_g){
			_contents->_g->setOrientation(vec);
		}
	}
	void Object::setOrientation(const Vec3 vec){
		if(_contents->_p){
			_contents->_p->setOrientation(vec);
		}
		if(_contents->_g){
			_contents->_g->setOrientation(vec);
		}
	}
	void Object::setStatic(bool s){
		_contents->_static = s;
	}

	void Object::sync(){
		_contents->_g->setPosition(_contents->_p->getPosition());
		_contents->_g->setOrientation(_contents->_p->getQuatOrientation());
	}

	void Object::hideGraphics(){
		if(_contents->_g){
			_contents->_g->hide();
		}
	}
	void Object::showGraphics(){
		if(_contents->_g){
			_contents->_g->show();
		}
	}

	void Object::setColor(const Vec4 color){
		if(_contents->_g){
			_contents->_g->color(color);
		}
	}
	const Entity_Types Object::type() const {
		return _contents->_type;
	}

	const Mesh Object::getMesh() const{
		static Mesh m;
		if(_contents->_g){
			return _contents->_g->getMesh();
		}
		return m;
	}
	void Object::setVelocity(const Vec3 vec){
		if(_contents->_p){
			_contents->_p->setVelocity(vec);
		}
	}
	void Object::setAngularVelocity(const Vec3 vec){
		if(_contents->_p){
			_contents->_p->setAngularVelocity(vec);
		}
	}
};