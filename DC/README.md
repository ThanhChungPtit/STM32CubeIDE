Project STM32 điều khiển động cơ DC thông qua Keypad, hiển thị trạng thái lên OLED   
-Sử dụng module NE555 để điều khiển DC, keypad4x4 để nhập giá trị tốc độ, chiều quay và ngừng, màn hình điều khiển OLED giám sát trạng thái
-Sử dụng chế độ PWM để điều chỉnh tốc độ quay của động cơ, I2C Interface để giao tiếp với OLED
-FreeRTOS chia làm 3 task nhập giá trị, quay động cơ và hiể n thị trạng thái
