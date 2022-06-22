#include "ft_dbginfo.hpp"

#include "globals.hpp"
#include "offsets.hpp"
#include "player_interface.hpp"
#include "utils.hpp"

void ft_dbginfo::on_disable()
{
	if( this->m_bWeaponPatch )
	{
		// deadrising2.exe + 245395 - F3 0F 5C 44 24 0C
		Globals::g_pProcess->write_to_protected_memory< uint32_t >( Offsets::break_weapon_patch, 0x445C0FF3 );
		Globals::g_pProcess->write_to_protected_memory< uint16_t >( Offsets::break_weapon_patch + 4, 0x0C24 );
		this->m_bWeaponPatch = false;
	}
}

void ft_dbginfo::on_render()
{
	if( Offsets::player )
	{
		if( PlayerInterface::get_player_level() > 100000 )
			PlayerInterface::initialize();

		if( utils::is_key_pressed( VK_DOWN ) )
		{
			this->m_iCurrentOption = this->m_iCurrentOption < 13
			                         ? this->m_iCurrentOption + 1
			                         : this->m_iCurrentOption;

			Sleep( 150 );
		}


		if( utils::is_key_pressed( VK_UP ) )
		{
			this->m_iCurrentOption = this->m_iCurrentOption > 1
			                         ? this->m_iCurrentOption - 1
			                         : this->m_iCurrentOption;

			Sleep( 150 );
		}


		float player_health = float();

		if( utils::is_key_pressed( VK_LEFT ) )
			switch( this->m_iCurrentOption )
			{
				case 1:
					PlayerInterface::set_player_level( PlayerInterface::get_player_level() - 1 );
					break;
				case 2:
					PlayerInterface::set_player_health( PlayerInterface::get_player_health() - 10.f );
					break;
				case 3:
					PlayerInterface::set_player_money( PlayerInterface::get_player_money() - 1000 );
					break;
				case 4:
					PlayerInterface::set_player_game_total_rp( PlayerInterface::get_player_game_total_rp() - 1000 );
					break;
				case 5:
					PlayerInterface::set_player_kills( PlayerInterface::get_player_kills() - 100 );
					break;
				case 6:
					if( this->m_bMaxAttributes )
					{
						PlayerInterface::set_player_attr_attack( 1 );
						PlayerInterface::set_player_attr_life( 1 );
						PlayerInterface::set_player_attr_speed( 1 );
						PlayerInterface::set_player_attr_throw_distance( 1 );
						this->m_bMaxAttributes = false;
					}
					break;
				case 7:
					if( this->m_bWeaponPatch )
					{
						// deadrising2.exe + 245395 - F3 0F 5C 44 24 0C
						Globals::g_pProcess->write_to_protected_memory< uint32_t >(
							Offsets::break_weapon_patch,
							0x445C0FF3
						);
						Globals::g_pProcess->write_to_protected_memory< uint16_t >(
							Offsets::break_weapon_patch + 4,
							0x0C24
						);
						this->m_bWeaponPatch = false;
					}
					break;
				case 8:
					if( this->m_bZombieAttack )
					{
						Globals::g_pProcess->write< bool >( Offsets::zombie_attack, false );
						Globals::g_pProcess->write< bool >( Offsets::zombie_grapple, false );
						Globals::g_pProcess->write< bool >( Offsets::zombie_ignore_all, false );
						this->m_bZombieAttack = false;
					}
					break;
				case 9:
					if( this->m_bZombieFreeze )
					{
						Globals::g_pProcess->write< bool >( Offsets::zombie_freeze, false );
						this->m_bZombieFreeze = false;
					}
					break;
				case 10:
					if( this->m_bRevealNotebook )
					{
						Globals::g_pProcess->write< bool >( Offsets::notebook_reveal, false );
						this->m_bRevealNotebook = false;
					}
					break;
				case 11:
					if( this->m_bUnlockCards )
					{
						Globals::g_pProcess->write< bool >( Offsets::unlock_cards, false );
						this->m_bUnlockCards = false;
					}
					break;
				case 12:
					if( this->m_bFreezeTime )
					{
						Globals::g_pProcess->write< int32_t >( Offsets::time_step, 12 );
						this->m_bFreezeTime = false;
					}
					break;
				case 13:
					if( this->m_bTimeHook )
					{
						Globals::g_pProcess->destroy_hook_x86( Offsets::time_hook );
						this->m_bTimeHook = false;
					}
					break;
				default:
					break;
			}

		if( utils::is_key_pressed( VK_RIGHT ) )
			switch( this->m_iCurrentOption )
			{
				case 1:
					PlayerInterface::set_player_level( PlayerInterface::get_player_level() + 1 );
					break;
				case 2:
					player_health = PlayerInterface::get_player_health();
					if( player_health < 1200 )
						PlayerInterface::set_player_health( player_health + 10.f );
					break;
				case 3:
					PlayerInterface::set_player_money( PlayerInterface::get_player_money() + 1000 );
					break;
				case 4:
					PlayerInterface::set_player_game_total_rp( PlayerInterface::get_player_game_total_rp() + 1000 );
					break;
				case 5:
					PlayerInterface::set_player_kills( PlayerInterface::get_player_kills() + 100 );
					break;
				case 6:
					if( !this->m_bMaxAttributes )
					{
						PlayerInterface::set_player_attr_attack( 7 );
						PlayerInterface::set_player_attr_life( 12 );
						PlayerInterface::set_player_attr_speed( 3 );
						PlayerInterface::set_player_attr_throw_distance( 5 );
						PlayerInterface::set_player_attr_item_stock( 12 );
						this->m_bMaxAttributes = true;
					}
					break;
				case 7:
					if( !this->m_bWeaponPatch )
					{
						Globals::g_pProcess->nop_bytes( Offsets::break_weapon_patch, 6 );
						this->m_bWeaponPatch = true;
					}
					break;
				case 8:
					if( !this->m_bZombieAttack )
					{
						Globals::g_pProcess->write< bool >( Offsets::zombie_attack, true );
						Globals::g_pProcess->write< bool >( Offsets::zombie_grapple, true );
						Globals::g_pProcess->write< bool >( Offsets::zombie_ignore_all, true );
						this->m_bZombieAttack = true;
					}
					break;
				case 9:
					if( !this->m_bZombieFreeze )
					{
						Globals::g_pProcess->write< bool >( Offsets::zombie_freeze, true );
						this->m_bZombieFreeze = true;
					}
					break;
				case 10:
					if( !this->m_bRevealNotebook )
					{
						Globals::g_pProcess->write< bool >( Offsets::notebook_reveal, true );
						this->m_bRevealNotebook = true;
					}
					break;
				case 11:
					if( !this->m_bUnlockCards )
					{
						Globals::g_pProcess->write< bool >( Offsets::unlock_cards, true );
						this->m_bUnlockCards = true;
					}
					break;
				case 12:
					if( !this->m_bFreezeTime )
					{
						Globals::g_pProcess->write< int32_t >( Offsets::time_step, 0 );
						this->m_bFreezeTime = true;
					}
					break;
				case 13:
					if( !this->m_bTimeHook )
					{
						/*
						 C7 41 18 07 00 00 00 mov [ecx+18],00000007
						 C7 41 1C 1E 00 00 00 mov [ecx+1C],0000001E
						 C7 41 20 00 00 00 00 mov [ecx+20],00000000
						 */
						Globals::g_pProcess->create_hook_x86(
							Offsets::time_hook,
							5,
							{
								0xC7, 0x41, 0x18, 0x07, 0x00, 0x00, 0x00,
								0xC7, 0x41, 0x1C, 0x1E, 0x00, 0x00, 0x00,
								0xC7, 0x41, 0x20, 0x00, 0x00, 0x00, 0x00
							}
						);
						this->m_bTimeHook = true;
					}
					break;
				default:
					break;
			}

		const auto first_ptr = Globals::g_pProcess->read< std::uintptr_t >( Offsets::player );

		const auto second_ptr = Globals::g_pProcess->read< std::uintptr_t >( first_ptr + 0x8 );

		Globals::g_pOverlay->draw_filled_rect( 18, 290, 240, 380, 1, 1, 1 );

		Globals::g_pOverlay->draw_string(
			std::format( "ppPlayer: 0x{:08X}", Offsets::player ),
			20,
			300,
			255,
			0,
			0
		);
		Globals::g_pOverlay->draw_string( std::format( "pPlayer: 0x{:08X}", first_ptr ), 20, 330, 255, 0, 0 );
		Globals::g_pOverlay->draw_string( std::format( "Player: 0x{:08X}", second_ptr ), 20, 360, 255, 0, 0 );

		const auto level = PlayerInterface::get_player_level();
		const auto health = PlayerInterface::get_player_health();
		const auto money = PlayerInterface::get_player_money();
		const auto total_rp = PlayerInterface::get_player_total_rp();
		const auto kills = PlayerInterface::get_player_kills();

		Globals::g_pOverlay->draw_string(
			std::format( "Level: {:4}", level ),
			20,
			400,
			255,
			0,
			this->m_iCurrentOption == 1 ? 255 : 0
		);
		Globals::g_pOverlay->draw_string(
			std::format( "Health: {:.2f}", health ),
			20,
			420,
			255,
			0,
			this->m_iCurrentOption == 2 ? 255 : 0
		);
		Globals::g_pOverlay->draw_string(
			std::format( "Money: {:8}", money ),
			20,
			440,
			255,
			0,
			this->m_iCurrentOption == 3 ? 255 : 0
		);
		Globals::g_pOverlay->draw_string(
			std::format( "Total RP: {:8}", total_rp ),
			20,
			460,
			255,
			0,
			this->m_iCurrentOption == 4 ? 255 : 0
		);
		Globals::g_pOverlay->draw_string(
			std::format( "Kills: {:5}", kills ),
			20,
			480,
			255,
			0,
			this->m_iCurrentOption == 5 ? 255 : 0
		);
		Globals::g_pOverlay->draw_string(
			std::format( "Max Attributes: {}", this->m_bMaxAttributes ? "YES" : "NO" ),
			20,
			500,
			255,
			0,
			this->m_iCurrentOption == 6 ? 255 : 0
		);
		Globals::g_pOverlay->draw_string(
			std::format( "Unbreakable Weapons: {}", this->m_bWeaponPatch ? "YES" : "NO" ),
			20,
			520,
			255,
			0,
			this->m_iCurrentOption == 7 ? 255 : 0
		);
		Globals::g_pOverlay->draw_string(
			std::format( "Harmless Zombies: {}", this->m_bZombieAttack ? "YES" : "NO" ),
			20,
			540,
			255,
			0,
			this->m_iCurrentOption == 8 ? 255 : 0
		);
		Globals::g_pOverlay->draw_string(
			std::format( "Freeze Zombies: {}", this->m_bZombieFreeze ? "YES" : "NO" ),
			20,
			560,
			255,
			0,
			this->m_iCurrentOption == 9 ? 255 : 0
		);
		Globals::g_pOverlay->draw_string(
			std::format( "Reveal Notebook: {}", this->m_bRevealNotebook ? "YES" : "NO" ),
			20,
			580,
			255,
			0,
			this->m_iCurrentOption == 10 ? 255 : 0
		);
		Globals::g_pOverlay->draw_string(
			std::format( "Unlock All Combo Cards: {}", this->m_bUnlockCards ? "YES" : "NO" ),
			20,
			600,
			255,
			0,
			this->m_iCurrentOption == 11 ? 255 : 0
		);
		Globals::g_pOverlay->draw_string(
			std::format( "Freeze Time: {}", this->m_bFreezeTime ? "YES" : "NO" ),
			20,
			620,
			255,
			0,
			this->m_iCurrentOption == 12 ? 255 : 0
		);
		Globals::g_pOverlay->draw_string(
			std::format( "Always 7:30 AM: {}", this->m_bTimeHook ? "YES" : "NO" ),
			20,
			640,
			255,
			0,
			this->m_iCurrentOption == 13 ? 255 : 0
		);
	}
}
