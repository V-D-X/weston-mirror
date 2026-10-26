#include "config.h"

#include "zunitc/zunitc.h"

#include "../libweston/backend-rdp/rdprail.c"

ZUC_TEST(rdp_cursor, hotspot_scales_with_buffer_and_display_scale)
{
	/* Cursor 16 logical pixels wide, drawn at double resolution
	 * (buffer_scale 2, 32 px buffer) and sent at 2x: the bitmap is 64 px
	 * wide, so hotspot 5 is pixel 20. */
	ZUC_ASSERT_EQ(20, rdp_rail_scale_cursor_hotspot(5, 16, 64));
}

ZUC_TEST(rdp_cursor, hotspot_scales_with_fractional_display_scale)
{
	/* With fractional HiDPI scaling enabled, a cursor 16 logical pixels
	 * wide at 250% is a 40 px bitmap: 5 * 2.5 rounds to 13. */
	ZUC_ASSERT_EQ(13, rdp_rail_scale_cursor_hotspot(5, 16, 40));
}

ZUC_TEST(rdp_cursor, hotspot_scales_with_display_scale_only)
{
	/* Xwayland-style cursor 24 logical pixels wide, drawn at normal
	 * resolution (buffer_scale 1) and sent at 2x: the bitmap is 48 px
	 * wide, so hotspot 7 is pixel 14. */
	ZUC_ASSERT_EQ(14, rdp_rail_scale_cursor_hotspot(7, 24, 48));
}

ZUC_TEST(rdp_cursor, hotspot_stays_inside_bitmap)
{
	ZUC_ASSERT_EQ(31, rdp_rail_scale_cursor_hotspot(16, 16, 32));
}

ZUC_TEST(rdp_cursor, hotspot_invalid_input_is_zero)
{
	ZUC_ASSERT_EQ(0, rdp_rail_scale_cursor_hotspot(-3, 16, 32));
	ZUC_ASSERT_EQ(0, rdp_rail_scale_cursor_hotspot(5, 0, 32));
	ZUC_ASSERT_EQ(0, rdp_rail_scale_cursor_hotspot(5, 16, 0));
}
