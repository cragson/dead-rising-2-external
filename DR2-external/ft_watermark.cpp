#include "ft_watermark.hpp"

#include "globals.hpp"

void ft_watermark::on_render()
{
	Globals::g_pOverlay->draw_rect( 10, 20, 173, 21, 255, 0, 0 );

	Globals::g_pOverlay->draw_string( "osmium: Dead Rising 2", 12, 22, 255, 255, 255 );
}
