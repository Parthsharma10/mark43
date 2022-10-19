#include <stdio.h>

#include "FreeRTOS.h"
#include "board_io.h"
#include "common_macros.h"
#include "esp32_task.h"

#include "gpio.h"
#include "gpio_lab.h"
#include "lpc40xx.h"
#include "lpc_peripherals.h"
#include "periodic_scheduler.h"
#include "semphr.h"
#include "sj2_cli.h"
#include "task.h"

// 'static' to make these functions 'private' to this file
static void create_blinky_tasks(void);
static void create_uart_task(void);
static void blink_task(void *params);
static void uart_task(void *params);
static void task_one(void *params);
static void task_two(void *params);
/*
typedef struct {
  float f1; // 4 bytes
  char c1;  // 1 byte
  float f2;
  char c2;
} __attribute__((packed)) my_s;
*/
// static SemaphoreHandle_t press_switch;
static SemaphoreHandle_t button_semaphore = NULL;

typedef struct {
  /* First get gpio0 driver to work only, and if you finish it
   * you can do the extra credit to also make it work for other Ports
   */
  uint8_t port;

  uint8_t pin_num;

} port_pin_s;

void button_isr(void *task_parameter) {
  const port_pin_s *button = (port_pin_s *)(task_parameter);
  gpio0__set_as_input(button->pin_num);
  long yield = 0;
  while (1) {
    if (gpio0__get_level(button->pin_num)) {
      xSemaphoreGiveFromISR(button_semaphore, &yield);
    }
    portYIELD_FROM_ISR(yield);
  }
}
/*static void button_task(void *task_parameter) {

  const port_pin_s *button = (port_pin_s *)(task_parameter);
  gpio0__set_as_input(button->pin_num);
  {
    while (1) {
      if (gpio0__get_level(button->pin_num))
        xSemaphoreGive(press_switch);
    }
    vTaskDelay(10);
  }
};
*/
void led_task(void *task_parameter) {
  // Type-cast the paramter that was passed from xTaskCreate()
  const port_pin_s *led = (port_pin_s *)(task_parameter);

  while (true) {
    if (xSemaphoreTake(button_semaphore, 5000)) {
      gpio__set_low(led->pin_num, led->port);
    } else {
      gpio__set_high(led->pin_num, led->port);
    }
  }
}

// Step 2:

void my_gpio_isr(void) {
  // a) Clear Port0/2 interrupt using CLR0 or CLR2 registers
  LPC_GPIOINT->IO0IntClr |= (1 << 29);

  // b) Use fprintf(stderr) or blink and LED here to test your ISR
  fprintf(stderr, "In ISR ");
  gpio__set_high(24, 1);
}

