#include <DX3D/Graphics/ShaderBinary.h>
#include <DX3D/Graphics/GraphicsUtils.h>
#include <d3dcompiler.h>
#include <iostream>

dx3d::ShaderBinary::ShaderBinary(const ShaderCompileDesc& desc, const GraphicsResourceDesc& gDesc) : GraphicsResource(gDesc),
				m_type(desc.shaderType)
{
	if (!desc.shaderSourceName)
	{
		//std::cout << "No shader source name provided, ShaderBinary.cpp";
		DX3DLogThrowInvalidArg("No shader source name provided, ShaderBinary.cpp");
	}

	if (!desc.shaderSourceCode)
	{
		//std::cout << "No shader source code provided, ShaderBinary.cpp";
		DX3DLogThrowInvalidArg("No shader source code provided, ShaderBinary.cpp");
	}

	if (!desc.shaderSourceCodeSize)
	{
		//std::cout << "No shader source code SIZE provided, ShaderBinary.cpp";
		DX3DLogThrowInvalidArg("No shader source code SIZE provided, ShaderBinary.cpp");
	}

	if (!desc.shaderSourceEntryPoint)
	{
		//std::cout << "No shader source entry point provided, ShaderBinary.cpp";
		DX3DLogThrowInvalidArg("No shader source entry point provided, ShaderBinary.cpp");
	}


	UINT compileFlags{};

#ifdef _DEBUG
	compileFlags |= D3DCOMPILE_DEBUG;
#endif

	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob{};
	DX3DGraphicsCheckShaderCompile(
		D3DCompile(
			desc.shaderSourceCode,
			desc.shaderSourceCodeSize,
			desc.shaderSourceName,
			nullptr,
			nullptr,
			desc.shaderSourceEntryPoint,
			dx3d::GraphicsUtils::GetShaderModelTarget(desc.shaderType),
			compileFlags,
			0,
			&m_blob, 
			&errorBlob),
			errorBlob.Get()
		);
}

dx3d::ShaderBinaryData dx3d::ShaderBinary::getData() const noexcept
{
	return {
		m_blob->GetBufferPointer(),
		m_blob->GetBufferSize()
	};
}

dx3d::ShaderType dx3d::ShaderBinary::getType() const noexcept
{
	return m_type;
}
