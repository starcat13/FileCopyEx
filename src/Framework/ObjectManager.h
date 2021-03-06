#ifndef __OBJECTMANAGER_H__
#define __OBJECTMANAGER_H__

#include "Payload.h"
#include "Node.h"

class ObjectManager
{
public:
	~ObjectManager();

	typedef Payload* createPayloadFunc();
	typedef Node* createNodeFunc();

	void regClass(const String& type, createPayloadFunc pf, createNodeFunc nf);
	Node* create(const String& type, const String& name, Node* parent);
	
private:
	class createFuncs {
	public:
		createPayloadFunc *pf;
		createNodeFunc *nf;

		createFuncs() {};
		createFuncs(createPayloadFunc *_pf, createNodeFunc *_nf): pf(_pf), nf(_nf) {};
	};

	std::map<String, createFuncs> classes;
};

extern ObjectManager *objectManager;

#endif // __OBJECTMANAGER_H__