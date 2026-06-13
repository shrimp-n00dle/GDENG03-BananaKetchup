#pragma once
#include <stdexcept>
#include <memory>

#define dx3d_disable_copy_and_move(Class)     \
protected:\
    Class(const Class&) = delete;        \
    Class& operator=(const Class&) = delete; \
    Class(Class&&) = delete;             \
    Class& operator=(Class&&) = delete;

//CATSUP 
namespace catsup
{
	class Spawner;
	using SpawnerPtr = std::shared_ptr<Spawner>;
}

namespace dx3d
{
	class Base;
	class Window;
	class Game;
	class GraphicsEngine;
	class RenderSystem;
	class Logger;
	class SwapChain;
	class Display;
	class DeviceContext;
	class ShaderBinary;
	class GraphicsPipelineState;
	class VertexBuffer;
	class VertexShaderSignature;
	class ConstantBuffer;

	using i32 = int;
	using ui32 = unsigned int;
	using f32 = float;
	using d64 = double;

	using SwapChainPtr = std::shared_ptr<SwapChain>;
	using DeviceContextPtr = std::shared_ptr<DeviceContext>;
	using ShaderBinaryPtr = std::shared_ptr<ShaderBinary>;
	using GraphicsPipelineStatePtr = std::shared_ptr<GraphicsPipelineState>;
	using VertexBufferPtr = std::shared_ptr<VertexBuffer>;
	using VertexShaderSignaturePtr = std::shared_ptr<VertexShaderSignature>;
	template <typename T> using RefPtr = std::shared_ptr<T>;
	template <typename T> using UniquePtr = std::unique_ptr<T>;
}
