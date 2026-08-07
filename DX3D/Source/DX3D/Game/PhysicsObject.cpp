#include <DX3D/Game/PhysicsObject.h>

PhysicsObject::PhysicsObject(const dx3d::GameObjectDesc& desc) : dx3d::GameObject(desc)
{
	//Get physicsCommon and World
	PhysicsCommon* physicsCommon = m_system->getPhysicsCommon();
	PhysicsWorld* physicsWorld = m_system->getPhysicsWorld();

	//Rigid Body Initialization
	dx3d::Vec3 scale = this->getTransform().getScale();

	dx3d::Vec3 pos = this->getTransform().getPosition();
	Vector3 position(pos.x,pos.y,pos.z);
	Quaternion orientation = rp3d::Quaternion::identity();

	//Transform transform;
	//transform.setFromOpenGL(this->getTransform()->)
	Transform transform(position, orientation);

	BoxShape* boxShape = physicsCommon->createBoxShape(Vector3(scale.x/2, scale.y/2, scale.z/2));
	this->rigidBody = physicsWorld->createRigidBody(transform);
	this->rigidBody->addCollider(boxShape, transform);
	this->rigidBody->updateMassPropertiesFromColliders();
	this->rigidBody->setMass(this->mass);
	this->rigidBody->setType(BodyType::DYNAMIC);

	transform = this->rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	//this->getOwner()->setLocalMatrix(matrix);


}

PhysicsObject::~PhysicsObject()
{
}

RigidBody* PhysicsObject::getRigidBody()
{
	return rigidBody;
}

void PhysicsObject::onCreate()
{
	createOrGetComponent<dx3d::MeshComponent>();
}

void PhysicsObject::onUpdate(dx3d::f32 deltaTime)
{
	const Transform transform = this->rigidBody->getTransform();
	
}
