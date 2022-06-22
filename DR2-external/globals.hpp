#pragma once
#include <memory>

#include "dr2_cheat.hpp"
#include "dr2_overlay.hpp"
#include "osmium/Memory/Process/process.hpp"
#include "osmium/Overlay/overlay.hpp"


namespace Globals
{
	inline std::unique_ptr< dr2_cheat > g_pCheat = std::make_unique< dr2_cheat >();

	inline std::unique_ptr< process > g_pProcess = std::make_unique< process >();

	inline std::unique_ptr< dr2_overlay > g_pOverlay = std::make_unique< dr2_overlay >();
}
