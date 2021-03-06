#include <map>
#include "nworld.hpp"

class NullWorldFactory : public World::EarthFactory {
public:
    virtual World::Earth * instantiate() {
        return new NullWorld();
    }
    NullWorldFactory(){
        World::EarthFactory::addEarth(this);
    }
    virtual const char * getName(){
    	return "Null World";
    }
};
static NullWorldFactory nwf;

class NullContainer {
public:
	Transform trans;
	NullContainer(){}
	NullContainer(const Transform t):trans(t){}
};

class NullWorldContents {
public:
	::std::map<size_t, NullContainer> bodies;
	size_t newid;
	NullWorldContents():newid(0){}
};

NullWorld::NullWorld(){
	_contents = new NullWorldContents();
}
NullWorld::~NullWorld(){
	delete _contents;
}
void NullWorld::tick(float delta){
	//Null world takes no action
}
size_t NullWorld::addSphere(const float radius){
	return _contents->newid++;
}
size_t NullWorld::addBox(const Vec3 & dimensions){
	return _contents->newid++;
}
size_t NullWorld::addPlane(const Vec3 & equation, const float constant){
	return _contents->newid++;
}
size_t NullWorld::addMesh(const Mesh & mesh){
	return _contents->newid++;
}
size_t NullWorld::addCapsule(const float length, const float radius){
	return _contents->newid++;
}
size_t NullWorld::compoundShapes(::std::vector< ::std::pair<size_t, Transform> > list){
	return _contents->newid++;
}
size_t NullWorld::makeRigidBody(const size_t index, const MassProperties & mass, const Transform & trans){
	size_t b_index = _contents->newid++;
	_contents->bodies[b_index] = NullContainer(trans);
	return b_index;
}
size_t NullWorld::makeStaticBody(const size_t index, const Transform & trans){
	size_t b_index = _contents->newid++;
	_contents->bodies[b_index] = NullContainer(trans);
	return b_index;
}

size_t NullWorld::addPoint2Point(size_t first, size_t second, const Vec3 firstAxis, const Vec3 secondAxis){
	return _contents->newid++;
}

void NullWorld::removeConstraint(size_t index){
	//Null world
}
void NullWorld::removeShape(size_t shape){
	//Null World doesn't give back shape information
}
void NullWorld::removeBody(size_t body){
	_contents->bodies.erase(body);
}

void NullWorld::transformBody(const size_t index, const Transform & trans){
	_contents->bodies[index].trans = trans;
}
const Transform NullWorld::getTransformation(const size_t index){
	return _contents->bodies[index].trans;
}
::std::vector<size_t> NullWorld::getBodies(){
	::std::vector<size_t> bodies;
	bodies.reserve(_contents->bodies.size());
	for_each(_contents->bodies.begin(), _contents->bodies.end(), [&](std::pair<const size_t, NullContainer> p){
		bodies.push_back(p.first);
	});
	return bodies;
}
void NullWorld::setVelocity(const size_t index, const Vec3 velocity){
	 //Nothing
}
void NullWorld::setAngularVelocity(const size_t index, const Vec3 velocity){
	//Nothing
}