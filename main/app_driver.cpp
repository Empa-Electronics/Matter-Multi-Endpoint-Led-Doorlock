/*
   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <esp_log.h>
#include <stdlib.h>
#include <string.h>

#include <esp_matter.h>
#include <app_priv.h>
#include <common_macros.h>

#include <device.h>
#include <led_driver.h>
#include <button_gpio.h>
#include <led_strip.h>

using namespace chip::app::Clusters;
using namespace esp_matter;

static const char *TAG = "app_driver";
extern uint16_t light_endpoint_id;
extern uint16_t door_endpoint_id2;

// Global variables to store current XY color coordinates
static uint16_t current_x = 0;
static uint16_t current_y = 0;

/* Do any conversions/remapping for the actual value here */
static esp_err_t app_driver_light_set_power(led_driver_handle_t handle, esp_matter_attr_val_t *val)
{
    // Cast handle to led_strip_t pointer
    led_strip_t *strip = (led_strip_t *)handle;
    
    if (val->val.b) {
        // Turn ON: Set RGB to white (255, 255, 255)
        ESP_LOGI(TAG, "LED ON - Setting RGB to (255, 255, 255)");
        strip->set_pixel(strip, 0, 255, 255, 255);
        strip->refresh(strip, 100);
    } else {
        // Turn OFF: Set RGB to black (0, 0, 0)
        ESP_LOGI(TAG, "LED OFF - Setting RGB to (0, 0, 0)");
        strip->set_pixel(strip, 0, 0, 0, 0);
        strip->refresh(strip, 100);
    }
    
    return ESP_OK;
}

static void app_driver_button_toggle_cb(void *arg, void *data)
{
    ESP_LOGI(TAG, "Toggle button pressed");
    uint16_t endpoint_id = light_endpoint_id;
    uint32_t cluster_id = OnOff::Id;
    uint32_t attribute_id = OnOff::Attributes::OnOff::Id;

    attribute_t *attribute = attribute::get(endpoint_id, cluster_id, attribute_id);

    esp_matter_attr_val_t val = esp_matter_invalid(NULL);
    attribute::get_val(attribute, &val);
    val.val.b = !val.val.b;
    attribute::update(endpoint_id, cluster_id, attribute_id, &val);
}

esp_err_t app_driver_attribute_update(app_driver_handle_t driver_handle, uint16_t endpoint_id, uint32_t cluster_id,
                                      uint32_t attribute_id, esp_matter_attr_val_t *val)
{
    esp_err_t err = ESP_OK;
    if (endpoint_id == light_endpoint_id) {
        // Physical LED control for endpoint 1
        led_driver_handle_t handle = (led_driver_handle_t)driver_handle;
        if (cluster_id == OnOff::Id) {
            if (attribute_id == OnOff::Attributes::OnOff::Id) {
                err = app_driver_light_set_power(handle, val);
            }
        }
    } else if (endpoint_id == door_endpoint_id2) {
        // Logging only for endpoint 2
        if (cluster_id == OnOff::Id) {
            if (attribute_id == OnOff::Attributes::OnOff::Id) {
                ESP_LOGI(TAG, "Light Endpoint 2: OnOff state changed to %s", val->val.b ? "ON" : "OFF");
            }
        }
    }
    return err;
}

esp_err_t app_driver_light_set_defaults(uint16_t endpoint_id)
{
    esp_err_t err = ESP_OK;
    
    if (endpoint_id == light_endpoint_id) {
        // Set physical LED defaults for endpoint 1
        void *priv_data = endpoint::get_priv_data(endpoint_id);
        led_driver_handle_t handle = (led_driver_handle_t)priv_data;
        esp_matter_attr_val_t val = esp_matter_invalid(NULL);

        /* Setting power - only attribute needed for on_off_light */
        attribute_t *attribute = attribute::get(endpoint_id, OnOff::Id, OnOff::Attributes::OnOff::Id);
        attribute::get_val(attribute, &val);
        err |= app_driver_light_set_power(handle, &val);
    } else if (endpoint_id == door_endpoint_id2) {
        // Just log for endpoint 2
        ESP_LOGI(TAG, "Light Endpoint 2: Initialized (logging only, no physical LED)");
    }

    return err;
}

app_driver_handle_t app_driver_light_init()
{
    /* Initialize led */
    led_driver_config_t config = led_driver_get_config();
    led_driver_handle_t handle = led_driver_init(&config);
    return (app_driver_handle_t)handle;
}

app_driver_handle_t app_driver_button_init()
{
    /* Initialize button */
    button_handle_t handle = NULL;
    const button_config_t btn_cfg = {0};
    const button_gpio_config_t btn_gpio_cfg = button_driver_get_config();

    if (iot_button_new_gpio_device(&btn_cfg, &btn_gpio_cfg, &handle) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to create button device");
        return NULL;
    }

    iot_button_register_cb(handle, BUTTON_PRESS_DOWN, NULL, app_driver_button_toggle_cb, NULL);
    return (app_driver_handle_t)handle;
}
