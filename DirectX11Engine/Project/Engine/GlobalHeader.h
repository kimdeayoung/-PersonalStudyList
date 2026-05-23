#pragma once

#include <d3d11.h> // DX11 기본 Header
#include <d3dcompiler.h> // Shader 컴파일시 필요한 함수 Header
#include <DirectXMath.h>
#include <DirectXPackedVector.h>

#include <DirectXTex/DirectXTex.h>

#include "SimpleMath.h"

#include <wrl.h>
using namespace Microsoft::WRL;

// Header들만 include하고 실제 구현은 존재하지 않기때문에
// pragma comment를 사용하여 명시적인 라이브러리 링킹
#pragma comment(lib, "d3d11") 
#pragma comment(lib, "d3dcompiler")

#ifdef _DEBUG
#pragma comment(lib, "DirectXTex/DirectXTex_debug")
#else
#pragma comment(lib, "DirectXTex/DirectXTex")
#endif

using namespace DirectX::SimpleMath;

#include <vector>
#include <list>
#include <map>
#include <string>

#include "define.h"
#include "enum.h"
#include "struct.h"
#include "func.h"

#include "Singleton.h"

#include "ptr.h"