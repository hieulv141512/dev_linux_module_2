## Chức năng Chính của Chương trình Hệ thống Sự kiện Nhà Thông Minh

Chương trình C này mô phỏng một hệ thống tự động hóa nhà thông minh bằng cách sử dụng **Observer Pattern** để quản lý giao tiếp giữa các cảm biến (Publishers) và các hệ thống điều khiển/thông báo (Subscribers).

Các chức năng chính có thể được tóm tắt như sau:

* **Khởi tạo Cảm biến (Publishers)**:
    * Chương trình khởi tạo bốn loại cảm biến khác nhau: **Cảm biến cửa** (`DoorSensor`), **Cảm biến chuyển động** (`MotionSensor`), **Cảm biến khói** (`SmokeSensor`), và **Cảm biến nhiệt độ** (`TemperatureSensor`).
    * Mỗi cảm biến được khởi tạo để sẵn sàng theo dõi và thông báo về các sự kiện liên quan.
* **Khởi tạo Bộ điều khiển/Thông báo (Subscribers)**:
    * Chương trình khởi tạo bốn thực thể của các hệ thống điều khiển và thông báo: **Bộ điều khiển hệ thống báo động** (`AlarmSystemController`), **Bộ điều khiển hệ thống HVAC** (`HvacSystemController`), **Bộ điều khiển hệ thống chiếu sáng** (`LightingSystemController`), và **Bộ thông báo ứng dụng di động** (`MobileAppNotifier`).
    * Mỗi bộ điều khiển/thông báo được khởi tạo để sẵn sàng nhận và xử lý các sự kiện từ cảm biến.
* **Đăng ký Subscribers với Publishers**:
    * Đây là bước cốt lõi của Observer Pattern. Mỗi cảm biến (Publisher) cho phép các bộ điều khiển/thông báo (Subscribers) đăng ký để nhận thông báo về các sự kiện của nó.
    * Trong chương trình này, **tất cả bốn loại Subscriber đều được đăng ký với tất cả bốn loại Sensor**. Điều này có nghĩa là mỗi khi bất kỳ cảm biến nào kích hoạt sự kiện, cả bốn bộ điều khiển/thông báo đều sẽ nhận được thông báo.
* **Mô phỏng Kích hoạt Sự kiện (Triggering Events)**:
    * Chương trình mô phỏng các sự kiện thực tế xảy ra bằng cách gọi các hàm `_Trigger()` của từng cảm biến.
    * Khi một sự kiện được kích hoạt (ví dụ: `doorSensorTrigger()`), cảm biến đó sẽ tự động thông báo đến tất cả các Subscriber đã đăng ký.
* **Phản ứng của Subscribers**:
    * Mỗi Subscriber có logic riêng để phản ứng với thông báo từ cảm biến. Ví dụ:
        * Khi cửa mở, hệ thống báo động có thể được kích hoạt, đèn có thể bật, HVAC có thể điều chỉnh, và ứng dụng di động có thể gửi thông báo.
        * Khi phát hiện khói, hệ thống báo động có thể hú còi, HVAC có thể tắt để ngăn khói lan rộng, và ứng dụng di động sẽ thông báo khẩn cấp.

---

## Cách Hoạt động của Observer Pattern

**Observer Pattern** (Mẫu thiết kế Người quan sát) là một mẫu thiết kế hành vi, trong đó một đối tượng (gọi là **Subject** hoặc **Publisher**) duy trì một danh sách các đối tượng phụ thuộc của nó (gọi là **Observer** hoặc **Subscriber**), và tự động thông báo cho tất cả chúng khi trạng thái của nó thay đổi.

Trong chương trình này, Observer Pattern hoạt động như sau:

1.  **Các Vai trò**:
    * **Subject/Publisher (Chủ thể/Nhà xuất bản)**: Trong ví dụ này, các cảm biến (`DoorSensor`, `MotionSensor`, `SmokeSensor`, `TemperatureSensor`) đóng vai trò là Publisher. Mỗi Publisher có một **interface chung** (`Publisher_t` hoặc một cấu trúc cơ sở với các hàm `subscribe`, `unsubscribe`, `notify`) cho phép các Observer đăng ký hoặc hủy đăng ký.
    * **Observer/Subscriber (Người quan sát/Người đăng ký)**: Các bộ điều khiển (`AlarmSystemController`, `HvacSystemController`, `LightingSystemController`) và bộ thông báo (`MobileAppNotifier`) đóng vai trò là Subscriber. Mỗi Subscriber cũng có một **interface chung** (`Subscriber_t` hoặc một cấu trúc cơ sở với hàm `update`) mà Publisher có thể gọi để thông báo sự kiện.

2.  **Đăng ký (Subscription)**:
    * Khi chương trình khởi tạo, nó gọi hàm `subscribe()` của mỗi cảm biến (`doorSensor.base.subscribe(...)`, v.v.), truyền vào một con trỏ tới đối tượng Subscriber.
    * Bên trong hàm `subscribe()`, Publisher sẽ thêm con trỏ của Subscriber vào một danh sách nội bộ (thường là một mảng hoặc danh sách liên kết). Publisher duy trì danh sách này.

3.  **Thông báo (Notification)**:
    * Khi một sự kiện xảy ra tại cảm biến (ví dụ: `doorSensorTrigger(&doorSensor, 1)`), cảm biến đó sẽ gọi hàm `notify()` (hoặc một hàm tương tự).
    * Hàm `notify()` sẽ lặp qua danh sách tất cả các Subscriber đã đăng ký với nó.
    * Đối với mỗi Subscriber trong danh sách, Publisher sẽ gọi hàm `update()` của Subscriber đó (ví dụ: `subscriber->update(subscriber_ptr, event_data)`).

4.  **Phản ứng của Observer**:
    * Mỗi Subscriber có hàm `update()` riêng, nơi nó định nghĩa logic để phản ứng với sự kiện. Vì mỗi Subscriber có thể là một loại hệ thống điều khiển khác nhau (báo động, HVAC, đèn, ứng dụng di động), chúng sẽ thực hiện các hành động khác nhau khi được thông báo, mà không cần Publisher phải biết chi tiết về các hành động đó.

**Lợi ích của Observer Pattern trong trường hợp này**:

* **Khớp nối lỏng lẻo (Loose Coupling)**: Các cảm biến (Publishers) không cần biết chi tiết về các hệ thống điều khiển (Subscribers). Chúng chỉ cần biết rằng có một giao diện `Subscriber` với hàm `update()`. Điều này giúp hệ thống dễ dàng mở rộng và bảo trì.
* **Tính linh hoạt**: Bạn có thể dễ dàng thêm các loại cảm biến hoặc bộ điều khiển mới mà không cần sửa đổi code hiện có của các thành phần khác, miễn là chúng tuân thủ giao diện Publisher/Subscriber.
* **Khả năng mở rộng**: Một sự kiện từ một cảm biến có thể kích hoạt nhiều hành động đồng thời từ nhiều hệ thống khác nhau.

Tóm lại, Observer Pattern cho phép một hệ thống tự động hóa nhà thông minh phản ứng với các thay đổi trạng thái (sự kiện từ cảm biến) một cách linh hoạt, hiệu quả và dễ quản lý, không cần các thành phần phải biết trực tiếp về nhau.

---

## How to run
- Build: `make all`
- Run: `make run`
- Clean: `make clean`