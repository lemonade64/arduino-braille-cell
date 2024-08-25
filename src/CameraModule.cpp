#include "CameraModule.h"
#include "HapticModule.h"

void Camera::setup() {
    camera_config_t config;

    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;

    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sccb_sda = SIOD_GPIO_NUM;
    config.pin_sccb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;

    config.frame_size = FRAMESIZE_CIF;
    config.jpeg_quality = 4;
    config.fb_count = 1;

    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        log_e("Camera Init Failed");
        return;
    }

    sensor_t * s = esp_camera_sensor_get();
    configureSettings(s);
}

std::string Camera::capturePhoto() {
    HapticModule::playEffect(HapticEffect::CAPTURE_PHOTO);
    camera_fb_t * fb = NULL;
    log_e("Capturing Image...");

    fb = esp_camera_fb_get();
    if (!fb) {
        log_e("Image Capture Failed");
        return "Image Capture Failed";
    }

    String base64Image = base64::encode(fb->buf, fb->len);

    esp_camera_fb_return(fb);

    return base64Image.c_str();
}

void Camera::configureSettings(sensor_t* s) {
    s->set_brightness(s, -2);
    s->set_contrast(s, 2);
    s->set_saturation(s, 0);
    s->set_special_effect(s, 2);
    s->set_whitebal(s, 1);
    s->set_awb_gain(s, 1);
    s->set_wb_mode(s, 0);
    s->set_exposure_ctrl(s, 1);
    s->set_aec2(s, 0);
    s->set_ae_level(s, 1);
    s->set_aec_value(s, 300);
    s->set_gain_ctrl(s, 1);
    s->set_agc_gain(s, 0);
    s->set_gainceiling(s, (gainceiling_t)0);
    s->set_bpc(s, 0);
    s->set_wpc(s, 0);
    s->set_raw_gma(s, 0);
    s->set_lenc(s, 1);
    s->set_dcw(s, 0);
    s->set_vflip(s, 1);
    s->set_hmirror(s, 1);
}