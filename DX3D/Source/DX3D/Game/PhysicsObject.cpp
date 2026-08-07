#include <DX3D/Game/PhysicsObject.h>

PhysicsObject::PhysicsObject(const dx3d::GameObjectDesc& desc) : dx3d::GameObject(desc)
{
	//Get physicsCommon and World
	
	PhysicsCommon& physicsCommon = desc.gameContext.physics.getPhysicsCommon();
	PhysicsWorld* physicsWorld = desc.gameContext.physics.getPhysicsWorld();//m_system->getPhysicsWorld();

	//Rigid Body Initialization
	dx3d::Vec3 scale = this->getTransform().getScale();

	dx3d::Vec3 pos = this->getTransform().getPosition();
	Vector3 position(pos.x,pos.y,pos.z);
	Quaternion orientation = Quaternion::identity();

	//Transform transform;
	//transform.setFromOpenGL(this->getTransform()->)
	Transform transform( Vector3(getTransform().getPosition().x, 
								getTransform().getPosition().y,
								getTransform().getPosition().z)
								, 
						orientation);


	BoxShape* boxShape = physicsCommon.createBoxShape(Vector3(scale.x/2, scale.y/2, scale.z/2));
	this->rigidBody = physicsWorld->createRigidBody(transform);
	this->rigidBody->addCollider(boxShape, transform);
	this->rigidBody->updateMassPropertiesFromColliders();
	this->rigidBody->setMass(this->mass);
	this->rigidBody->setType(BodyType::DYNAMIC);

	transform = this->rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);


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
	std::cout << "P6!!" << std::endl;
	//Get Transform
	Transform transform = this->rigidBody->getTransform();

	//Position Updated
	Vector3 pos = transform.getPosition();
	Vector3 position(pos.x, pos.y, pos.z);
	this->getTransform().setPosition({position.x, position.y,position.z});

	//Rotation
	Quaternion orientation = transform.getOrientation();


	// Convert to degrees if your TransformComponent expects degrees
	dx3d::Vec3 finalRot(
		orientation.x * (180.0f / 3.14),
		orientation.y * (180.0f / 3.14),
		orientation.z * (180.0f / 3.14)
	);

	this->getTransform().setRotation(finalRot);
	
}
