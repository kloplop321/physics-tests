#pragma once
#include <vector>
#include "vec.hpp"
#include "enums.hpp"
#include "mesh.hpp"
#include "forward.hpp"

namespace Physical {
	class Entity {
	private:
		Entity_Types _type;
		size_t _body_index;
		::std::vector<size_t> _shape_index;
		World::Earth * _world;
		bool _static;
		size_t createShape(const Entity_Types type, const Mesh & m);
		size_t createShape(const Entity_Types type, const Vec3 data, float constant = 1);
		void makeBody(const Transform t, const MassProperties mass);
	public:
		Entity(const Entity_Types type, const bool Static, World::Earth *);
		virtual ~Entity();
		void init(const Mesh & m, const MassProperties mass, const Transform t);
		void init(const Vec3 data, const MassProperties mass, const Transform t, const float constant = 1);
		void init(const ShapeList & list, const MassProperties mass, const Transform t);
		
		const Vec3 getPosition() const;
		const Vec4 getQuatOrientation() const;
		const Vec3 getEulerOrientation() const;
		const Transform getTransform() const;
		void setPosition(const Vec3 vec);
		void setOrientation(const Vec4 vec);
		void setOrientation(const Vec3 vec);
		void setTransform(const Transform t);
		void setVelocity(const Vec3 vec);
		void setAngularVelocity(const Vec3 vec);

		inline const Entity_Types type() const {return _type;}
	};
};