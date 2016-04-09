#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
enum KEYS{ UP, DOWN, LEFT, RIGHT };
int main(void)
{
	int FPS = 60;
	const int width = 800;
	const int height = 600;
	bool keys[4] = { false, false, false, false };
	bool done = false;
	bool redraw = true;
	int posX = width / 2;
	int posY = height / 2;

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue;;
	ALLEGRO_TIMER *timer = NULL;

	if (!al_init())
	{
		return -1;
	}
	display = al_create_display(width, height);
	al_clear_to_color(al_map_rgb(100, 66, 0));//Background colour
	al_flip_display();//brings block to the front 
	if (!display)
	{

		return -1;
	}

	timer = al_create_timer(1.0 / FPS);//Frames per second coding
	al_init_primitives_addon();
	al_install_keyboard();
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));//close button

	al_start_timer(timer);//start timer

	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)//activates when key is pressed down
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)//activates when key is released 
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			}
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)//activates when key ESC is released
			{
				done = true; //set boolean variable true to end gaming loop
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)//activites the close button
		{
			done = true; //set boolean variable true to end gaming loop
		}
		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			/*Moves block 10 spaces*/
			posY -= keys[UP] * 5;
			posY += keys[DOWN] * 5;
			posX -= keys[LEFT] * 5;
			posX += keys[RIGHT] * 5;
			/*Moves block 10 spaces*/
			redraw = true;
		}
		if (redraw && al_event_queue_is_empty(event_queue))
		{
			redraw = false;
			al_draw_filled_rectangle(posX, posY, posX + 30, posY + 30, al_map_rgb(100, 255, 255));//creates block
			al_flip_display();//brings block to the front 
			al_clear_to_color(al_map_rgb(100, 66, 0));//refreshes background
		}
	}
	al_destroy_display(display);// exits the display window
	return 0;
}