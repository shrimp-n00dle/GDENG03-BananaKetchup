#include <DX3D/Core/Base.h>
using namespace dx3d;

dx3d::Base::Base(const BaseDesc& desc): m_logger(desc.logger)
{
}

dx3d::Base::~Base()
{
}

dx3d::Logger& dx3d::Base::getLogger() noexcept
{
	// TODO: insert return statement here
	return m_logger;
}
