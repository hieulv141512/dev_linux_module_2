## Tóm tắt chức năng chương trình

Chương trình C này minh họa việc sử dụng **Factory Method Pattern** để tạo và quản lý các đối tượng cảm biến khác nhau. Chức năng cốt lõi của nó là:

* **Tạo đa dạng cảm biến**: Chương trình sử dụng một "nhà máy" (`sensor_factory`) để tạo ra bốn loại cảm biến khác nhau: nhiệt độ, độ ẩm, áp suất và ánh sáng.
* **In thông tin cảm biến**: Sau khi mỗi cảm biến được tạo, chương trình gọi một hàm để in các thông tin cơ bản của cảm biến đó ra console.
* **Giải phóng bộ nhớ**: Mỗi cảm biến sau khi được sử dụng sẽ được hủy bỏ để tránh rò rỉ bộ nhớ.

Mục đích chính là trình bày cách Factory Method Pattern giúp tách biệt quá trình tạo đối tượng khỏi mã sử dụng, làm cho hệ thống linh hoạt và dễ mở rộng hơn khi có các loại cảm biến mới.

---

## Chi tiết Factory Method Pattern hoạt động

**Factory Method Pattern** là một mẫu thiết kế khởi tạo (creational design pattern) cung cấp một giao diện để tạo đối tượng trong một lớp cha, nhưng cho phép các lớp con thay đổi loại đối tượng sẽ được tạo. Nó giúp **tách rời logic tạo đối tượng** khỏi mã khách hàng (client code) sử dụng đối tượng đó.

Dựa trên đoạn mã bạn cung cấp, Factory Method Pattern hoạt động như sau:

### 1. Sản phẩm (Product)

* **`Sensor`**: Đây là giao diện hoặc lớp cơ sở (abstract base class/interface) cho tất cả các loại cảm biến. Trong C, điều này thường được thực hiện thông qua một `struct` chung và các con trỏ hàm (function pointers) để mô phỏng tính đa hình.
* **Các loại cảm biến cụ thể**: `temperatureSensor`, `humiditySensor`, `pressureSensor`, `lightSensor` là các "sản phẩm" cụ thể được tạo ra bởi nhà máy. Chúng đều tuân theo giao diện `Sensor` chung.
    * Trong code, bạn có thể có các `struct` riêng cho từng loại cảm biến (ví dụ: `TemperatureSensor_t`, `HumiditySensor_t`) mà chúng đều chứa hoặc được chuyển đổi thành `Sensor*`.

### 2. Người tạo (Creator / Factory)

* **`createSensor()` function**: Đây là "Factory Method" thực sự. Nó là một hàm trong `sensor_factory` chịu trách nhiệm tạo ra các đối tượng cảm biến cụ thể.
    * Nó nhận vào một tham số (`SENSOR_TYPE_TEMPERATURE`, `SENSOR_TYPE_HUMIDITY`, v.v.) để xác định loại cảm biến cần tạo.
    * Bên trong hàm này, có logic để quyết định sẽ khởi tạo loại cảm biến cụ thể nào (ví dụ: dùng một câu lệnh `switch-case` dựa trên `SENSOR_TYPE`).
    * Hàm này sẽ cấp phát bộ nhớ cho cảm biến và trả về một con trỏ kiểu `Sensor*` (con trỏ tới giao diện chung).

* **`main()` function (Client)**: Hàm `main()` đóng vai trò là "mã khách hàng".
    * Nó **không biết chi tiết về quá trình khởi tạo** từng loại cảm biến cụ thể (ví dụ: nó không gọi `malloc` hoặc khởi tạo các trường riêng của `TemperatureSensor`).
    * Nó chỉ gọi `createSensor()` và tin tưởng rằng hàm này sẽ trả về một đối tượng `Sensor*` đã được khởi tạo đúng cách.
    * Nó tương tác với đối tượng `Sensor*` thông qua giao diện chung (`printSensorInfo`, `destroySensor`), không cần biết đó là cảm biến nhiệt độ hay độ ẩm.

### 3. Cách hoạt động chi tiết trong code

1.  **Định nghĩa `enum` cho các loại cảm biến**:
    ```c
    // Trong inc/sensor_factory/sensor_factory.h (hoặc tương tự)
    typedef enum {
        SENSOR_TYPE_TEMPERATURE,
        SENSOR_TYPE_HUMIDITY,
        SENSOR_TYPE_PRESSURE,
        SENSOR_TYPE_LIGHT,
        // ... các loại khác
    } SensorType_t;
    ```

