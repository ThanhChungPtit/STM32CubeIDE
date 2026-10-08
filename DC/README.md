# ⚙️ Dự Án STM32: Điều Khiển Động Cơ DC Qua Bàn Phím Keypad 4x4 & Hiển Thị Màn Hình OLED (FreeRTOS)

Dự án thực hiện điều khiển tốc độ, chiều quay và trạng thái dừng của **động cơ DC** (kết hợp module NE555/driver) thông qua **bàn phím trận Keypad 4x4**, sử dụng tín hiệu **PWM** từ vi điều khiển **STM32F103C8T6**, hiển thị thông số giám sát lên màn hình **OLED (I2C)** và quản lý đa nhiệm bằng hệ điều hành **FreeRTOS**.

---

## 📌 Tính Năng Chính

* ⌨️ **Bàn phím Keypad 4x4:** Cho phép người dùng nhập trực tiếp giá trị tốc độ, chọn chiều quay (thuận/ngược) và phát lệnh dừng động cơ.
* ⚡ **Tín hiệu PWM:** Thay đổi chu kỳ xung (Duty Cycle) để điều chỉnh mịn tốc độ quay của động cơ DC.
* 🖥️ **Hiển thị OLED:** Giao tiếp I2C cập nhật thông số tốc độ, chiều quay và trạng thái hoạt động thực tế.
* 🔄 **Quản lý đa nhiệm FreeRTOS (3 Task):**
  * **Task 1 (Keypad Input Task):** Quét và nhận giá trị nhập từ bàn phím trận 4x4.
  * **Task 2 (Motor Control Task):** Xử lý tính toán, điều chỉnh tín hiệu PWM và điều khiển chiều quay động cơ.
  * **Task 3 (OLED Display Task):** Đảm nhận nhiệm vụ cập nhật thông số giám sát lên màn hình OLED.

---

## 🛠️ Cấu Trúc Dự Án

```text
DC/
├── Inc/                  # Các file header (.h) định nghĩa driver & cấu hình
├── Src/                  # Mã nguồn C (.c) chứa các hàm khởi tạo & xử lý
├── FreeRTOS/             # Mã nguồn hệ điều hành thời gian thực FreeRTOS
├── Startup/              # File khởi động STM32 (startup_stm32f103c8tx.s)
├── STM32F103C8TX_FLASH.ld# File cấu hình bộ nhớ Linker Script
└── README.md             # Tài liệu hướng dẫn & mô tả dự án
