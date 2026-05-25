#include <DX3D/Graphics/VertexShaderSignature.h>
#include <DX3D/Graphics/ShaderBinary.h>
#include <DX3D/Graphics/GraphicsUtils.h>
#include <d3dcompiler.h>
#include <ranges>


dx3d::VertexShaderSignature::VertexShaderSignature(const VertexShaderSignatureDesc& desc, 
	const GraphicsResourceDesc& gDesc) : GraphicsResource(gDesc), m_vsBinary(desc.vsBinary)
{

	if (!desc.vsBinary) DX3DLogThrowInvalidArg("No shader binary provided, VSSignautre.cpp");
	if (desc.vsBinary->getType() != ShaderType::VertexShader)
		DX3DLogThrowInvalidArg("Shader binary is not a vertex shader binary, VSSignature.cpp");

	auto vsData = m_vsBinary->getData();

	//Allow us to inspect various shader components
	DX3DGraphicsLogErrorAndThrow(
		D3DReflect(
		vsData.data,
		vsData.dataSize,
		IID_PPV_ARGS(&m_shaderReflection)),
		"D3DReflect() failed, from VSSignature.cpp"
	);

	D3D11_SHADER_DESC shaderDesc{};
	DX3DGraphicsLogErrorAndThrow (m_shaderReflection->GetDesc(&shaderDesc), 
		"ID3D11ShaderReflection::GetDesc failed, VSSignature.cpp");

	m_numElements =  shaderDesc.InputParameters;


	D3D11_SIGNATURE_PARAMETER_DESC params[D3D11_STANDARD_VERTEX_ELEMENT_COUNT]{};
	//range adaptor that generates a sequence of continuously incrementing values, lazily and on-demand
	for (auto i : std::views::iota(0u, m_numElements))
	{
		DX3DGraphicsLogErrorAndThrow(
			m_shaderReflection->GetInputParameterDesc(i, &params[i]),
			"ID3D11ShaderReflection::GetInputParamaterDesc failed, VSSignature.cpp"
		);
	}

	//constexpr D3D11_INPUT_ELEMENT_DESC elements[] =
	//{
	//	{"POSITION",0, DXGI_FORMAT_R32G32B32_FLOAT, 0,0,D3D11_INPUT_PER_VERTEX_DATA, 0},
	//	//Color Attribute
	//	{"COLOR",0, DXGI_FORMAT_R32G32B32A32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA, 0}
	//};


	for (auto i : std::views::iota(0u, m_numElements))
	{
		auto param = params[i];

		m_elements[i] =
		{
			param.SemanticName,
			param.SemanticIndex,
			GraphicsUtils::GetDXGIFormatFromMask(param.ComponentType, param.Mask),
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		};
	}


}

dx3d::BinaryData dx3d::VertexShaderSignature::getShaderBinaryData() const noexcept
{
	return m_vsBinary->getData();
}

dx3d::BinaryData dx3d::VertexShaderSignature::getInputElementsData() const noexcept
{
	return
	{
		m_elements,
		m_numElements
	};
}

