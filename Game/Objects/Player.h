#include <DX3D/All.h>
#include <DX3D/Command/Command.h>

class Player : public dx3d::GameObject
{
	dx3d_typeid(Player)
public:
	explicit Player(const dx3d::GameObjectDesc& desc);
	virtual ~Player() override;

	//Test
	void spawnCube();
	//Test
	int x = -2;
	int y = -2;

protected:
	virtual void onCreate();
	virtual void onUpdate(dx3d::f32 deltaTime);

private:
	GameObject* m_cam{};
};
