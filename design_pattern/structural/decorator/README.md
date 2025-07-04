## Tóm tắt Chức năng Chính của Project "Communication Channel Decorator"

Project này minh họa việc áp dụng **Decorator Pattern trong C** để xây dựng một hệ thống kênh giao tiếp linh hoạt, cho phép thêm các chức năng xử lý dữ liệu vào một kênh cơ bản mà không thay đổi mã nguồn của nó. Các chức năng chính bao gồm:

### 1. Kênh Giao tiếp Cơ bản (UART Channel )

* **Mô phỏng kênh vật lý**: `uart_channel_base.c` cung cấp một kênh giao tiếp "thô" (raw) mô phỏng hoạt động gửi và nhận dữ liệu qua cổng UART. Đây là **thành phần cốt lõi** (`Concrete Component`) mà các chức năng khác sẽ được "trang trí" lên trên.

### 2. Các Lớp "Trang trí" (Decorators)

Project triển khai bốn decorator chính, mỗi decorator thêm một lớp xử lý dữ liệu riêng biệt:

* **CRC Decorator (`crc.c`)**:
    * **Gửi**: Tính toán và **thêm mã kiểm tra lỗi CRC** vào cuối gói dữ liệu trước khi chuyển giao cho kênh con (lớp bên dưới).
    * **Nhận**: **Kiểm tra CRC** của dữ liệu nhận được. Nếu CRC hợp lệ, loại bỏ mã CRC và chuyển tiếp dữ liệu đã kiểm tra. Nếu không hợp lệ, báo lỗi dữ liệu bị hỏng.
* **Encryption Decorator (`encryption.c`)**:
    * **Gửi**: Thực hiện **mã hóa** dữ liệu (ví dụ: XOR đơn giản) trước khi gửi đi.
    * **Nhận**: Thực hiện **giải mã** dữ liệu đã nhận để khôi phục lại dữ liệu gốc.
* **Compression Decorator (`compression.c`)**:
    * **Gửi**: **Nén** dữ liệu (ví dụ: giảm kích thước mô phỏng) trước khi gửi, nhằm tối ưu băng thông.
    * **Nhận**: **Giải nén** dữ liệu nhận được để khôi phục kích thước và nội dung gốc.
* **Logging Decorator (`logging.c`)**:
    * **Gửi**: **Ghi log** (in ra console) nội dung dữ liệu được gửi đi ở lớp mà nó đang "trang trí".
    * **Nhận**: **Ghi log** nội dung dữ liệu nhận được. Decorator này thường được đặt ở ngoài cùng để ghi lại dữ liệu đã qua tất cả các bước xử lý hoặc dữ liệu thô tùy vị trí đặt.

---

## How to run
- Build: `make all`
- Run: `make run`
- Clean: `make clean`