2.  **Định nghĩa `struct Sensor` chung**:
    ```c
    // Trong inc/sensor_factory/sensor.h
    typedef struct Sensor Sensor; // Khai báo forward
    struct Sensor {
        // Các thuộc tính chung cho tất cả cảm biến (ví dụ: ID)
        char* id;
        // Các con trỏ hàm để mô phỏng phương thức ảo (polymorphism)
        void (*printInfo)(const Sensor*);
        void (*destroy)(Sensor*);
        // ... các hàm khác
    };

    // Có thể có các struct riêng cho từng loại cảm biến với dữ liệu đặc thù
    // và chúng sẽ được ép kiểu (cast) thành Sensor* khi cần giao tiếp chung.
    // Ví dụ:
    // typedef struct {
    //     Sensor base; // Kế thừa giả
    //     float temperature_value;
    // } TemperatureSensor_t;
    ```

3.  **Triển khai `createSensor` (Factory Method)**:
    ```c
    // Trong src/sensor_factory/sensor_factory.c
    #include "inc/sensor_factory/sensor_factory.h"
    #include "inc/sensor_factory/sensor.h"
    // Bao gồm các header cho các loại cảm biến cụ thể nếu có
    #include "inc/temperature/temperature_sensor.h" // ví dụ

    Sensor* createSensor(SensorType_t type, const char* id) {
        Sensor* newSensor = NULL;

        switch (type) {
            case SENSOR_TYPE_TEMPERATURE:
                // Cấp phát bộ nhớ cho TemperatureSensor_t và khởi tạo các hàm
                // newSensor = (Sensor*)malloc(sizeof(TemperatureSensor_t));
                // if (newSensor) {
                //     newSensor->id = strdup(id);
                //     newSensor->printInfo = &printTemperatureSensorInfo; // Hàm riêng của nhiệt độ
                //     newSensor->destroy = &destroyTemperatureSensor;
                // }
                // Đây là nơi tạo instance cụ thể của từng loại cảm biến
                newSensor = createTemperatureSensor(id); // Nếu có hàm create riêng cho từng loại
                break;
            case SENSOR_TYPE_HUMIDITY:
                newSensor = createHumiditySensor(id);
                break;
            case SENSOR_TYPE_PRESSURE:
                newSensor = createPressureSensor(id);
                break;
            case SENSOR_TYPE_LIGHT:
                newSensor = createLightSensor(id);
                break;
            default:
                fprintf(stderr, "Unknown sensor type.\n");
                break;
        }
        return newSensor;
    }
    ```

4.  **Sử dụng trong `main` (Client Code)**:
    ```c
    // Trong main.c
    // ...
    Sensor* temperatureSensor = createSensor(SENSOR_TYPE_TEMPERATURE, "1");
    if (temperatureSensor != NULL) {
        temperatureSensor->printInfo(temperatureSensor); // Gọi hàm thông qua con trỏ hàm
        temperatureSensor->destroy(temperatureSensor);   // Giải phóng thông qua con trỏ hàm
    }
    // ... tương tự cho các loại cảm biến khác
    ```

### Lợi ích của Factory Method Pattern trong trường hợp này:

* **Tính mở rộng**: Nếu bạn muốn thêm một loại cảm biến mới (ví dụ: cảm biến âm thanh), bạn chỉ cần:
    1.  Tạo `struct` và các hàm cụ thể cho cảm biến âm thanh.
    2.  Thêm một `enum` mới (`SENSOR_TYPE_SOUND`).
    3.  Thêm một `case` mới trong hàm `createSensor()` để tạo cảm biến âm thanh.
    Bạn không cần thay đổi mã trong `main()` hoặc bất kỳ mã khách hàng nào khác đã sử dụng `createSensor()`.
* **Tách rời trách nhiệm**: `main()` không cần quan tâm đến cách `Sensor` được tạo ra. Nó chỉ cần biết rằng `createSensor()` sẽ cung cấp cho nó một `Sensor*` hoạt động được.
* **Dễ bảo trì**: Mọi logic liên quan đến việc khởi tạo đối tượng nằm tập trung ở một nơi (`createSensor()`), giúp việc sửa lỗi hoặc thay đổi quy trình khởi tạo trở nên dễ dàng hơn.