#include "global.h"


#define MAX_DISPLAY_CHARS 8
#define CHAR_WIDTH 8 // Adjust this based on your font's character width
#define NUM_NAMES 8 // Maximum number of names to handle
#define SCREEN_HEIGHT 240 // Assumed screen height
#define BOTTOM_MARGIN 10 // Margin from the bottom of the screen for the last name
#define LINE_HEIGHT 10 // Height of each line

// Macro to convert a variable name to a string
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

// Define the names and corresponding variables
#define name1 0
#define name2 0
#define name3 0
#define name4 0
#define name5 0
#define name6 0
#define name7 0
#define name8 0

// Function to convert a character to uppercase
char my_toupper(char ch) {
    if (ch >= 'a' && ch <= 'z') {
        return ch - ('a' - 'A');
    }
    return ch;
}

// Function to convert a string to uppercase and truncate it to a specified length
void convert_to_upper_and_truncate(char *dest, const char *src, size_t max_chars) {
    size_t i;
    for (i = 0; i < max_chars && src[i] != '\0'; i++) {
        dest[i] = my_toupper(src[i]);
    }
    dest[i] = '\0'; // Null-terminate the destination string
}

// Function to calculate the x-coordinate for the number based on the length of the text
int calculate_number_x_position(const char *text, int base_x) {
    size_t length = strlen(text);
    int offset = length * CHAR_WIDTH; // Width of each character
    return base_x + offset + CHAR_WIDTH; // Adding an extra character width as space
}

void Display_Text(void) { // theboy181 Display Text
    char display_names[NUM_NAMES][MAX_DISPLAY_CHARS + 1];
    const char *names[NUM_NAMES];
    int values[NUM_NAMES];
    int base_x, base_y, y_offset, i, j, number_x_position, y_position;
    int total_names = 0;

    // Initialize names array with corresponding variable names and count valid names
    names[0] = TOSTRING(name1); if (name1 != 0) total_names++;
    names[1] = TOSTRING(name2); if (name2 != 0) total_names++;
    names[2] = TOSTRING(name3); if (name3 != 0) total_names++;
    names[3] = TOSTRING(name4); if (name4 != 0) total_names++;
    names[4] = TOSTRING(name5); if (name5 != 0) total_names++;
    names[5] = TOSTRING(name6); if (name6 != 0) total_names++;
    names[6] = TOSTRING(name7); if (name7 != 0) total_names++;
    names[7] = TOSTRING(name8); if (name8 != 0) total_names++;

    // Initialize values array with corresponding variable values
    values[0] = name1;
    values[1] = name2;
    values[2] = name3;
    values[3] = name4;
    values[4] = name5;
    values[5] = name6;
    values[6] = name7;
    values[7] = name8;

    base_x = 10; // Base x-coordinate for placement
    y_offset = LINE_HEIGHT; // Y offset for each line

    // Calculate the base y-coordinate based on the number of valid names
    base_y = SCREEN_HEIGHT - BOTTOM_MARGIN - total_names * y_offset;

    RCP_SetupDL(&gMasterDisp, SETUPDL_80);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 35, 245, 125);

    for (i = 0, j = 0; i < NUM_NAMES; i++) {
        if (values[i] == 0) continue; // Skip names with zero values
        convert_to_upper_and_truncate(display_names[j], names[i], MAX_DISPLAY_CHARS);
        y_position = base_y + j * y_offset;
        Graphics_DisplaySmallText(base_x, y_position, 1.0f, 1.0f, display_names[j]);
        number_x_position = calculate_number_x_position(display_names[j], base_x);
        Graphics_DisplaySmallNumber(number_x_position, y_position, values[i]);
        j++;
    }
}