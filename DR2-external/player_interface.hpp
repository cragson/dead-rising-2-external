#pragma once

#include "offsets.hpp"
#include "globals.hpp"

/*
class Player
{
public:
	char pad_0000[32]; //0x0000
	uint32_t m_iLevel; //0x0020
	uint32_t m_iTotalRP; //0x0024
	uint32_t m_iGameTotalRP; //0x0028
	float m_flHealth; //0x002C
	char pad_0030[8]; //0x0030
	uint32_t m_iKills; //0x0038
	char pad_003C[24]; //0x003C
	uint32_t m_iAttrAttack; //0x0054
	uint32_t m_iAttrSpeed; //0x0058
	uint32_t m_iAttrLife; //0x005C
	uint32_t m_iAttrItemStock; //0x0060
	uint32_t m_iAttrThrowDistance; //0x0064
	char pad_0068[8]; //0x0068
	uint32_t m_iMoney; //0x0070
}; //Size: 0x0074
 */

namespace PlayerInterface
{
	inline std::uintptr_t interface_ptr = std::uintptr_t();

	[[nodiscard]] inline std::uintptr_t get_interface_ptr()
	{
		const auto first_ptr = Globals::g_pProcess->read< std::uintptr_t >( Offsets::player );

		const auto second_ptr = Globals::g_pProcess->read< std::uintptr_t >( first_ptr + 0x8 );

		return second_ptr;
	}

	[[nodiscard]] inline bool initialize()
	{
		const auto ptr = get_interface_ptr();

		if( ptr )
		{
			interface_ptr = ptr;
			return true;
		}

		return false;
	}

	[[nodiscard]] inline uint32_t get_player_level()
	{
		return Globals::g_pProcess->read< uint32_t >( interface_ptr + 0x20 );
	}

	inline void set_player_level( const uint32_t level )
	{
		Globals::g_pProcess->write< uint32_t >( interface_ptr + 0x20, level );
	}

	[[nodiscard]] inline uint32_t get_player_total_rp()
	{
		return Globals::g_pProcess->read< uint32_t >( interface_ptr + 0x24 );
	}

	inline void set_player_total_rp( const uint32_t rp )
	{
		Globals::g_pProcess->write< uint32_t >( interface_ptr + 0x24, rp );
	}

	[[nodiscard]] inline uint32_t get_player_game_total_rp()
	{
		return Globals::g_pProcess->read< uint32_t >( interface_ptr + 0x28 );
	}

	inline void set_player_game_total_rp( const uint32_t rp )
	{
		Globals::g_pProcess->write< uint32_t >( interface_ptr + 0x28, rp );
	}

	[[nodiscard]] inline float get_player_health()
	{
		return Globals::g_pProcess->read< float >( interface_ptr + 0x2C );
	}

	inline void set_player_health( const float health )
	{
		Globals::g_pProcess->write< float >( interface_ptr + 0x2C, health );
	}

	[[nodiscard]] inline uint32_t get_player_kills()
	{
		return Globals::g_pProcess->read< uint32_t >( interface_ptr + 0x38 );
	}

	inline void set_player_kills( const uint32_t kills )
	{
		Globals::g_pProcess->write< uint32_t >( interface_ptr + 0x38, kills );
	}

	[[nodiscard]] inline uint32_t get_player_attr_attack()
	{
		return Globals::g_pProcess->read< uint32_t >( interface_ptr + 0x54 );
	}

	inline void set_player_attr_attack( const uint32_t attack )
	{
		Globals::g_pProcess->write< uint32_t >( interface_ptr + 0x54, attack );
	}

	[[nodiscard]] inline uint32_t get_player_attr_speed()
	{
		return Globals::g_pProcess->read< uint32_t >( interface_ptr + 0x58 );
	}

	inline void set_player_attr_speed( const uint32_t speed )
	{
		Globals::g_pProcess->write< uint32_t >( interface_ptr + 0x58, speed );
	}

	[[nodiscard]] inline uint32_t get_player_attr_life()
	{
		return Globals::g_pProcess->read< uint32_t >( interface_ptr + 0x5C );
	}

	inline void set_player_attr_life( const uint32_t life )
	{
		Globals::g_pProcess->write< uint32_t >( interface_ptr + 0x5C, life );
	}

	[[nodiscard]] inline uint32_t get_player_attr_item_stock()
	{
		return Globals::g_pProcess->read< uint32_t >( interface_ptr + 0x60 );
	}

	inline void set_player_attr_item_stock( const uint32_t item_stock )
	{
		Globals::g_pProcess->write< uint32_t >( interface_ptr + 0x60, item_stock );
	}

	[[nodiscard]] inline uint32_t get_player_attr_throw_distance()
	{
		return Globals::g_pProcess->read< uint32_t >( interface_ptr + 0x64 );
	}

	inline void set_player_attr_throw_distance( const uint32_t throw_dist )
	{
		Globals::g_pProcess->write< uint32_t >( interface_ptr + 0x64, throw_dist );
	}

	[[nodiscard]] inline uint32_t get_player_money()
	{
		return Globals::g_pProcess->read< uint32_t >( interface_ptr + 0x70 );
	}

	inline void set_player_money( const uint32_t money )
	{
		Globals::g_pProcess->write< uint32_t >( interface_ptr + 0x70, money );
	}
}
