#define BGFX_IDL_CPP FALSE
#define STDCALL __stdcall

#include "bgfx/c99/bgfx.h"


extern bool entry_process_events(uint32_t* _width, uint32_t* _height, uint32_t* _debug, uint32_t* _reset);
extern void* entry_get_default_native_window_handle(void);
extern void* entry_get_native_display_handle(void);
extern bgfx_native_window_handle_type_t entry_get_native_window_handle_type(void);

uint16_t uint16_max(uint16_t _a, uint16_t _b)
{
	return _a < _b ? _b : _a;
}


int32_t _main_(){
    uint32_t width  = 1600;
	uint32_t height = 900;
	uint32_t debug  = BGFX_DEBUG_TEXT;
	uint32_t reset  = BGFX_RESET_VSYNC;

	bgfx_init_t init;
	bgfx_init_ctor(&init);

	init.platformData.nwh = entry_get_default_native_window_handle();
	init.platformData.ndt = entry_get_native_display_handle();
	init.platformData.type = entry_get_native_window_handle_type();
	bgfx_init(&init);
    bgfx_reset(width, height, BGFX_RESET_VSYNC, init.resolution.format);

	bgfx_set_debug(debug);

	bgfx_set_view_clear(0
		, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
		, 0xF03030ff
		, 1.0f
		, 1
		);

	while (!entry_process_events(&width, &height, &debug, &reset) )
	{
		bgfx_set_view_rect(0, 0, 0, (uint16_t)width, (uint16_t)height);
		bgfx_encoder_t* encoder = bgfx_encoder_begin(true);
		bgfx_encoder_touch(encoder, 0);
		bgfx_encoder_end(encoder);

		bgfx_dbg_text_clear(0, false);
		bgfx_dbg_text_printf(10, 10, 0xf, "Hello World!");
		bgfx_frame(false);
	}   
	bgfx_shutdown();
    return 0;
}

