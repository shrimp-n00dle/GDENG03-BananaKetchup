#include <DX3D/Graphics/GraphicsPipelineState.h>
#include <DX3D/Graphics/ShaderBinary.h>
#include <DX3D/Graphics/GraphicsPipelineLayout.h>


dx3d::GraphicsPipelineState::GraphicsPipelineState(const GraphicsPipelineStateDesc& desc, const GraphicsResourceDesc& gDesc) :
	GraphicsResource(gDesc)
{
	auto vs = desc.layout.getVSBinaryData();
	auto ps = desc.layout.getPSBinaryData();
	auto vsInputElements = desc.layout.getInputElementsData();

	DX3DGraphicsLogErrorAndThrow(
		m_device.CreateInputLayout(
			static_cast<const D3D11_INPUT_ELEMENT_DESC*>(vsInputElements.data), 
			static_cast<ui32>(vsInputElements.dataSize), 
			vs.data, 
			vs.dataSize,
			&m_layout),
		"CreateInputLayout() failed, from GPS.cpp"
	);


	DX3DGraphicsLogErrorAndThrow(m_device.CreateVertexShader(vs.data,vs.dataSize,nullptr,&m_vs),
		"CreateVertexShader() failed, from GraphicsPipelineState.cpp");

	DX3DGraphicsLogErrorAndThrow(m_device.CreatePixelShader(ps.data, ps.dataSize, nullptr, &m_ps),
		"CreatePixelShader() failed, from GraphicsPipelineState.cpp");
}

