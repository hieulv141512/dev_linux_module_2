## Tóm tắt chương trình

Hệ thống Quản lý Cảm biến (Sensor Manager), được thiết kế dựa trên **mẫu thiết kế Singleton**. Mục tiêu chính của chương trình là minh họa cách một thể hiện duy nhất của `SensorManager` được tạo và sử dụng để thu thập, lưu trữ, và đẩy dữ liệu cảm biến vào một cơ sở dữ liệu (được mô phỏng).

Các chức năng chính của chương trình bao gồm:

* **Khởi tạo Singleton**: Chương trình cố gắng tạo hai thể hiện của `SensorManager` để chứng minh rằng chỉ có một thể hiện duy nhất có thể tồn tại (đặc trưng của Singleton Pattern).
* **Kết nối cơ sở dữ liệu**: Một kết nối cơ sở dữ liệu được thiết lập cho thể hiện `SensorManager` duy nhất.
* **Thu thập dữ liệu cảm biến**: Dữ liệu từ các "cảm biến" khác nhau (ánh sáng, nhiệt độ, độ ẩm) được thu thập và lưu trữ tạm thời trong `SensorManager`.
* **Đẩy dữ liệu**: Dữ liệu đã thu thập được đẩy (mô phỏng) vào cơ sở dữ liệu.
* **Kiểm tra tràn bộ đệm**: Chương trình kiểm tra hành vi của hệ thống khi cố gắng thu thập nhiều dữ liệu hơn khả năng lưu trữ của bộ đệm, minh họa cách xử lý giới hạn tài nguyên.
* **Giải phóng tài nguyên**: Thể hiện `SensorManager` được hủy bỏ để giải phóng tài nguyên.

---

## Chi tiết cách Singleton Pattern hoạt động

**Singleton Pattern** là một mẫu thiết kế đảm bảo rằng một lớp chỉ có **một thể hiện (instance) duy nhất** và cung cấp một **điểm truy cập toàn cục** đến thể hiện đó.

Dựa trên đoạn mã `main.c` bạn cung cấp và các hàm như `getSensorManagerInstance()` và `destroySensorManagerInstance()`, hoạt động của Singleton Pattern trong `SensorManager` có thể được suy ra và giải thích chi tiết như sau:

### 1. Đảm bảo một thể hiện duy nhất

* **Hàm `getSensorManagerInstance()`**: Đây là điểm mấu chốt của Singleton. Hàm này chịu trách nhiệm kiểm tra xem đã có thể hiện nào của `SensorManager` được tạo chưa.
    * Nếu **chưa có thể hiện nào**, nó sẽ tạo một thể hiện mới của `SensorManager` và trả về con trỏ tới nó.
    * Nếu **đã có một thể hiện tồn tại**, nó sẽ không tạo thể hiện mới mà chỉ trả về con trỏ tới thể hiện đã có.
* **Minh họa trong `main.c`**:
    ```c
    SensorManager* manager1 = getSensorManagerInstance(); // Lần đầu gọi, sẽ tạo instance
    // ...
    SensorManager* manager2 = getSensorManagerInstance(); // Lần hai gọi, sẽ trả về cùng instance của manager1
    if (manager2 == NULL){
        printf("Failed to create manager2 because a instance already exists.\n\n");
    }
    ```
    Dòng `printf("Failed to create manager2 because a instance already exists.\n\n");` cho thấy rằng hàm `getSensorManagerInstance()` trả về `NULL` (hoặc một giá trị lỗi khác) nếu một thể hiện đã tồn tại, ngăn chặn việc tạo ra nhiều thể hiện. Cách phổ biến hơn trong Singleton là trả về chính thể hiện đã tồn tại thay vì `NULL`. Tuy nhiên, cách triển khai này cũng có thể chấp nhận được nếu mục tiêu là chỉ cho phép một lần khởi tạo và báo lỗi khi cố gắng tạo lại.

### 2. Cung cấp điểm truy cập toàn cục

* Các hàm như `setupDatabaseConnection()`, `collectSensorData()`, và `pushDataToDatabase()` đều nhận một con trỏ tới `SensorManager` làm đối số. Điều này ngụ ý rằng các hàm này sẽ tương tác với **thể hiện duy nhất** được trả về bởi `getSensorManagerInstance()`.
* Mặc dù không phải là "điểm truy cập toàn cục" theo đúng nghĩa đen (như một biến toàn cục công khai), việc luôn phải gọi `getSensorManagerInstance()` để lấy con trỏ tới thể hiện duy nhất và truyền nó đi khắp nơi đã thiết lập một phương tiện truy cập kiểm soát.

### 3. Quản lý vòng đời (tùy chọn nhưng quan trọng)

* **Hàm `destroySensorManagerInstance()`**: Để tránh rò rỉ bộ nhớ và giải phóng tài nguyên khi không còn cần `SensorManager` nữa, một hàm hủy Singleton thường được cung cấp. Hàm này sẽ giải phóng bộ nhớ được cấp phát cho thể hiện `SensorManager` duy nhất.
* **Minh họa trong `main.c`**:
    ```c
    destroySensorManagerInstance(); // Giải phóng instance khi kết thúc
    ```
    Điều này cho phép kiểm soát khi thể hiện Singleton bị hủy, đặc biệt quan trọng trong các ứng dụng nhúng nơi tài nguyên có hạn và cần được quản lý chặt chẽ.