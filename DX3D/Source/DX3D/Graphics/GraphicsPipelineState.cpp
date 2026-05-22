#include <DX3D/Graphics/GraphicsPipelineState.h>
#include <DX3D/Graphics/ShaderBinary.h>
#include <iostream>

dx3d::GraphicsPipelineState::GraphicsPipelineState(const GraphicsPipelineStateDesc& desc, const GraphicsResourceDesc& gDesc) :
	GraphicsResource(gDesc)
{
	if (desc.vs.getType() != ShaderType::VertexShader)
	{
		std::cout << "THE 'VS' MEMBER IS NOT A VALID VERTEX SHADER BINARY";
		//DX3DLogThrowInvalidArg("THE 'VS' MEMBER IS NOT A VALID VERTEX SHADER BINARY");
	}
	if (desc.ps.getType() != ShaderType::PixelShader)
	{
		std::cout << "THE 'PS' MEMBER IS NOT A VALID PIXEL SHADER BINARY"; 
		//DX3DLogThrowInvalidArg("THE 'PS' MEMBER IS NOT A VALID PIXEL SHADER BINARY");
	}

	auto vs = desc.vs.getData();
	auto ps = desc.ps.getData();

	DX3DGraphicsLogErrorAndThrow(m_device.CreateVertexShader(vs.data,vs.dataSize,nullptr,&m_vs),
		"CreateVertexShader() failed, from GraphicsPipelineState.cpp");

	DX3DGraphicsLogErrorAndThrow(m_device.CreatePixelShader(ps.data, ps.dataSize, nullptr, &m_ps),
		"CreatePixelShader() failed, from GraphicsPipelineState.cpp");
}

