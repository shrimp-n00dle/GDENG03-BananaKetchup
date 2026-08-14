#include <DX3D/Game/PhysicsObject.h>

PhysicsObject::PhysicsObject(const dx3d::GameObjectDesc& desc) : dx3d::GameObject(desc), physicsCommon(desc.gameContext.physics.getPhysicsCommon())
{
	//Get physicsCommon and World

	physicsWorld = desc.gameContext.physics.getPhysicsWorld();

}

void PhysicsObject::initializePhysicsObject(bool isStatic)
{
	//Rigid Body Initialization
	dx3d::Vec3 scale = this->getTransform().getScale();

	dx3d::Vec3 pos = this->getTransform().getPosition();
	std::cout << "POSITION IS: " << this->getTransform().getPosition().y << std::endl;
	Vector3 position(pos.x, pos.y, pos.z);
	Quaternion orientation = Quaternion::identity();

	Transform transform(Vector3(this->getTransform().getPosition().x,
		this->getTransform().getPosition().y,
		this->getTransform().getPosition().z)
		,
		orientation);


	BoxShape* boxShape = physicsCommon.createBoxShape(Vector3(scale.x/6, scale.y/6, scale.z/6));
	this->rigidBody = physicsWorld->createRigidBody(transform);
	this->rigidBody->addCollider(boxShape, Transform::identity());
	this->rigidBody->updateMassPropertiesFromColliders();
	this->rigidBody->setMass(this->mass);

	if (isStatic)
	{
		this->rigidBody->setType(BodyType::STATIC);
	} else this->rigidBody->setType(BodyType::DYNAMIC);

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

void PhysicsObject::isObjStatic(bool v)
{
	//If it is static
	if (v == true)
	{
		this->rigidBody->setType(BodyType::STATIC);
	}
}

void PhysicsObject::onCreate()
{
	createOrGetComponent<dx3d::MeshComponent>();
}

void PhysicsObject::onUpdate(dx3d::f32 deltaTime)
{
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
