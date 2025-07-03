
## Tóm tắt Chức năng Chính của Chương trình LED Driver

Chương trình này triển khai một **driver phần mềm cấp cao** để điều khiển các dải đèn LED RGB địa chỉ hóa (như WS2812B/NeoPixel) thông qua việc quản lý một bộ đệm dữ liệu màu. Các chức năng chính bao gồm:

### 1. Quản lý Bộ nhớ Đệm LED

* **Khởi tạo (`ledInit`)**:
    * Cấp phát động một mảng `uint32_t` để lưu trữ dữ liệu màu cho tất cả các pixel.
    * **Khởi tạo toàn bộ bộ đệm về 0** (màu đen) đảm bảo trạng thái ban đầu rõ ràng.
    * Kiểm tra và trả về lỗi nếu việc cấp phát bộ nhớ thất bại hoặc số lượng pixel không hợp lệ.
    * Xử lý việc khởi tạo lại bằng cách tự động giải phóng bộ nhớ cũ nếu driver đã được khởi tạo trước đó.
* **Giải phóng (`ledShutdown`)**:
    * **Giải phóng bộ nhớ** đã được cấp phát bởi `ledInit` để ngăn chặn rò rỉ bộ nhớ.
    * Đặt con trỏ bộ đệm về `NULL` và số lượng pixel về 0 để đánh dấu driver chưa được khởi tạo.

### 2. Thao tác Màu sắc Pixel

* **Đặt màu cho từng pixel (`ledSetPixelColor`)**:
    * Nhận các giá trị màu **Đỏ (R), Xanh lá (G), Xanh dương (B)** riêng biệt (8-bit mỗi màu).
    * Sử dụng **thao tác bit (`<<`, `|`)** để đóng gói 3 giá trị màu này vào một giá trị `uint32_t` duy nhất theo đúng định dạng **G-R-B (Green, Red, Blue)** của WS2812B. Cụ thể: `0x00GG RR BB`.
    * Bao gồm **kiểm tra biên (bounds checking)** để đảm bảo `index` của pixel hợp lệ, tránh lỗi ghi ra ngoài vùng nhớ.

* **Đổ màu toàn bộ dải (`ledFill`)**:
    * Tính toán giá trị màu `uint32_t` mong muốn chỉ **một lần**.
    * Lặp qua toàn bộ bộ đệm và gán giá trị màu đã tính toán cho **tất cả các pixel**, hiệu quả hơn so với việc đặt từng pixel một.

* **Xóa/Tắt tất cả pixel (`ledClear`)**:
    * Là một trường hợp đặc biệt của `ledFill`, đặt tất cả pixel về **màu đen** (R=0, G=0, B=0).

### 3. Truy xuất Thông tin Bộ đệm

* **Lấy con trỏ bộ đệm (`ledGetBuffer`)**:
    * Cung cấp một con trỏ **chỉ đọc (`const uint32_t*`)** tới bộ đệm dữ liệu màu bên trong. Chức năng này hữu ích cho việc kiểm thử và cho phép một module khác "gửi" dữ liệu này ra phần cứng.
* **Lấy số lượng pixel (`ledGetPixelCount`)**:
    * Trả về số lượng pixel mà dải LED hiện đang được cấu hình.

## Cách chạy bằng Makefile
- Build: `make all`
- Run: `make run`
- Clean: `make clean`