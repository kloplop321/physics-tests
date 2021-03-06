#include <utility>
#include "pentity.hpp"
#include "math.hpp"
#include "world.hpp"

namespace Physical {
	Entity::Entity(const Entity_Types type, const bool s, World::Earth * world){
		_world = world;
		_type = type;
		_body_index = 0;
		_static = s;
	}
	Entity::~Entity(){
		_world->removeBody(_body_index);
		for_each(_shape_index.begin(),_shape_index.end(),[this](size_t shape){
			_world->removeShape(shape);
		});
	}
	void Entity::init(const Mesh & m, const MassProperties mass, const Transform t){
		size_t shape = createShape(_type, m);
		_shape_index.push_back(shape);
		//create body
		makeBody(t, mass);
	}
	void Entity::init(const Vec3 data, const MassProperties mass, const Transform t, const float constant){
		size_t shape = createShape(_type, data, constant);
		_shape_index.push_back(shape);
		//create body
		makeBody(t, mass);
	}
	void Entity::init(const ShapeList & list, const MassProperties mass, const Transform t){
		std::vector< ::std::pair<size_t, Transform> > shapes;
		size_t compound;
		//Create the shapes
		for_each(list.begin(), list.end(), [&](const ShapeList::value_type & shape){
			switch(shape.first.type){
				case E_CAPSULE:
				case E_SPHERE:
				case E_BOX:
				case E_PLANE:
				{
					size_t s = createShape(
						shape.first.type,
						Math::Vec4ToVec3(shape.first.data),
						Math::VecLast(shape.first.data)
					);
					Transform t = shape.second;
					::std::pair<size_t, Transform> p(s,t);
					shapes.push_back(p);
				}
				break;
				case E_MESH:
				{
					size_t s = createShape(
						shape.first.type,
						shape.first.rawMesh
					);
					Transform t = shape.second;
					::std::pair<size_t, Transform> p(s,t);
					shapes.push_back(p);
				}
				break;
				default:
				{
					throw "Not valid shape type!";
				}
			}
		});
		//Got a list of shapes, make the compound shape
		compound = _world->compoundShapes(shapes);
		//Put it back on with the compound object first
		_shape_index.push_back(compound);
		for_each(shapes.begin(),shapes.end(),[&](decltype(shapes)::value_type s){
			_shape_index.push_back(s.first);
		});
		//create body
		makeBody(t, mass);
	}
	void Entity::makeBody(const Transform t, const MassProperties mass){
		size_t shape = _shape_index.front();
		if(_static){
			_body_index = _world->makeStaticBody(shape, t);
		}else{
			MassProperties m = mass;
			//??
			_body_index = _world->makeRigidBody(shape, m, t);
		}
	}
	size_t Entity::createShape(const Entity_Types type, const Mesh & m){
		size_t shape;
		switch(type){
			case E_MESH:
			{
				shape = _world->addMesh(m);
			}
			break;
			default:
			{
				throw "Type not compatible!";
			}
		}
		return shape;
	}
	size_t Entity::createShape(const Entity_Types type, const Vec3 data, float constant){
		size_t shape = 0;
		switch(type){
			case E_BOX:
			{
				shape = _world->addBox(data);
			}
			break;
			case E_SPHERE:
			{
				shape = _world->addSphere(
					::std::tr1::get<0>(data)
					);
			}
			break;
			case E_CAPSULE:
			{
				shape = _world->addCapsule(
					::std::tr1::get<0>(data),
					::std::tr1::get<1>(data)
					);
			}
			break;
			case E_PLANE:
			{
				shape = _world->addPlane(
					data,
					constant
					);
			}
			default:
			{
				throw "Type not compatible!";
			}
		}
		return shape;
	}

	const Vec3 Entity::getPosition() const{
		Transform t = _world->getTransformation(_body_index);
		return t.first;
	}
	const Vec4 Entity::getQuatOrientation() const{
		Transform t = _world->getTransformation(_body_index);
		return t.second;
	}
	const Vec3 Entity::getEulerOrientation() const{
		Transform t = _world->getTransformation(_body_index);
		return Math::QuaternionToEuler(t.second);
	}
	const Transform Entity::getTransform() const {
		Transform t;
		return _world->getTransformation(_body_index);
	}
	void Entity::setPosition(const Vec3 vec){
		Transform t = _world->getTransformation(_body_index);
		t.first = vec;
		_world->transformBody(_body_index,t);
	}
	void Entity::setOrientation(const Vec4 vec){
		Transform t = _world->getTransformation(_body_index);
		t.second = vec;
		_world->transformBody(_body_index,t);
	}
	void Entity::setOrientation(const Vec3 vec){
		setOrientation(Math::EulerToQuaternion(vec));
	}
	void Entity::setVelocity(const Vec3 vec){
		_world->setVelocity(_body_index,vec);
	}
	void Entity::setAngularVelocity(const Vec3 vec){
		_world->setAngularVelocity(_body_index,vec);
	}
};