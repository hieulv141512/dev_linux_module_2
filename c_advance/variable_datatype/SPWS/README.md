---

### Tóm tắt Hệ thống tưới cây tự động thông minh (SPWS)

Hệ thống SPWS là một **hệ thống nhúng** được thiết kế để **tự động hóa việc tưới nước** cho cây trồng, dựa trên các tham số cấu hình và dữ liệu cảm biến.

---

### Ý chính và Ký hiệu Markdown

* **Mục tiêu chính**: **Tự động tưới nước** cho cây trồng một cách **thông minh** và **quản lý trạng thái** hiệu quả.

* **Phần cứng mô phỏng**:
    * `Cảm biến độ ẩm đất`: Đo `% độ ẩm` (0-100%).
    * `Cảm biến nhiệt độ môi trường`: Đo `nhiệt độ` xung quanh.
    * `Bơm nước mini`: `BẬT/TẮT` tưới.
    * `LED trạng thái`: Hiển thị trạng thái (`Xanh`: bình thường, `Vàng`: đang tưới, `Đỏ`: lỗi/cảnh báo).
    * `Nút nhấn 1`: `BẬT/TẮT` **chế độ tự động**.
    * `Nút nhấn 2`: Kích hoạt **tưới thủ công**.

* **Trạng thái hoạt động**:
    * `Chế độ hệ thống`:
        * `MODE_AUTO`: **Tự động** tưới dựa trên cảm biến.
        * `MODE_MANUAL`: Chờ lệnh **thủ công**.
    * `Trạng thái bơm`:
        * `PUMP_OFF`: Bơm `TẮT`.
        * `PUMP_ON`: Bơm `BẬT`.
    * `Trạng thái LED`:
        * `LED_NORMAL`: Hoạt động `bình thường`.
        * `LED_WATERING`: Đang `tưới nước`.
        * `LED_LOW_MOISTURE_ALERT`: `Độ ẩm thấp`.
        * `LED_ERROR`: `Lỗi` hệ thống.

* **Dữ liệu chính**:
    * `SensorData`: Lưu `độ ẩm` và `nhiệt độ`.
    * `SystemSettings`: Lưu các **tham số cấu hình** như `ngưỡng độ ẩm tối thiểu`, `ngưỡng độ ẩm tối đa`, `thời gian tưới tối đa`, `chu kỳ kiểm tra cảm biến`, `chế độ hiện tại`, `thời gian tưới thủ công`.

* **Yêu cầu chức năng**:
    * `Khởi tạo hệ thống`: Thiết lập `GPIO`, `giá trị mặc định`, `MODE_AUTO` ban đầu.
    * `Đọc/xử lý cảm biến`: `Định kỳ` đọc và lưu dữ liệu.
    * `Logic tưới tự động`: Trong `MODE_AUTO`, kích hoạt bơm khi `độ ẩm < ngưỡng tối thiểu` và dừng khi `độ ẩm >= ngưỡng tối đa` hoặc `hết thời gian tưới tối đa`.
    * `Điều khiển bơm`: Hàm `turnPumpOn()`, `turnPumpOff()`.
    * `Điều khiển LED`: Cập nhật màu LED theo **trạng thái hệ thống**.
    * `Xử lý nút nhấn`:
        * `Nút BẬT/TẮT chế độ`: Chuyển đổi `MODE_AUTO` / `MODE_MANUAL` (tắt bơm khi chuyển sang thủ công).
        * `Nút tưới thủ công`: Kích hoạt bơm trong `thời gian cố định` (chỉ trong `MODE_MANUAL`).
    * `Thông báo trạng thái`: Gửi thông báo `định kỳ` hoặc khi có **thay đổi quan trọng**.

* **Luồng hoạt động chính**: Vòng lặp vô hạn xử lý `nút nhấn`, `logic tưới`, `cập nhật LED`, `báo cáo trạng thái`, với `độ trễ nhỏ`.

* **Yêu cầu triển khai**: Ngôn ngữ **C**, **module hóa** (`.h`, `.c`), sử dụng `enum` và `struct`, **quản lý biến** `static`/`extern`, **mô phỏng** hoạt động trên console.

---