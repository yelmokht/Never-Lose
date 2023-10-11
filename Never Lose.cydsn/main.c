/*
 * ======================================================================================
 * Project name: Never Lose
 * Group number: 3
 * Authors : Aguilar Adriano, Azouar Mohamed, El Mokhtari Younes, Ferreira Ribeiro Brenno
 * Date: 23/05/2023
 * Github link: 
 * ======================================================================================
*/

//Imports
#include <math.h>
#include "project.h"
#include "keypad.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

// Constants
#define UART_RX_DATA_LENGTH 5
#define N 100
#define PI 3.14
#define INITIAL_POSITION 900
#define RELEASE 1000                                       
#define PRESS 2000
#define JUMP_THRESHOLD_VALUE 2400
#define DUCK_THRESHOLD_VALUE 2000
#define HIGH 1
#define LOW 0
#define LEFT_ROW 0
#define LEFT_COLUMN 0
#define RIGHT_ROW 1
#define RIGHT_COLUMN 0
#define DEFAULT_DELAY 30
#define SCORE_INCREMENT_PER_SECOND 10
#define JUMP_KEY '1'
#define DUCK_KEY '3'

//Structures
typedef struct {
	float position;
	float speed;
} dino_t;

typedef struct {
	float position;
    float width;
} obstacle_t;

// Global variables
char uart_rx_buffer;
char uart_rx_data[UART_RX_DATA_LENGTH];
char score_message[32];
int uart_rx_counter = 0;
int speed = 0;
int score = 0;
int count = 0;
float jump_audio_vector[100];
float duck_audio_vector[100];
bool is_running = false;
bool is_ground_obstacle_detected = false;
bool is_flying_obstacle_detected = false;

// Functions
void initialize_audio_vector(float *audio_vector, int type) {
    for (int i = 0; i < N; i++){
        audio_vector[i] = sin(type*PI/2 - 2*PI*i/N);
    }
}

void initialize_servos() {
    PWM_WriteCompare1(INITIAL_POSITION);
    PWM_WriteCompare2(INITIAL_POSITION);
}

void print_on_LCD(const char* message, const int row_number, const int column_number) {
    LCD_Position(row_number, column_number);
    LCD_PrintString(message);
}

void detect_obstacle() {
    AMux_Select(0);
    CyDelay(10);
    int32_t jump_value= ADC_Read32();
    jump_value = jump_value*5000/0xFFFF;
    
    AMux_Select(1);
    CyDelay(10);
    int32_t duck_value = ADC_Read32();
    duck_value = duck_value*5000/0xFFFF;
   
    
    if (jump_value < JUMP_THRESHOLD_VALUE) {
        is_ground_obstacle_detected = true;
    }
    
    if (duck_value < DUCK_THRESHOLD_VALUE) {
        is_flying_obstacle_detected = true;
    } 
    
}

bool is_dino_close_ground_obstacle() {
    bool result = is_ground_obstacle_detected;
    is_ground_obstacle_detected = false;
    return result;
}

bool is_dino_close_flying_obstacle() {
    bool result = is_flying_obstacle_detected;
    is_flying_obstacle_detected = false;
    return result;
}

void servo_press_spacebar() {
    PWM_WriteCompare1(PRESS);
}

void servo_release_spacebar() {
    PWM_WriteCompare1(RELEASE);
}

void servo_press_down_arrow_key() {
    PWM_WriteCompare2(PRESS);
}

void servo_release_down_arrow_key() {
    PWM_WriteCompare2(RELEASE);
}

void set_LED1_and_LED2(const int value) {
    LED_1_Write(value);
    LED_2_Write(value);
}

void set_LED3_and_LED4(const int value) {
    LED_3_Write(value);
    LED_4_Write(value);
}

void send_data_to_PC(const char* data) {
    UART_PutString(data);
}



void play_sound_jump() {
    for (int i =0 ; i < N; i++){
        VDAC_SetValue(jump_audio_vector[i]*1000);
        CyDelay(2);
    }
}

void play_sound_duck() {
    for (int i = N-1; i > 0; i--){
        VDAC_SetValue(duck_audio_vector[i]*1000);
        CyDelay(2);
    }
}

