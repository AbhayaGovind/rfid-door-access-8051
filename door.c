#include <reg51.h>
#include <string.h>

sbit dooropen = P2^0;  // Motor open control pin
sbit doorclose = P2^1; // Motor close control pin
sbit rs = P2^6;        // LCD Register Select pin
sbit en = P2^7;        // LCD Enable pin

unsigned char rfid[13]; // Store 12 characters + NULL Terminator
unsigned char a;

void lcddat(unsigned char);
void lcdcmd(unsigned char);
void lcdstring(unsigned char *);
void lcdinit();
void serial_init();
void check();
void delay(int a);

// Main Function
void main()
{
    dooropen = doorclose = 0;  // Initialize door control pins
    serial_init();             // Initialize serial communication
    lcdinit();                 // Initialize the LCD

    // Step 1: Display "WELCOME"
    lcdstring("WELCOME");
    delay(1000);
    lcdcmd(0x01);  // Clear screen
    delay(500);

    // Step 2: Display "CAM PROJECT"
    lcdstring("CAM PROJECT");
    delay(1000);
    lcdcmd(0xC0);


    // Step 3: Display each team member's name separately
    lcdstring("ABHAYA GOVIND");
    delay(1000);
    lcdcmd(0x01);  // Clear screen
    delay(500);


    // Step 4: Display "DOOR ACCESS SYSTEM"
    lcdstring("DOOR ACCESS ");
    delay(1000);
    lcdcmd(0xC0);
		lcdstring("SYSTEM");
    delay(1000);
    lcdcmd(0x01);
    delay(500);

    while (1)  
    {  
        lcdinit();  
        lcdstring("SWIPE YOUR CARD");  
        
        // Read 12 characters from RFID reader
        for (a = 0; a < 12; a++)  
        {  
            while (RI == 0);      // Wait for data reception  
            rfid[a] = SBUF;       // Store received character  
            RI = 0;               // Clear receive interrupt flag  
        }  
        rfid[12] = '\0';          // Properly terminate the string  

        check();                  // Check if RFID is valid
        delay(1000);              // Small delay
    }
}

// Function to Check Valid RFID
void check()
{
    char *valid_rfid[] = {"135792468012", "123456789012"};
    char *person_names[] = {"PERSON_NAME1", "PERSON_NAME2"};
    int i, found = 0;

    // Check if the scanned RFID matches any of the valid RFID numbers
    for (i = 0; i < 2; i++)  
    {
        if (strcmp(rfid, valid_rfid[i]) == 0) // Compare RFID input with valid ones
        {
            lcdcmd(0x01);               // Clear LCD screen
            lcdstring(person_names[i]); // Display person's name
            delay(1000);                 
            lcdcmd(0x01);               // Clear screen again

            // Door Opening Process
            lcdstring("DOOR OPENING");
            lcdcmd(0xC0);
            lcdstring("ALLOW ACCESS");

            dooropen = 1;   // Rotate motor to open the door
            doorclose = 0;  // Ensure doorclose is OFF
            delay(3000);    // Wait for 3 seconds (door stays open)

            // Stop the motor before closing
            dooropen = 0;   // Stop dooropen
            doorclose = 0;  // Stop doorclose
            delay(1000);    // Small delay to ensure the motor stops completely

            // Door Closing Process
            lcdcmd(0x01);
            lcdstring("DOOR CLOSING");

            dooropen = 0;    // Ensure the motor stops turning
            doorclose = 1;   // Rotate motor in the closing direction
            delay(3000);     // Wait for 3 seconds (door stays closed)

            // Stop the motor after closing
            dooropen = 0;    // Stop motor after closing
            doorclose = 0;   // Stop motor after closing
            found = 1;
            break;  // Exit loop if RFID is valid
        }
    }

    // If RFID is not found, display the access denied message
    if (!found) 
    {
        lcdcmd(0x01);               // Clear screen
        lcdstring("UNAUTHORIZED PERSON");
        lcdcmd(0xC0);
        lcdstring("ACCESS DENIED");
        delay(2000);    // Display message for 2 seconds
    }
}

// UART Initialization for 9600 Baud Rate
void serial_init()
{
    TMOD = 0x20;  // Timer 1, Mode 2 (8-bit auto-reload)
    TH1 = 0xFD;   // 9600 Baud Rate
    SCON = 0x50;  // 8-bit data, 1 stop bit, Receive enabled
    TR1 = 1;      // Start Timer 1
}

// LCD Functions
void lcdcmd(unsigned char cmd)
{
    P1 = cmd; // Send command to LCD
    rs = 0;   // Command Mode
    en = 1;   // Enable LCD
    delay(5); 
    en = 0;
}

void lcddat(unsigned char dat)
{
    P1 = dat; // Send data to LCD
    rs = 1;   // Data Mode
    en = 1;   
    delay(5);
    en = 0;
}

void lcdstring(unsigned char *str)
{
    while (*str)
    {
        lcddat(*str++);
    }
}

void lcdinit()
{
    lcdcmd(0x38); // 2 lines, 5x7 matrix
    lcdcmd(0x0C); // Display ON, Cursor OFF
    lcdcmd(0x06); // Auto increment cursor
    lcdcmd(0x01); // Clear Display
    delay(500);
}

// Delay Function (Adjust delay as per your system clock)
void delay(int a)
{
    int i, j;
    for (i = 0; i < a; i++)
    {
        for (j = 0; j < 100; j++);
    }
}
