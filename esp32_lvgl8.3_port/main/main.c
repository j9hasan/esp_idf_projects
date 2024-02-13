/* APP RELATED INCLUDES */
#include "lvgl.h"
#include "ui/ui.h"
#include "esp_system.h"
#include "lvgl_helpers.h"
// #include "esp_spi_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"
#include "app_main.h"
#define TAG "app_main"
/*interrupt defines*/
void *(*open_cb)(lv_fs_drv_t *drv, const char *path, lv_fs_mode_t mode);
static void lv_tick_task(void *arg)
{
  (void)arg;
  lv_tick_inc(LV_TICK_PERIOD_MS);
}
// gpio_num_t BUTTON_PIN = GPIO_NUM_27;
SemaphoreHandle_t xGuiSemaphore, xSemaphore = NULL;
static void guiTask(void *pvParameter);
// void *(*open_cb)(lv_fs_drv_t *drv, const char *path, lv_fs_mode_t mode);
void app_main()
{
  xTaskCreatePinnedToCore(guiTask, "gui", 4096 * 3, NULL, 10, NULL, 1);

  /*testing fs*/
  lv_fs_file_t f;
  lv_fs_res_t res;
  res = lv_fs_open(&f, "S:/hello.txt", LV_FS_MODE_RD);
  if (res != LV_FS_RES_OK)
  {
    printf("failed to open file err code %d\n", res);
    fflush(stdout);
  }

  // uint32_t read_num;
  // uint8_t buf[8];
  // res = lv_fs_read(&f, buf, 8, &read_num);
  // if (res != LV_FS_RES_OK || read_num != 8)
  //   my_error_handling();

  lv_fs_close(&f);
}
static void guiTask(void *pvParameter)
{
  (void)pvParameter;
  xGuiSemaphore = xSemaphoreCreateMutex();

  lv_init();
  /* Initialize SPI or I2C bus used by the drivers */
  lvgl_driver_init();
  static lv_fs_drv_t drv; /*Needs to be static or global*/
  lv_fs_drv_init(&drv);   /*Basic initialization*/

  drv.letter = 'S';              /*An uppercase letter to identify the drive */
  drv.cache_size = sizeof(FILE); /*Cache size for reading in bytes. 0 to not cache.*/
  drv.ready_cb = NULL;           /*Callback to tell if the drive is ready to use */
  drv.open_cb = fopen;           /*Callback to open a file */
  drv.close_cb = fclose;         /*Callback to close a file */
  drv.read_cb = fread;           /*Callback to read a file */
  drv.write_cb = fwrite;         /*Callback to write a file */
  drv.seek_cb = fseek;           /*Callback to seek in a file (Move cursor) */
  drv.tell_cb = ftell;           /*Callback to tell the cursor position  */
  drv.dir_open_cb = NULL;        /*Callback to open directory to read its content */
  drv.dir_read_cb = NULL;        /*Callback to read a directory's content */
  drv.dir_close_cb = NULL;       /*Callback to close a directory */
  drv.user_data = NULL;          /*Any custom data if required*/
  lv_fs_drv_register(&drv);      /*Finally register the drive*/

  /* Initialize the working buffers. */
  static lv_color_t buf1[DISP_BUF_SIZE];
  static lv_color_t buf2[DISP_BUF_SIZE];

  /*register DISP driver*/
  static lv_disp_draw_buf_t disp_buf;
  uint32_t size_in_px = DISP_BUF_SIZE;

  lv_disp_draw_buf_init(&disp_buf, buf1, buf2, size_in_px);
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.draw_buf = &disp_buf;
  disp_drv.flush_cb = disp_driver_flush;
  disp_drv.hor_res = LV_HOR_RES_MAX;
  disp_drv.ver_res = LV_VER_RES_MAX;
  // disp_drv.rotated = 1;
  lv_disp_drv_register(&disp_drv);

  /*register TOUCH driver*/
  lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.read_cb = touch_driver_read;
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  lv_indev_drv_register(&indev_drv);

  /* Create and start a periodic timer interrupt to call lv_tick_inc */
  const esp_timer_create_args_t periodic_timer_args = {
      .callback = &lv_tick_task, .name = "periodic_gui"};
  esp_timer_handle_t periodic_timer;
  ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
  ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, LV_TICK_PERIOD_MS * 1000));

  ui_init();

  while (1)
  {
    vTaskDelay(pdMS_TO_TICKS(10));
    /*take the semaphore, call lvgl related function on success */
    if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
    {
      lv_task_handler();
      xSemaphoreGive(xGuiSemaphore);
    }
  }
  vTaskDelete(NULL);
}
