Chương trình bạn cung cấp là một ví dụ điển hình về việc triển khai mẫu thiết kế **Builder (Xây dựng)** trong ngôn ngữ C để cấu hình UART (Universal Asynchronous Receiver-Transmitter). Đây là một cách rất hay để tạo ra các đối tượng phức tạp một cách có kiểm soát và dễ đọc.

---

## Các Ý Chính Được Thể Hiện Trong Mã Nguồn

Chương trình tập trung vào việc tạo ra và quản lý cấu hình cho một thiết bị UART thông qua một "Builder".

### 1. Mẫu Thiết Kế Builder
* **Mục đích:** Mẫu Builder cho phép bạn xây dựng các đối tượng phức tạp từng bước một, thay vì phải truyền một số lượng lớn các tham số vào một hàm tạo duy nhất (constructor). Điều này làm cho việc tạo đối tượng dễ dàng hơn và ít gây lỗi hơn, đặc biệt khi có nhiều tùy chọn cấu hình.
* **Cách triển khai:**
    * Sử dụng một cấu trúc `UART_Builder` để chứa cấu hình tạm thời (`config`) và các con trỏ hàm (function pointers) trỏ đến các hàm thiết lập (`setBaudRate`, `setParity`, v.v.).
    * Các hàm `setXyz` trả về con trỏ đến chính `UART_Builder` đó, cho phép gọi chuỗi các phương thức (method chaining), ví dụ: `builder.setBaudRate(...).setParity(...)`.
    * Hàm `build()` cuối cùng sẽ trả về đối tượng `UART_Config` đã hoàn chỉnh.

### 2. Cấu Trúc `UART_Builder` và `UART_Config`
* **`UART_Config`**: là một `struct` chứa các thành phần cấu hình cơ bản của UART như `baudRate`, `parity`, `stopBits`, `dataBits`. Đây là đối tượng cuối cùng mà Builder sẽ tạo ra.
* **`UART_Builder`**: Là `struct` trung tâm của mẫu Builder.
    * Chứa một biến kiểu `UART_Config` (`config`) để lưu trữ các giá trị cấu hình đang được xây dựng.
    * Chứa nhiều con trỏ hàm, mỗi con trỏ tương ứng với một phương thức để thiết lập một thuộc tính cụ thể của UART.

### 3. Các Hàm Thiết Lập (Setters)
* `setBaudRate`, `setParity`, `setStopBits`, `setDataBits`:
    * Mỗi hàm chịu trách nhiệm thiết lập một tham số cấu hình cụ thể cho UART.
    * Chúng nhận vào một con trỏ tới `UART_Builder` hiện tại và giá trị cần thiết lập.
    * **Kiểm tra tính hợp lệ (Validation):** Điều quan trọng là mỗi hàm đều thực hiện kiểm tra đầu vào để đảm bảo rằng giá trị được cung cấp là hợp lệ (ví dụ: `baudRate` nằm trong dải cho phép, `parity` là 0, 1 hoặc 2). Nếu giá trị không hợp lệ, một thông báo lỗi sẽ được in ra `stderr` và hàm sẽ trả về Builder mà không thay đổi cấu hình, cho phép quá trình xây dựng tiếp tục hoặc xử lý lỗi.
    * Trả về con trỏ `UART_Builder*`: Cho phép việc **gọi chuỗi phương thức** (`method chaining`).

### 4. Hàm `build()`
* `build(UART_Builder* builder)`:
    * Đây là hàm kết thúc quá trình xây dựng.
    * Nó nhận vào con trỏ tới `UART_Builder` và trả về một bản sao của đối tượng `UART_Config` đã hoàn chỉnh.
    * Sau khi gọi hàm này, đối tượng `UART_Config` đã sẵn sàng để sử dụng.

### 5. Hàm Khởi Tạo `UART_Builder_Init()`
* Đây là hàm khởi tạo `UART_Builder`.
* Nó tạo ra một biến `UART_Builder` cục bộ.
* **Thiết lập giá trị mặc định:** Gán các giá trị cấu hình UART mặc định (ví dụ: `baudRate = 9600`, `parity = NONE`, v.v.) vào trường `config`. Điều này đảm bảo rằng ngay cả khi người dùng không gọi tất cả các hàm `setXyz`, đối tượng `UART_Config` vẫn có một trạng thái hợp lệ.
* **Gán con trỏ hàm:** Quan trọng nhất, nó gán địa chỉ của các hàm `setBaudRate`, `setParity`, `setStopBits`, `setDataBits` và `build` vào các con trỏ hàm tương ứng trong cấu trúc `UART_Builder`. Đây là cách "gắn" các phương thức vào đối tượng Builder trong C.
* Trả về đối tượng `UART_Builder` đã được khởi tạo.

### 6. Hàm `printUartConfig()`
* Là một hàm tiện ích để hiển thị các giá trị cấu hình UART hiện tại của Builder.
* Giúp ích cho việc gỡ lỗi và kiểm tra.

---

## Ưu Điểm của Cách Tiếp Cận Này

* **Tính dễ đọc và rõ ràng:** Mã nguồn để cấu hình UART trở nên rất dễ đọc, ví dụ: `UART_Builder_Init().setBaudRate(9600).setParity(PARITY_EVEN).build()`.
* **Kiểm soát quá trình tạo đối tượng:** Cho phép kiểm soát chặt chẽ các bước tạo đối tượng, bao gồm kiểm tra tính hợp lệ của từng tham số.
* **Tính linh hoạt:** Bạn có thể dễ dàng thêm các tùy chọn cấu hình mới bằng cách thêm một trường vào `UART_Config`, một con trỏ hàm vào `UART_Builder`, và một hàm `setXyz` tương ứng mà không làm thay đổi các hàm đã có.
* **Tránh các hàm tạo có quá nhiều tham số:** Thay vì một hàm khởi tạo với 4-5 tham số, bạn có một hàm khởi tạo đơn giản và các phương thức riêng biệt cho từng tùy chọn.
* **Cung cấp giá trị mặc định:** Dễ dàng thiết lập các giá trị mặc định trong hàm `UART_Builder_Init()`, giúp người dùng không phải cấu hình mọi thứ nếu họ hài lòng với các giá trị mặc định.

---
## How to run:
- Build: `make all`
- Run: `make run`
- Clean: `make clean`