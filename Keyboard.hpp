#include <SDL3/SDL.h>

char get_char(SDL_Event* event) 
{
    char c;
    if (event->key.scancode == SDL_SCANCODE_Q) {
        c = 'й';
    }
    else if (event->key.scancode == SDL_SCANCODE_W) {
        c = 'ц';
    }
    else if (event->key.scancode == SDL_SCANCODE_E) {
        c = 'у';
    }
    else if (event->key.scancode == SDL_SCANCODE_R) {
        c = 'к';
    }
    else if (event->key.scancode == SDL_SCANCODE_T) {
        c = 'е';
    }
    else if (event->key.scancode == SDL_SCANCODE_Y) {
        c = 'н';
    }
    else if (event->key.scancode == SDL_SCANCODE_U) {
        c = 'г';
    }
    else if (event->key.scancode == SDL_SCANCODE_I) {
        c = 'ш';
    }
    else if (event->key.scancode == SDL_SCANCODE_O) {
        c = 'щ';
    }
    else if (event->key.scancode == SDL_SCANCODE_P) {
        c = 'з';
    }
    else if (event->key.scancode == SDL_SCANCODE_A) {
        c = 'ф';
    }
    else if (event->key.scancode == SDL_SCANCODE_S) {
        c = 'ы';
    }
    else if (event->key.scancode == SDL_SCANCODE_D) {
        c = 'в';
    }
    else if (event->key.scancode == SDL_SCANCODE_F) {
        c = 'а';
    }
    else if (event->key.scancode == SDL_SCANCODE_G) {
        c = 'п';
    }
    else if (event->key.scancode == SDL_SCANCODE_H) {
        c = 'р';
    }
    else if (event->key.scancode == SDL_SCANCODE_J) {
        c = 'о';
    }
    else if (event->key.scancode == SDL_SCANCODE_K) {
        c = 'л';
    }
    else if (event->key.scancode == SDL_SCANCODE_L) {
        c = 'д';
    }
    else if (event->key.scancode == SDL_SCANCODE_Z) {
        c = 'я';
    }
    else if (event->key.scancode == SDL_SCANCODE_X) {
        c = 'ч';
    }
    else if (event->key.scancode == SDL_SCANCODE_C) {
        c = 'с';
    }
    else if (event->key.scancode == SDL_SCANCODE_V) {
        c = 'м';
    }
    else if (event->key.scancode == SDL_SCANCODE_B) {
        c = 'и';
    }
    else if (event->key.scancode == SDL_SCANCODE_N) {
        c = 'т';
    }
    else if (event->key.scancode == SDL_SCANCODE_M) {
        c = 'ь';
    }
    // Цифры
    else if (event->key.scancode == SDL_SCANCODE_1) {
        c = '1';
    }
    else if (event->key.scancode == SDL_SCANCODE_2) {
        c = '2';
    }
    else if (event->key.scancode == SDL_SCANCODE_3) {
        c = '3';
    }
    else if (event->key.scancode == SDL_SCANCODE_4) {
        c = '4';
    }
    else if (event->key.scancode == SDL_SCANCODE_5) {
        c = '5';
    }
    else if (event->key.scancode == SDL_SCANCODE_6) {
        c = '6';
    }
    else if (event->key.scancode == SDL_SCANCODE_7) {
        c = '7';
    }
    else if (event->key.scancode == SDL_SCANCODE_8) {
        c = '8';
    }
    else if (event->key.scancode == SDL_SCANCODE_9) {
        c = '9';
    }
    else if (event->key.scancode == SDL_SCANCODE_0) {
        c = '0';
    }
    // Специальные клавиши
    else if (event->key.scancode == SDL_SCANCODE_SPACE) {
        c = ' ';
    }
    else if (event->key.scancode == SDL_SCANCODE_MINUS) {
        c = '-';
    }
    else if (event->key.scancode == SDL_SCANCODE_EQUALS) {
        c = '=';
    }
    else if (event->key.scancode == SDL_SCANCODE_LEFTBRACKET) {
        c = '[';
    }
    else if (event->key.scancode == SDL_SCANCODE_RIGHTBRACKET) {
        c = ']';
    }
    else if (event->key.scancode == SDL_SCANCODE_SEMICOLON) {
        c = ';';
    }
    else if (event->key.scancode == SDL_SCANCODE_APOSTROPHE) {
        c = '\'';
    }
    else if (event->key.scancode == SDL_SCANCODE_COMMA) {
        c = ',';
    }
    else if (event->key.scancode == SDL_SCANCODE_PERIOD) {
        c = '.';
    }
    else if (event->key.scancode == SDL_SCANCODE_SLASH) {
        c = '/';
    }
    else if (event->key.scancode == SDL_SCANCODE_BACKSLASH) {
        c = '\\';
    }
    else {
        c = '\0'; // Неизвестный символ
    }
    return c;
}