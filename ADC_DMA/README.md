# 📊 Dự Án STM32: Đọc Cảm Biến Qua ADC + DMA & Hiển Thị Màn Hình OLED (FreeRTOS)

Dự án thực hiện đọc dữ liệu từ **cảm biến ánh sáng** và **cảm biến mưa** sử dụng vi điều khiển **STM32F103C8T6**, ứng dụng cơ chế truy cập bộ nhớ trực tiếp (**DMA**) để tối ưu hóa hiệu năng CPU và hiển thị thông số lên màn hình **OLED** quản lý bởi hệ điều hành thời gian thực **FreeRTOS**.

---

## 📌 Tính Năng Chính

* 🔄 **ADC Multi-Channel + DMA:** Đọc đồng thời 2 kênh ADC ở chế độ chuyển đổi liên tục (Scan Continuous Conversion Mode), dữ liệu tự động lưu vào bộ nhớ RAM thông qua DMA mà không làm tiêu tốn tài nguyên xử lý của CPU.
* 🖥️ **Hiển thị OLED:** Giao tiếp I2C hiển thị thông số cảm biến ánh sáng và cảm biến mưa theo thời gian thực.
* ⚡ **Quản lý đa nhiệm FreeRTOS:**
  * **Task 1 (Đọc cảm biến):** Xử lý và đọc dữ liệu từ bộ đệm DMA.
  * **Task 2 (Hiển thị OLED):** Đảm nhận nhiệm vụ cập nhật giao diện màn hình.
  * **Giao tiếp giữa các Task:** Sử dụng **`MailQueue`** (Queue) để truyền dữ liệu an toàn, đồng bộ giữa task đọc cảm biến và task hiển thị.

---

## 🛠️ Cấu Trúc Dự Án

```text
ADC_DMA/
├── Inc/                  # Các file header (.h) định nghĩa driver & cấu hình
├── Src/                  # Mã nguồn C (.c) chứa các hàm khởi tạo & xử lý
├── FreeRTOS/             # Mã nguồn hệ điều hành thời gian thực FreeRTOS
├── Startup/              # File khởi động STM32 (startup_stm32f103c8tx.s)
├── STM32F103C8TX_FLASH.ld# File cấu hình bộ nhớ Linker Script
└── README.md             # Tài liệu hướng dẫn & mô tả dự án
