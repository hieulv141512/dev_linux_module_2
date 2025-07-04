## Chức năng Chính của Chương trình Smart Home Facade

Chương trình này mô phỏng một hệ thống nhà thông minh đơn giản, sử dụng **mẫu thiết kế Facade Pattern** để cung cấp một giao diện đơn giản hóa cho các hệ thống con phức tạp bên trong.

Các chức năng chính có thể được tóm tắt như sau:

* **Khởi tạo hệ thống nhà thông minh**: Chương trình tạo một thể hiện của `SmartHomeFacade`, bên trong đó khởi tạo các hệ thống con như **Hệ thống Chiếu sáng** (`LightingSystem`), **Hệ thống An ninh** (`SecuritySystem`), và **Hệ thống Điều hòa không khí** (`HvacSystem`).
* **Kích hoạt các kịch bản tự động hóa**:
    * **Kịch bản "Thức dậy buổi sáng"** (`activateMorningRoutine`): Tự động tắt báo thức và điều chỉnh nhiệt độ điều hòa về 26 độ C.
    * **Kịch bản "Chế độ vắng nhà"** (`activateAwayMode`): Tự động bật báo thức và tắt tất cả đèn.
    * **Kịch bản "Cảnh đêm xem phim"** (`setMovieNightScene`): Điều chỉnh nhiệt độ điều hòa về 24 độ C, giảm độ sáng đèn và tắt báo thức.
* **Quản lý bộ nhớ**: Sau khi hoàn tất các kịch bản, chương trình sẽ giải phóng bộ nhớ đã cấp phát cho đối tượng `SmartHomeFacade` và các hệ thống con của nó để tránh rò rỉ bộ nhớ.

---

## Cách hoạt động của Facade Pattern

**Facade Pattern** (Mẫu thiết kế Facade) là một mẫu thiết kế cấu trúc cung cấp một **giao diện đơn giản và hợp nhất** cho một tập hợp các giao diện trong một hệ thống con (subsystem) phức tạp. Nó giúp che giấu sự phức tạp của hệ thống con từ phía client.

Trong chương trình này, Facade Pattern hoạt động như sau:

1.  **Hệ thống con phức tạp**:
    * Chương trình có ba hệ thống con riêng biệt: `LightingSystem` (hệ thống đèn), `HvacSystem` (hệ thống điều hòa), và `SecuritySystem` (hệ thống an ninh).
    * Mỗi hệ thống con này có các phương thức và hoạt động riêng của nó (ví dụ: `turnOn()`, `setBrightness()` cho đèn; `setTemperature()` cho điều hòa; `activateAlarm()`, `deactivateAlarm()` cho an ninh). Nếu một client (ví dụ: `main.c`) muốn thực hiện một kịch bản yêu cầu tương tác với nhiều hệ thống này, nó sẽ phải gọi nhiều phương thức từ nhiều đối tượng khác nhau.

2.  **Lớp Facade (`SmartHomeFacade`)**:
    * `SmartHomeFacade` là lớp thực hiện vai trò của Facade. Nó chứa các con trỏ tới các đối tượng của các hệ thống con (`lighting`, `hvac`, `security`).
    * Nó cung cấp một **API đơn giản hóa** (`activateMorningRoutine`, `activateAwayMode`, `setMovieNightScene`) cho client.

3.  **Cách thức che giấu sự phức tạp**:
    * Khi `main.c` muốn thực hiện "kịch bản buổi sáng", thay vì phải tự gọi `security->deactivateAlarm()` và `hvac->setTemperature(26)`, nó chỉ cần gọi **một hàm duy nhất** trên đối tượng Facade: `activateMorningRoutine(smartHome)`.
    * Lớp `SmartHomeFacade` bên trong sẽ chịu trách nhiệm **điều phối các lời gọi** đến các phương thức thích hợp của các hệ thống con. Nó che giấu chi tiết về cách các hệ thống con tương tác với nhau để hoàn thành một tác vụ cụ thể.

4.  **Lợi ích**:
    * **Giảm sự phụ thuộc**: Client (ở đây là `main.c`) không cần phải biết về các lớp hệ thống con hoặc cách chúng hoạt động. Nó chỉ phụ thuộc vào lớp Facade.
    * **Đơn giản hóa giao diện**: Cung cấp một giao diện dễ sử dụng, rõ ràng cho các tác vụ phức tạp, giúp giảm thiểu lỗi và tăng tốc độ phát triển.
    * **Tách biệt mối quan tâm**: Giúp phân tách logic nghiệp vụ của các kịch bản tự động hóa khỏi chi tiết triển khai của từng hệ thống phần cứng.

Tóm lại, Facade Pattern trong project này hoạt động như một **lớp trung gian đơn giản hóa**, giúp người dùng cuối (hoặc các phần khác của chương trình) tương tác với hệ thống nhà thông minh phức tạp một cách dễ dàng và hiệu quả hơn.

---

## How to run
- Build: `make all`
- Run: `make run`
- Clean: `make clean`