int main(void) {

  // Read Table 95 in the LPC user manual and setup an interrupt on a switch connected to Port0 or Port2
  // a) For example, choose SW2 (P0_30) pin on SJ2 board and configure as input
  //.   Warning: P0.30, and P0.31 require pull-down resistors

  gpio0__set_as_input(29);

  gpio_s gpio = {.port_number = 1, .pin_number = 18};
  gpio__set_as_output(gpio);
  LPC_GPIOINT->IO0IntEnF |= (1 << 29);

  // b) Configure the registers to trigger Port0 interrupt (such as falling edge)

  // Install GPIO interrupt function at the CPU interrupt (exception) vector
  // c) Hijack the interrupt vector at interrupt_vector_table.c and have it call our gpio_interrupt()
  //    Hint: You can declare 'void gpio_interrupt(void)' at interrupt_vector_table.c such that it can see this function

  // Most important step: Enable the GPIO interrupt exception using the ARM Cortex M API (this is from lpc40xx.h)
  NVIC_EnableIRQ(GPIO_IRQn);

  // Toggle an LED in a loop to ensure/test that the interrupt is entering and exiting
  // For example, if the GPIO interrupt gets stuck, this LED will stop blinking
  while (1) {
    delay__ms(100);
    // TODO: Toggle an LED here
    gpio__toggle(gpio);
    fprintf(stderr, "Main ");
  }

  create_uart_task();

  // If you have the ESP32 wifi module soldered on the board, you can try uncommenting this code
  // See esp32/README.md for more details
  // uart3_init();                                                                     // Also include:  uart3_init.h
  // xTaskCreate(esp32_tcp_hello_world_task, "uart3", 1000, NULL, PRIORITY_LOW, NULL); // Include esp32_task.h
  // printf("hello world\n");
  // puts("Starting RTOS");
  // press_switch = xSemaphoreCreateBinary();
  // button_semaphore = xSemaphoreCreateBinary();
  // static port_pin_s button = {.pin_num = 29};

  // static port_pin_s led = {.port = 1, .pin_num = 24};

  // // xTaskCreate(button_task, "button", 2048 / sizeof(void *), &button, PRIORITY_LOW, NULL);
  // xTaskCreate(led_task, "led1", 2048 / sizeof(void *), &led, PRIORITY_LOW, NULL);
  // /*
  // my_s s = {
  //     .c1 = "tsla",
  //     .c2 = "tsla",
  //     .f1 = 0.1,
  //     .f2 = 1.1,

  // };
  //* /
  /*
    printf("Size of structure : %d bytes\n"
           "floats 0x%p 0x%p\n"
           "chars  0x%p 0x%p\n",
           sizeof(s), sizeof(s.f1, s.f2), sizeof(s.c1, s.c2));
  */
  // vTaskStartScheduler(); // This function never returns unless RTOS scheduler runs out of memory and fails
  return 0;
}
/*
static void task_one(void *task_parameter) {

  while (true) {
    fprintf(stderr, "AAAAAAAAAAAA");
    vTaskDelay(100);
  }
}

static void task_two(void *task_parameter) {

  while (true) {
    fprintf(stderr, "BBBBBBBBBBBB \n");
    vTaskDelay(100);
  }
}
*/
static void create_blinky_tasks(void) {
  /**
   * Use '#if (1)' if you wish to observe how two tasks can blink LEDs
   * Use '#if (0)' if you wish to use the 'periodic_scheduler.h' that will spawn 4 periodic tasks, one for each LED
   */
#if (1)
  // These variables should not go out of scope because the 'blink_task' will reference this memory
  static gpio_s led0, led1;

  // If you wish to avoid malloc, use xTaskCreateStatic() in place of xTaskCreate()
  static StackType_t led0_task_stack[512 / sizeof(StackType_t)];
  static StackType_t led1_task_stack[512 / sizeof(StackType_t)];
  static StaticTask_t led0_task_struct;
  static StaticTask_t led1_task_struct;

  led0 = board_io__get_led0();
  led1 = board_io__get_led1();

  xTaskCreateStatic(blink_task, "led0", ARRAY_SIZE(led0_task_stack), (void *)&led0, PRIORITY_LOW, led0_task_stack,
                    &led0_task_struct);
  xTaskCreateStatic(blink_task, "led1", ARRAY_SIZE(led1_task_stack), (void *)&led1, PRIORITY_LOW, led1_task_stack,
                    &led1_task_struct);
#else
  periodic_scheduler__initialize();
  UNUSED(blink_task);
#endif
}

static void create_uart_task(void) {
  // It is advised to either run the uart_task, or the SJ2 command-line (CLI), but not both
  // Change '#if (0)' to '#if (1)' and vice versa to try it out
#if (0)
  // printf() takes more stack space, size this tasks' stack higher
  xTaskCreate(uart_task, "uart", (512U * 8) / sizeof(void *), NULL, PRIORITY_LOW, NULL);
#else
  sj2_cli__init();
  UNUSED(uart_task); // uart_task is un-used in if we are doing cli init()
#endif
}

static void blink_task(void *params) {
  const gpio_s led = *((gpio_s *)params); // Parameter was input while calling xTaskCreate()

  // Warning: This task starts with very minimal stack, so do not use printf() API here to avoid stack overflow
  while (true) {
    gpio__toggle(led);
    vTaskDelay(500);
  }
}

// This sends periodic messages over printf() which uses system_calls.c to send them to UART0
static void uart_task(void *params) {
  TickType_t previous_tick = 0;
  TickType_t ticks = 0;

  while (true) {
    // This loop will repeat at precise task delay, even if the logic below takes variable amount of ticks
    vTaskDelayUntil(&previous_tick, 2000);

    /* Calls to fprintf(stderr, ...) uses polled UART driver, so this entire output will be fully
     * sent out before this function returns. See system_calls.c for actual implementation.
     *
     * Use this style print for:
     *  - Interrupts because you cannot use printf() inside an ISR
     *    This is because regular printf() leads down to xQueueSend() that might block
     *    but you cannot block inside an ISR hence the system might crash
     *  - During debugging in case system crashes before all output of printf() is sent
     */
    ticks = xTaskGetTickCount();
    fprintf(stderr, "%u: This is a polled version of printf used for debugging ... finished in", (unsigned)ticks);
    fprintf(stderr, " %lu ticks\n", (xTaskGetTickCount() - ticks));

    /* This deposits data to an outgoing queue and doesn't block the CPU
     * Data will be sent later, but this function would return earlier
     */
    ticks = xTaskGetTickCount();
    printf("This is a more efficient printf ... finished in");
    printf(" %lu ticks\n\n", (xTaskGetTickCount() - ticks));
  }
}