//Version: 0.1.1
//Author: Jakob Pipping
//Contributors:

//Changelog:
//+ added		graphics_bad_draw_state_exception
//+ added		graphics_end_without_begin_exception
//+ added		graphics_begin_without_end_exception
//+ added		graphics_draw_without_begin_exception

#ifndef INC_EXCEPTIONS_H
#define INC_EXCEPTIONS_H

#ifdef ANGLER_0_1_1

#include <exception>

namespace Angler
{
	namespace Exceptions
	{
		struct graphics_bad_draw_state_exception
			: public std::logic_error
		{
			graphics_bad_draw_state_exception(const char* message)
				: std::logic_error(message)
			{

			}
		};

		struct graphics_end_without_begin_exception
			: public graphics_bad_draw_state_exception
		{
			graphics_end_without_begin_exception()
				: graphics_bad_draw_state_exception("End called before draw cycle started")
			{

			}
		};

		struct graphics_begin_without_end_exception
			: public graphics_bad_draw_state_exception
		{
			graphics_begin_without_end_exception()
				: graphics_bad_draw_state_exception("Before called before draw cycle ended")
			{

			}
		};

		struct graphics_draw_without_begin_exception
			: public graphics_bad_draw_state_exception
		{
			graphics_draw_without_begin_exception()
				: graphics_bad_draw_state_exception("Draw called before draw cycle started")
			{

			}
		};
	}
}

#else
#error Exceptions.h: Wrong version 0.1.1
#endif

#endif