#include "test.hpp"
#include "lib/testenvironment.hpp"
#include "lib/object.hpp"


class BasicTestInstance : public TestInstance {
	std::vector<World::Object*> obs;
public:
    
	BasicTestInstance(TestEnvironment * env, float x, float y){
		obs.push_back(new World::Object(env));
		obs.back()->init(E_SPHERE, Vec4(1,0,0,0),MassProperties(2,0),Transform(Vec3(x,rand() % 10,y),Vec4(0,0,0,1)));
        for(int i = 0; i < 20; i++){
             obs.push_back(new World::Object(env));
            obs.back()->init(E_SPHERE, Vec4(1,0,0,0),MassProperties(4,0),Transform(Vec3(x,i*2.1f,y+rand() % 10),Vec4(0,0,0,1)));
        }
       
	}
    ~BasicTestInstance(){
    	for_each(obs.begin(),obs.end(),[](World::Object * obj){
    		delete obj;
    	});
    }
    virtual void update(){
        for_each(obs.begin(),obs.end(),[](World::Object * obj){
            obj->sync();
        });
    }
};

TestInstance * BasicTestFactory::instance(TestEnvironment* env, float x, float y){
    return new BasicTestInstance(env,x,y);
}
BasicTestFactory::BasicTestFactory(){
    TestFactory::addFactory(this);
}
BasicTestFactory _btf;//statically initialize and add this test.

