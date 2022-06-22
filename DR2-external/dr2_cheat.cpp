#include "dr2_cheat.hpp"

#include "ft_dbginfo.hpp"
#include "ft_watermark.hpp"
#include "globals.hpp"
#include "offsets.hpp"
#include "utils.hpp"

bool dr2_cheat::setup_features()
{
	auto mark = std::make_unique< ft_watermark >();
	mark->set_name( L"Watermark" );
	mark->set_print_status( false );
	mark->set_activation_delay( 420 );
	mark->enable_drawing();
	mark->set_status( true );
	mark->set_virtual_key_code( VK_F1 );

	this->m_features.push_back( std::move( mark ) );

	auto dbg = std::make_unique< ft_dbginfo >();
	dbg->set_name( L"Menu" );
	dbg->set_print_status( false );
	dbg->set_activation_delay( 420 );
	dbg->enable_drawing();
	dbg->set_status( false );
	dbg->set_virtual_key_code( VK_INSERT );

	this->m_features.push_back( std::move( dbg ) );

	return true;
}

bool dr2_cheat::setup_offsets()
{
	if( !Globals::g_pProcess->does_image_exist_in_map( L"deadrising2.exe" ) )
		return false;

	const auto dr2 = Globals::g_pProcess->get_image_ptr_by_name( L"deadrising2.exe" );

	const auto ppPlayer = dr2->find_pattern( L"A1 ? ? ? ? 8B 48 08 8B 51 20", false );

	if( !ppPlayer )
		return false;

	Offsets::player = dr2->deref_address< std::uintptr_t >( ppPlayer + 1 );

	const auto break_patch = dr2->find_pattern( L"04 F3 0F 5C 44 24 0C", false );

	if( !break_patch )
		return false;

	Offsets::break_weapon_patch = break_patch + 1;

	const auto zattack = dr2->find_pattern( L"A0 ? ? ? ? 88 46 58", false );

	if( !zattack )
		return false;

	Offsets::zombie_attack = dr2->deref_address< std::uintptr_t >( zattack + 1 );

	const auto zfreeze = dr2->find_pattern( L"C6 05 ? ? ? ? ? 83 86", false );

	if( !zfreeze )
		return false;

	Offsets::zombie_freeze = dr2->deref_address< std::uintptr_t >( zfreeze + 2 );

	const auto zgrapple = dr2->find_pattern( L"38 1D ? ? ? ? 57 8B F9 75 44", false );

	if( !zgrapple )
		return false;

	Offsets::zombie_grapple = dr2->deref_address< std::uintptr_t >( zgrapple + 2 );

	const auto nreveal = dr2->find_pattern( L"80 3D ? ? ? ? ? 75 6F 8B 4E 18", false );

	if( !nreveal )
		return false;

	Offsets::notebook_reveal = dr2->deref_address< std::uintptr_t >( nreveal + 2 );

	const auto zignore = dr2->find_pattern( L"8A 15 ? ? ? ? 5E", false );

	if( !zignore )
		return false;

	Offsets::zombie_ignore_all = dr2->deref_address< std::uintptr_t >( zignore + 2 );

	const auto unlockcards = dr2->find_pattern( L"38 1D ? ? ? ? 74 0A 8B 4E 0C", false );

	if( !unlockcards )
		return false;

	Offsets::unlock_cards = dr2->deref_address< std::uintptr_t >( unlockcards + 2 );

	const auto step = dr2->find_pattern( L"8B 0D ? ? ? ? 0F AF CF", false );

	if( !step )
		return false;

	Offsets::time_step = dr2->deref_address< std::uintptr_t >( step + 2 );

	const auto timehook = dr2->find_pattern( L"BE 3C 00 00 00 3B", false );

	if( !timehook )
		return false;

	Offsets::time_hook = timehook;


	return true;
}

void dr2_cheat::print_features()
{
	printf( "\n" );

	printf( "Feature-Name -> Feature-Hotkey\n" );

	for( const auto& feature : this->m_features )
		printf(
			"[>] %-25ws -> %s\n",
			feature->get_name().c_str(),
			utils::virtual_key_as_string( feature->get_virtual_key_code() ).c_str()
		);

	printf( "\n" );
}

void dr2_cheat::print_offsets()
{
	printf( "\n" );

	const auto msg = []( const std::string& name, const std::uintptr_t value )
	{
		printf( "[>] %-35s -> 0x%08X\n", name.c_str(), value );
	};

	msg( "ppPlayer", Offsets::player );
	msg( "Weapon break patch", Offsets::break_weapon_patch );
	msg( "Zombie Attack", Offsets::zombie_attack );
	msg( "Zombie Freeze", Offsets::zombie_freeze );
	msg( "Zombie Grapple", Offsets::zombie_grapple );
	msg( "Notebook Reveal", Offsets::notebook_reveal );
	msg( "Zombie Ignore All", Offsets::zombie_ignore_all );
	msg( "Unlock All Combo Cards", Offsets::unlock_cards );
	msg( "Time step", Offsets::time_step );
	msg( "Time hook", Offsets::time_hook );

	printf( "\n" );
}

void dr2_cheat::run()
{
	for( const auto& feature : this->m_features )
	{
		// before tick'ing the feature, check first if the state will eventually change
		if( GetAsyncKeyState( feature->get_virtual_key_code() ) & 0x8000 )
			feature->toggle();

		// let the feature tick() when active
		if( feature->is_active() )
			feature->tick();
	}
}

void dr2_cheat::shutdown()
{
	// disable every feature here
	for( const auto& feature : this->m_features )
		if( feature->is_active() )
			feature->disable();

	// clear image map here
	if( Globals::g_pProcess )
		Globals::g_pProcess->clear_image_map();
}
