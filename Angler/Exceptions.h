//Version: 0.1.8
//Author: Jakob Pipping
//Contributors:

#ifndef INC_EXCEPTIONS_H
#define INC_EXCEPTIONS_H

#ifdef ANGLER_0_1_8

#include <exception>

namespace Angler
{
	namespace Exceptions
	{
		struct node_already_has_parent_exception
			: public std::logic_error
		{
			node_already_has_parent_exception()
				: std::logic_error("Node already has parent")
			{

			}
		};

		namespace Graphics
		{
			//Base error for bad draw states, not directly used
			struct graphics_bad_draw_state_exception
				: public std::logic_error
			{
				graphics_bad_draw_state_exception(const char* message)
					: std::logic_error(message)
				{

				}
			};
		
			//Thrown when end is called "before" begin (after an end or before ever running begin), 
			//i.e. before the draw cyrcle has started
			struct graphics_end_without_begin_exception
				: public graphics_bad_draw_state_exception
			{
				graphics_end_without_begin_exception()
					: graphics_bad_draw_state_exception("End called before draw cycle started")
				{

				}
			};

			//Thrown when begin is called "before" end (after a begin), i.e. before a 
			//draw cycle has ended
			struct graphics_begin_without_end_exception
				: public graphics_bad_draw_state_exception
			{
				graphics_begin_without_end_exception()
					: graphics_bad_draw_state_exception("Before called before draw cycle ended")
				{

				}
			};

			//Thrown when draw is called outside of the draw cycle
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
}

#else
#error Exceptions.h: Wrong version 0.1.8
#endif

#endif