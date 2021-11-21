#ifndef WI_SHADERINTEROP_H
#define WI_SHADERINTEROP_H

#ifdef __cplusplus // not invoking shader compiler, but included in engine source

// Application-side types:

using matrix = XMMATRIX;
using float3x4 = XMFLOAT3X4;
using float4x4 = XMFLOAT4X4;
using float2 = XMFLOAT2;
using float3 = XMFLOAT3;
using float4 = XMFLOAT4;
using uint = uint32_t;
using uint2 = XMUINT2;
using uint3 = XMUINT3;
using uint4 = XMUINT4;
using int2 = XMINT2;
using int3 = XMINT3;
using int4 = XMINT4;

#define column_major
#define row_major

#define CB_GETBINDSLOT(name) __CBUFFERBINDSLOT__##name##__
#define CBUFFER(name, slot) static const int CB_GETBINDSLOT(name) = slot; struct alignas(16) name
#define CONSTANTBUFFER(name, type, slot)
#define PUSHCONSTANT(name, type)

#else

// Shader - side types:

#define CBUFFER(name, slot) cbuffer name : register(b ## slot)
#define CONSTANTBUFFER(name, type, slot) ConstantBuffer< type > name : register(b ## slot)

#ifdef SPIRV
#define PUSHCONSTANT(name, type) [[vk::push_constant]] type name;
#endif // SPIRV

#ifdef HLSL6
#define PUSHCONSTANT(name, type) ConstantBuffer<type> name : register(b999)
#endif // HLSL6

struct IndirectDrawArgsInstanced
{
	uint VertexCountPerInstance;
	uint InstanceCount;
	uint StartVertexLocation;
	uint StartInstanceLocation;
};
struct IndirectDrawArgsIndexedInstanced
{
	uint IndexCountPerInstance;
	uint InstanceCount;
	uint StartIndexLocation;
	int BaseVertexLocation;
	uint StartInstanceLocation;
};
struct IndirectDispatchArgs
{
	uint ThreadGroupCountX;
	uint ThreadGroupCountY;
	uint ThreadGroupCountZ;
};

#endif // __cplusplus


// Common buffers:
// These are usable by all shaders
#define CBSLOT_RENDERER_FRAME					0
#define CBSLOT_RENDERER_CAMERA					1

// On demand buffers:
// These are bound on demand and alive until another is bound at the same slot

#define CBSLOT_RENDERER_MISC					5
#define CBSLOT_RENDERER_FORWARD_LIGHTMASK		7
#define CBSLOT_RENDERER_VOLUMELIGHT				7
#define CBSLOT_RENDERER_VOXELIZER				7
#define CBSLOT_RENDERER_TRACED					7
#define CBSLOT_RENDERER_BVH						7
#define CBSLOT_RENDERER_CUBEMAPRENDER			8

#define CBSLOT_OTHER_EMITTEDPARTICLE			7
#define CBSLOT_OTHER_HAIRPARTICLE				7
#define CBSLOT_OTHER_FFTGENERATOR				7
#define CBSLOT_OTHER_OCEAN_SIMULATION_IMMUTABLE	7
#define CBSLOT_OTHER_OCEAN_SIMULATION_PERFRAME	8
#define CBSLOT_OTHER_OCEAN_RENDER				7
#define CBSLOT_OTHER_CLOUDGENERATOR				7
#define CBSLOT_OTHER_GPUSORTLIB					8


#endif // WI_SHADERINTEROP_H
