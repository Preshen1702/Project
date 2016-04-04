#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
int main(int argc, char **argv){

	ALLEGRO_DISPLAY *display = NULL;

	if (!al_init())
	{
		al_show_native_message_box(NULL, NULL, NULL, "Could not work", NULL, NULL);
		return -1;
	}
	display = al_create_display(800, 600);
	if (!display)
	{
		al_show_native_message_box(display,"sample title","display setting","display window was not created successfully",NULL,ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	al_destroy_display(display);
	return 0;
}