void dino_jump() {
    if (!is_running) {
        is_running = true;
        Timer_ISR_Enable();
    }
    servo_press_spacebar();
    set_LED1_and_LED2(HIGH);
    send_data_to_PC("Jump\n");
    print_on_LCD("Jump", LEFT_ROW, LEFT_COLUMN);
    play_sound_jump();
    CyDelay(DEFAULT_DELAY);
    servo_release_spacebar();
    set_LED1_and_LED2(LOW);
    LCD_ClearDisplay();
}


void dino_duck() {
    servo_press_down_arrow_key();
    set_LED3_and_LED4(HIGH);
    send_data_to_PC("Duck\n");
    print_on_LCD("Duck", LEFT_ROW, LEFT_COLUMN);
    play_sound_duck();
    CyDelay(DEFAULT_DELAY);
    servo_release_down_arrow_key();
    set_LED3_and_LED4(LOW);
    LCD_ClearDisplay();
}

void dino_reset() {
    is_running = false;
    Timer_ISR_Disable();
    score = 0;
}

void dino_increase_score() {
    score += SCORE_INCREMENT_PER_SECOND;
    sprintf(score_message, "%d", score); // Convert integer to string
    print_on_LCD(score_message, RIGHT_ROW, LEFT_COLUMN);
    
}

// Interrupts
CY_ISR(RX_ISR_Handler) {
    uint8_t status = 0;
    do{
        status = UART_ReadRxStatus (); // Checks if no UART Rx errors
        if ((status & UART_RX_STS_PAR_ERROR) |
            (status & UART_RX_STS_STOP_ERROR) |
            (status & UART_RX_STS_BREAK) |
            (status & UART_RX_STS_OVERRUN) ) {
            LCD_Position (1,0);
            LCD_PrintString("UART err"); // Parity , framing , break or overrun error
        }
        if ((status & UART_RX_STS_FIFO_NOTEMPTY) != 0){ // Check that rx buffer is not empty and get rx data
            uart_rx_buffer = UART_ReadRxData();
            if (uart_rx_buffer != '\n') {   
                if (uart_rx_counter < UART_RX_DATA_LENGTH) {
                    uart_rx_data[uart_rx_counter] = uart_rx_buffer;
                    UART_PutString("Received: ");
                    UART_PutChar(uart_rx_buffer);
                    UART_PutString("\n");
                }
                if (uart_rx_counter == UART_RX_DATA_LENGTH) {
                    memset(uart_rx_data, 0, sizeof(uart_rx_data));
                }
                uart_rx_counter += 1;
            }
            else {
                uart_rx_data[uart_rx_counter] = '\0'; // add null terminator
                if (strncmp(uart_rx_data, "jump", 4) == 0) {
                    dino_jump();
                }
                if (strncmp(uart_rx_data, "duck", 4) == 0) {
                    dino_duck();
                }
                memset(uart_rx_data, 0, sizeof(uart_rx_data));
                uart_rx_counter = 0;
            }
        }
    } while (( status & UART_RX_STS_FIFO_NOTEMPTY) != 0);
}

CY_ISR(Timer_ISR_Handler){  
    dino_increase_score();
    Timer_ReadStatusRegister();
}

int main(void) {
    CyGlobalIntEnable; /* Enable global interrupts. */
    RX_ISR_StartEx(RX_ISR_Handler);
    UART_Start();
    Timer_ISR_StartEx(Timer_ISR_Handler);
    Timer_Start();
    Clock_Start();
    PWM_Start();
    VDAC_Start();
    AMux_Start();
    ADC_Start();
    ADC_StartConvert();
    LCD_Start();
    initialize_audio_vector(jump_audio_vector, 0);
    initialize_audio_vector(duck_audio_vector, 1);
    initialize_servos();
    
    is_running = false;
    Timer_ISR_Disable();
    for(;;) {
        
        detect_obstacle();
            
        if  (SW_1_Read() || keypadScan() == JUMP_KEY || is_dino_close_ground_obstacle()) {
            dino_jump();
        }

        if (SW_2_Read() || keypadScan() == DUCK_KEY || is_dino_close_flying_obstacle()) {
            dino_duck();
        }

        if (SW_3_Read()) {
            dino_reset();
        }    

        CyDelay(10);  
    }
}
                                                                                                                                    